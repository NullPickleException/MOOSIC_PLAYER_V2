//==============================================================================
// WaveVisualizer.cpp
//==============================================================================
// Implementation of waveform/spectrum visualizer for audio playback using BASS FFT
//==============================================================================

#include "WaveVisualizer.h"
#include <imgui.h>
#include <cmath>
#include <algorithm>

namespace moosic
{

//==============================================================================
// Construction
//==============================================================================

WaveVisualizer::WaveVisualizer()
{
    m_fftData.resize(FFT_SIZE, 0.0f);
    m_waveformData.resize(256, 0.0f);
    m_spectrumPeaks.resize(m_style.SpectrumBands, 0.0f);
    m_smoothSpectrum.resize(m_style.SpectrumBands, 0.0f);
    m_pcmData.resize(512, 0.0f);
}

WaveVisualizer::WaveVisualizer(const WaveVisualizerStyle& style)
    : WaveVisualizer()
{
    ApplyTheme(style);
}

WaveVisualizer::~WaveVisualizer() {}

//==============================================================================
// Configuration
//==============================================================================

// REMOVED: SetStyle - Now using ApplyTheme from header

void WaveVisualizer::SetAudioStream(HSTREAM stream)
{
    m_stream = stream;
    if (stream == 0) { m_hasData = false; Reset(); }
}

void WaveVisualizer::SetVolume(float volume) 
{ 
    m_volume = std::clamp(volume, 0.0f, 1.0f); 
}

void WaveVisualizer::SetMode(VisualizerMode mode) 
{ 
    m_style.Mode = mode; 
}

void WaveVisualizer::SetScaleMultiplier(float multiplier) 
{ 
    m_style.ScaleMultiplier = (std::max)(0.1f, multiplier); 
}

void WaveVisualizer::SetVolumeAffectsScale(bool affects) 
{ 
    m_style.VolumeAffectsScale = affects; 
}

void WaveVisualizer::SetBoxSize(float width, float height) 
{ 
    m_style.BoxWidth = width; 
    m_style.BoxHeight = height; 
}

void WaveVisualizer::SetBoxWidth(float width) 
{ 
    m_style.BoxWidth = width; 
}

void WaveVisualizer::SetBoxHeight(float height) 
{ 
    m_style.BoxHeight = height; 
}

void WaveVisualizer::SetOffset(float x, float y) 
{ 
    m_style.OffsetX = x; 
    m_style.OffsetY = y; 
}

void WaveVisualizer::SetBarDimensions(float width, float gap) 
{ 
    m_style.BarWidth = (std::max)(1.0f, width); 
    m_style.BarGap = (std::max)(0.0f, gap); 
}

void WaveVisualizer::SetBarWidth(float width) 
{ 
    m_style.BarWidth = (std::max)(1.0f, width); 
}

void WaveVisualizer::SetBarGap(float gap) 
{ 
    m_style.BarGap = (std::max)(0.0f, gap); 
}

void WaveVisualizer::SetBarCount(int count) 
{ 
    m_style.SpectrumBands = (std::max)(4, (std::min)(count, 64)); 
    m_spectrumPeaks.resize(m_style.SpectrumBands, 0.0f); 
    m_smoothSpectrum.resize(m_style.SpectrumBands, 0.0f); 
}

void WaveVisualizer::SetPadding(float top, float bottom) 
{ 
    m_style.BarTopPadding = (std::max)(0.0f, top); 
    m_style.BarBottomPadding = (std::max)(0.0f, bottom); 
}

void WaveVisualizer::SetOscilloscopeScale(float scaleX, float scaleY) 
{ 
    m_style.OscilloscopeScaleX = scaleX; 
    m_style.OscilloscopeScaleY = scaleY; 
}

void WaveVisualizer::SetSpectrumScale(float scaleX, float scaleY) 
{ 
    m_style.SpectrumScaleX = scaleX; 
    m_style.SpectrumScaleY = scaleY; 
}

//==============================================================================
// Main Draw
//==============================================================================

void WaveVisualizer::Draw(float width)
{
    float boxWidth = width > 0.0f ? width : (m_customWidth > 0.0f ? m_customWidth : m_style.BoxWidth);
    if (boxWidth < 10.0f) boxWidth = 10.0f;

    ImVec2 size(boxWidth, m_style.BoxHeight);
    ImVec2 pos = ImGui::GetCursorScreenPos();
    pos.x += m_style.OffsetX;
    pos.y += m_style.OffsetY;

    ImGui::SetCursorScreenPos(pos);
    ImGui::Dummy(size);

    DrawBackground(pos, size);

    if (m_stream != 0)
    {
        ProcessAudioData();
        ProcessWaveform();
        UpdateSpectrumPeaks();
    }

    if (m_style.ShowGrid) DrawGrid(pos, size);

    if (m_style.Mode == VisualizerMode::Oscilloscope)
        DrawOscilloscope(pos, size);
    else
        DrawSpectrum(pos, size);

    DrawBorder(pos, size);
}

void WaveVisualizer::Reset()
{
    std::fill(m_fftData.begin(), m_fftData.end(), 0.0f);
    std::fill(m_waveformData.begin(), m_waveformData.end(), 0.0f);
    std::fill(m_spectrumPeaks.begin(), m_spectrumPeaks.end(), 0.0f);
    std::fill(m_smoothSpectrum.begin(), m_smoothSpectrum.end(), 0.0f);
    std::fill(m_pcmData.begin(), m_pcmData.end(), 0.0f);
    m_hasData = false;
}

//==============================================================================
// Audio Processing
//==============================================================================

void WaveVisualizer::ProcessAudioData()
{
    if (m_stream == 0) return;

    // Process FFT data
    float fft[FFT_SIZE];
    DWORD fftResult = BASS_ChannelGetData(m_stream, fft, BASS_DATA_FFT512);
    if (fftResult != (DWORD)-1)
    {
        float volFactor = m_style.VolumeAffectsScale ? m_volume : 1.0f;
        float sensitivity = m_style.SpectrumSensitivity * volFactor * m_style.ScaleMultiplier;
        for (int i = 0; i < FFT_SIZE; ++i)
        {
            m_fftData[i] = fft[i] * sensitivity;
            if (m_style.ClampToBounds) m_fftData[i] = (std::min)(m_fftData[i], 1.0f);
        }
        m_hasData = true;
    }
    else
    {
        for (int i = 0; i < FFT_SIZE; ++i) m_fftData[i] *= 0.95f;
    }

    // Process PCM data for waveform
    float pcm[1024];
    DWORD pcmResult = BASS_ChannelGetData(m_stream, pcm, sizeof(pcm) | BASS_DATA_FLOAT);
    if (pcmResult != (DWORD)-1 && pcmResult > 0)
    {
        const int totalSamples = pcmResult / sizeof(float);
        BASS_CHANNELINFO info;
        BASS_ChannelGetInfo(m_stream, &info);
        const int channels = info.chans;
        const int monoSamples = totalSamples / channels;
        m_pcmData.resize(monoSamples);
        float volFactor = m_style.VolumeAffectsScale ? m_volume : 1.0f;
        float scale = volFactor * m_style.ScaleMultiplier * 0.5f;
        for (int i = 0; i < monoSamples; ++i)
        {
            float sum = 0.0f;
            for (int ch = 0; ch < channels; ++ch) sum += pcm[i * channels + ch];
            sum /= (float)channels;
            float value = sum * scale;
            if (m_style.ClampToBounds) value = std::clamp(value, -1.0f, 1.0f);
            m_pcmData[i] = value;
        }
    }
}

void WaveVisualizer::ProcessWaveform()
{
    int samples = m_style.WaveformSamples;
    m_waveformData.resize(samples);
    if (samples <= 0 || m_pcmData.empty()) return;
    
    int pcmSize = (int)m_pcmData.size();
    for (int i = 0; i < samples; ++i)
    {
        float startT = (float)i / samples;
        float endT = (float)(i + 1) / samples;
        int startIdx = (int)(startT * pcmSize);
        int endIdx = (int)(endT * pcmSize);
        if (startIdx >= pcmSize) startIdx = pcmSize - 1;
        if (endIdx > pcmSize) endIdx = pcmSize;
        if (endIdx <= startIdx) endIdx = startIdx + 1;
        
        float maxAbs = 0.0f;
        float bestVal = 0.0f;
        for (int j = startIdx; j < endIdx; ++j)
        {
            float absVal = std::abs(m_pcmData[j]);
            if (absVal > maxAbs) { maxAbs = absVal; bestVal = m_pcmData[j]; }
        }
        
        if (i > 0 && m_style.Smoothing > 0.0f)
        {
            float prev = m_waveformData[i - 1];
            bestVal = prev + (bestVal - prev) * (1.0f - m_style.Smoothing);
        }
        m_waveformData[i] = std::clamp(bestVal, -1.0f, 1.0f);
    }
}

void WaveVisualizer::UpdateSpectrumPeaks()
{
    const int bands = m_style.SpectrumBands;
    m_spectrumPeaks.resize(bands);
    m_smoothSpectrum.resize(bands);
    const int fftBins = FFT_SIZE;
    
    for (int i = 0; i < bands; ++i)
    {
        float t0 = (float)i / bands;
        float t1 = (float)(i + 1) / bands;
        float logMin = std::log2(1.0f);
        float logMax = std::log2((float)(fftBins - 1));
        float startLog = logMin + t0 * (logMax - logMin);
        float endLog   = logMin + t1 * (logMax - logMin);
        int startBin = (int)std::pow(2.0f, startLog);
        int endBin   = (int)std::pow(2.0f, endLog);
        if (startBin < 0) startBin = 0;
        if (endBin > fftBins) endBin = fftBins;
        if (endBin <= startBin) endBin = startBin + 1;
        
        float peak = 0.0f;
        for (int j = startBin; j < endBin; ++j) 
            peak = (std::max)(peak, m_fftData[j]);
        
        if (m_style.ClampToBounds) 
            peak = std::clamp(peak, 0.0f, 1.0f);
        
        m_spectrumPeaks[i] *= m_style.SpectrumDecay;
        if (peak > m_spectrumPeaks[i]) 
            m_spectrumPeaks[i] = peak;
        
        m_smoothSpectrum[i] += (peak - m_smoothSpectrum[i]) * (1.0f - m_style.Smoothing);
    }
}

//==============================================================================
// Drawing Helpers
//==============================================================================

void WaveVisualizer::DrawBackground(const ImVec2& pos, const ImVec2& size)
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), 
                      ImGui::GetColorU32(m_style.BackgroundColor));
}

void WaveVisualizer::DrawGrid(const ImVec2& pos, const ImVec2& size)
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImU32 gridCol = ImGui::GetColorU32(m_style.GridColor);
    
    for (int i = 0; i <= m_style.GridLinesHorizontal; ++i)
    {
        float y = pos.y + (size.y * i) / m_style.GridLinesHorizontal;
        dl->AddLine(ImVec2(pos.x, y), ImVec2(pos.x + size.x, y), gridCol);
    }
    
    for (int i = 0; i <= m_style.GridLinesVertical; ++i)
    {
        float x = pos.x + (size.x * i) / m_style.GridLinesVertical;
        dl->AddLine(ImVec2(x, pos.y), ImVec2(x, pos.y + size.y), gridCol);
    }
}

void WaveVisualizer::DrawOscilloscope(const ImVec2& pos, const ImVec2& size)
{
    if (!m_hasData || m_waveformData.empty()) 
    { 
        DrawPlaceholder(pos, size); 
        return; 
    }

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const int sampleCount = (int)m_waveformData.size();
    const float centerY = pos.y + size.y * 0.5f;
    
    // Apply vertical scaling
    const float amplitude = size.y * 0.45f * m_style.OscilloscopeScaleY;
    
    // Calculate horizontal scale and offset for centering
    const float scaledWidth = size.x * m_style.OscilloscopeScaleX;
    const float xOffset = (size.x - scaledWidth) * 0.5f;

    std::vector<ImVec2> points;
    points.reserve(sampleCount);

    for (int i = 0; i < sampleCount; ++i)
    {
        float t = (sampleCount > 1) ? (float)i / (sampleCount - 1) : 0.0f;
        float x = pos.x + xOffset + t * scaledWidth;
        float sample = std::clamp(m_waveformData[i], -1.0f, 1.0f);
        float y = centerY - sample * amplitude;
        y = std::clamp(y, pos.y + 2.0f, pos.y + size.y - 2.0f);
        points.emplace_back(x, y);
    }

    // Draw fill between waveform and center line
    if (m_style.EnableWaveformFill && points.size() > 1)
    {
        ImU32 fillColor = ImGui::GetColorU32(m_style.WaveformFillColor);
        std::vector<ImVec2> fillPoints;
        fillPoints.reserve(points.size() * 2);

        for (const auto& p : points) 
            fillPoints.push_back(p);
        
        for (int i = (int)points.size() - 1; i >= 0; --i)
            fillPoints.push_back(ImVec2(points[i].x, centerY));

        drawList->AddConvexPolyFilled(fillPoints.data(), (int)fillPoints.size(), fillColor);
    }

    // Draw the waveform line
    drawList->AddPolyline(points.data(), (int)points.size(),
        ImGui::GetColorU32(m_style.WaveformColor), ImDrawFlags_None, m_style.WaveformLineWidth);
}

void WaveVisualizer::DrawSpectrum(const ImVec2& pos, const ImVec2& size)
{
    if (m_smoothSpectrum.empty() || !m_hasData) 
    { 
        DrawPlaceholder(pos, size); 
        return; 
    }

    ImDrawList* dl = ImGui::GetWindowDrawList();
    const int bands = m_style.SpectrumBands;
    const float barW = m_style.BarWidth;
    const float barGap = m_style.BarGap;

    // Apply horizontal scaling
    const float scaledWidth = size.x * m_style.SpectrumScaleX;
    const float xOffset = (size.x - scaledWidth) * 0.5f;
    
    const float totalW = bands * barW + (bands - 1) * barGap;
    const float startX = pos.x + xOffset + (scaledWidth - totalW) * 0.5f;
    
    // Apply vertical scaling
    const float bottomY = pos.y + size.y - m_style.BarBottomPadding;
    const float maxH = (size.y - m_style.BarTopPadding - m_style.BarBottomPadding) * m_style.SpectrumScaleY;

    for (int i = 0; i < bands; ++i)
    {
        float value = std::clamp(m_smoothSpectrum[i], 0.0f, 1.0f);
        float barH = value * maxH;
        if (barH > 0.01f && barH < 2.0f) barH = 2.0f;

        float y = bottomY - barH;
        if (y < pos.y + m_style.BarTopPadding) 
            y = pos.y + m_style.BarTopPadding;

        float brightness = 0.35f + value * 0.65f;
        ImVec4 c = (i >= bands * 2 / 3) ? m_style.SpectrumColorHigh : m_style.SpectrumColor;
        c.x *= brightness; 
        c.y *= brightness; 
        c.z *= brightness;

        float x = startX + i * (barW + barGap);

        dl->AddRectFilled(ImVec2(x, y), ImVec2(x + barW, bottomY),
            ImGui::GetColorU32(c), m_style.BarTopRounding, ImDrawFlags_RoundCornersTop);
    }
}

void WaveVisualizer::DrawPlaceholder(const ImVec2& pos, const ImVec2& size)
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const char* text = (m_stream == 0) ? "No Audio" : "Waiting...";
    ImVec2 ts = ImGui::CalcTextSize(text);
    ImVec2 tp(pos.x + (size.x - ts.x) * 0.5f, pos.y + (size.y - ts.y) * 0.5f);
    dl->AddText(tp, ImGui::GetColorU32(m_style.PlaceholderColor), text);
}

void WaveVisualizer::DrawBorder(const ImVec2& pos, const ImVec2& size)
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(m_style.BorderColor), m_style.BorderRounding,
        ImDrawFlags_RoundCornersAll, m_style.BorderThickness);
}

} // namespace moosic