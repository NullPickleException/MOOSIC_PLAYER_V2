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
        m_springVelocity.resize(m_style.SpectrumBands, 0.0f);
        m_runningMax = 0.01f;
    }

    WaveVisualizer::WaveVisualizer(const WaveVisualizerStyle &style)
        : WaveVisualizer()
    {
        ApplyTheme(style);
    }

    WaveVisualizer::~WaveVisualizer() {}

    //==============================================================================
    // Configuration
    //==============================================================================

    void WaveVisualizer::SetAudioStream(HSTREAM stream)
    {
        m_stream = stream;
        if (stream == 0)
        {
            m_hasData = false;
            Reset();
        }
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
        m_springVelocity.resize(m_style.SpectrumBands, 0.0f);
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
        if (boxWidth < 10.0f)
            boxWidth = 10.0f;

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

        if (m_style.ShowGrid)
            DrawGrid(pos, size);

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
        std::fill(m_springVelocity.begin(), m_springVelocity.end(), 0.0f);
        m_runningMax = 0.01f;
        m_hasData = false;
    }

    //==============================================================================
    // Audio Processing
    //==============================================================================

    void WaveVisualizer::ProcessAudioData()
    {
        if (m_stream == 0)
            return;

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
                if (m_style.ClampToBounds)
                    m_fftData[i] = (std::min)(m_fftData[i], 1.0f);
            }
            m_hasData = true;
        }
        else
        {
            for (int i = 0; i < FFT_SIZE; ++i)
                m_fftData[i] *= 0.95f;
        }

        // Process PCM data for waveform
        float pcm[2048];

        DWORD pcmResult = BASS_ChannelGetData(
            m_stream,
            pcm,
            sizeof(pcm) | BASS_DATA_FLOAT);

        if (pcmResult != (DWORD)-1 && pcmResult > 0)
        {
            const int totalSamples = pcmResult / sizeof(float);

            BASS_CHANNELINFO info;
            BASS_ChannelGetInfo(m_stream, &info);

            const int channels = info.chans;
            const int monoSamples = totalSamples / channels;

            m_pcmData.resize(monoSamples);

            float volFactor =
                m_style.VolumeAffectsScale ? m_volume : 1.0f;

            float scale =
                volFactor *
                m_style.ScaleMultiplier;

            for (int i = 0; i < monoSamples; ++i)
            {
                float sample = 0.0f;

                for (int ch = 0; ch < channels; ++ch)
                    sample += pcm[i * channels + ch];

                sample /= (float)channels;

                sample *= scale;

                if (m_style.ClampToBounds)
                    sample = std::clamp(sample, -1.0f, 1.0f);

                m_pcmData[i] = sample;
            }
        }
    }

    void WaveVisualizer::ProcessWaveform()
    {
        const int samples = m_style.WaveformSamples;

        m_waveformData.resize(samples);

        if (samples <= 0 || m_pcmData.empty())
            return;

        const int pcmSize = (int)m_pcmData.size();

        constexpr float EnvelopeBlend = 0.35f;
        constexpr float TemporalSmooth = 0.65f;

        for (int i = 0; i < samples; ++i)
        {
            int start =
                (i * pcmSize) / samples;

            int end =
                ((i + 1) * pcmSize) / samples;

            if (end <= start)
                end = start + 1;

            float average = 0.0f;
            float peak = 0.0f;

            for (int j = start; j < end; ++j)
            {
                float s = m_pcmData[j];

                average += s;

                peak = (std::max)(peak, std::abs(s));
            }

            average /= (float)(end - start);

            float value =
                average * (1.0f - EnvelopeBlend);

            value +=
                peak *
                (average >= 0.0f ? 1.0f : -1.0f) *
                EnvelopeBlend;

            if (i > 0)
            {
                value =
                    m_waveformData[i - 1] * TemporalSmooth +
                    value * (1.0f - TemporalSmooth);
            }

            m_waveformData[i] =
                std::clamp(value, -1.0f, 1.0f);
        }
    }


    
    void WaveVisualizer::UpdateSpectrumPeaks()
    {
        const int bands = m_style.SpectrumBands;
        const int fftBins = FFT_SIZE;

        m_spectrumPeaks.resize(bands);
        m_smoothSpectrum.resize(bands);
        m_springVelocity.resize(bands);

        // ──────────────────────────────────────────────
        // Step 1: Compute raw energy per band (RMS)
        // ──────────────────────────────────────────────
        std::vector<float> rawEnergy(bands, 0.0f);

        for (int i = 0; i < bands; ++i)
        {
            // Logarithmic frequency mapping
            float t0 = (float)i / bands;
            float t1 = (float)(i + 1) / bands;

            int startBin = (int)(powf((float)fftBins, t0));
            int endBin = (int)(powf((float)fftBins, t1));

            startBin = std::clamp(startBin, 1, fftBins - 1);
            endBin = std::clamp(endBin, startBin + 1, fftBins);

            // RMS energy
            float energy = 0.0f;
            for (int j = startBin; j < endBin; ++j)
                energy += m_fftData[j] * m_fftData[j];
            energy = sqrtf(energy / (float)(endBin - startBin));

            rawEnergy[i] = energy;
        }

        // ──────────────────────────────────────────────
        // Step 2: Auto-gain normalization
        // ──────────────────────────────────────────────
        if (m_style.EnableAutoGain)
        {
            float frameMax = 0.0f;
            for (int i = 0; i < bands; ++i)
                if (rawEnergy[i] > frameMax)
                    frameMax = rawEnergy[i];

            frameMax = (std::max)(frameMax, 0.001f); // Prevent division by zero

            // Slowly track the running maximum
            m_runningMax = (std::max)(m_runningMax * m_style.AutoGainSpeed, frameMax);
            m_runningMax = (std::max)(m_runningMax, 0.01f); // Floor so quiet sections don't blow up

            float gain = 1.0f / m_runningMax;
            for (int i = 0; i < bands; ++i)
                rawEnergy[i] *= gain;
        }

        // ──────────────────────────────────────────────
        // Step 3: Frequency compensation + gamma
        // ──────────────────────────────────────────────
        for (int i = 0; i < bands; ++i)
        {
            float t = (float)i / bands;

            // High frequency boost: 1.0 + boost * t^curve
            float eq = 1.0f + m_style.HighFrequencyBoost * powf(t, m_style.FrequencyBoostCurve);

            // Gamma correction for dynamic range
            float shaped = powf(rawEnergy[i], m_style.DynamicRange);

            // Apply EQ
            shaped *= eq;

            // Apply sensitivity and scale
            shaped *= m_style.SpectrumSensitivity * m_style.ScaleMultiplier;

            // Noise floor gate
            if (shaped < m_style.NoiseFloor)
                shaped = 0.0f;

            // Clamp
            shaped = std::clamp(shaped, 0.0f, 1.0f);

            rawEnergy[i] = shaped;
        }

        // ──────────────────────────────────────────────
        // Step 4: Neighbor blur (spatial smoothing)
        // ──────────────────────────────────────────────
        std::vector<float> blurred(bands, 0.0f);

        if (m_style.EnableNeighborBlur && m_style.NeighborSmoothing > 0.0f)
        {
            float s = m_style.NeighborSmoothing;

            for (int i = 0; i < bands; ++i)
            {
                // Get neighbors (with clamping at edges)
                float left = (i > 0) ? rawEnergy[i - 1] : rawEnergy[i];
                float self = rawEnergy[i];
                float right = (i < bands - 1) ? rawEnergy[i + 1] : rawEnergy[i];

                // Weighted blend: (s/2) left + (1-s) self + (s/2) right
                blurred[i] = (left + right) * (s * 0.5f) + self * (1.0f - s);
            }
        }
        else
        {
            blurred = rawEnergy;
        }

        // ──────────────────────────────────────────────
        // Step 5: Temporal smoothing (attack/release or spring)
        // ──────────────────────────────────────────────
        for (int i = 0; i < bands; ++i)
        {
            float target = blurred[i];

            if (m_style.EnableSpringAnimation)
            {
                // ── Spring physics ─────────────────────
                // velocity += (target - height) * stiffness
                // velocity *= damping
                // height += velocity

                float force = (target - m_smoothSpectrum[i]) * m_style.SpringStiffness;
                m_springVelocity[i] += force;
                m_springVelocity[i] *= m_style.SpringDamping;
                m_smoothSpectrum[i] += m_springVelocity[i];

                m_smoothSpectrum[i] = std::clamp(m_smoothSpectrum[i], 0.0f, 1.0f);
            }
            else
            {
                // ── Attack/Release smoothing ──────────
                float response = (target > m_smoothSpectrum[i])
                                     ? m_style.AttackSpeed
                                     : m_style.ReleaseSpeed;

                m_smoothSpectrum[i] += (target - m_smoothSpectrum[i]) * response;
            }

            // ──────────────────────────────────────────
            // Peak hold (common to both modes)
            // ──────────────────────────────────────────
            if (m_style.ShowPeaks)
            {
                if (m_smoothSpectrum[i] > m_spectrumPeaks[i])
                    m_spectrumPeaks[i] = m_smoothSpectrum[i];
                else
                    m_spectrumPeaks[i] *= m_style.PeakDecay;
            }
        }
    }

    //==============================================================================
    // ComputeBarColor — helper for peak-aware + frequency-tinted coloring
    //==============================================================================

    ImVec4 WaveVisualizer::ComputeBarColor(int bandIndex, int totalBands, float energy) const
    {
        ImVec4 result;

        if (m_style.UseColorRamp)
        {
            // --- Peak-aware color ramp ---
            // Blend between Low / Mid / High based on bar energy

            ImVec4 low = m_style.SpectrumColorLow;
            ImVec4 mid = m_style.SpectrumColorMid;
            ImVec4 high = m_style.SpectrumColorHigh;

            float t_low = m_style.ColorRampLowThreshold;
            float t_mid = m_style.ColorRampMidThreshold;
            float t_high = m_style.ColorRampHighThreshold;

            if (energy <= t_low)
            {
                result = low;
            }
            else if (energy <= t_mid)
            {
                float blend = (energy - t_low) / (t_mid - t_low);
                result = ImVec4(
                    low.x + (mid.x - low.x) * blend,
                    low.y + (mid.y - low.y) * blend,
                    low.z + (mid.z - low.z) * blend,
                    1.0f);
            }
            else if (energy <= t_high)
            {
                float blend = (energy - t_mid) / (t_high - t_mid);
                result = ImVec4(
                    mid.x + (high.x - mid.x) * blend,
                    mid.y + (high.y - mid.y) * blend,
                    mid.z + (high.z - mid.z) * blend,
                    1.0f);
            }
            else
            {
                result = high;
            }

            // --- Frequency-based tint ---
            if (m_style.UseFrequencyTint)
            {
                float freqT = (float)bandIndex / (float)(totalBands - 1); // 0.0 = bass, 1.0 = treble
                ImVec4 tint;
                tint.x = m_style.LowFreqTint.x + (m_style.HighFreqTint.x - m_style.LowFreqTint.x) * freqT;
                tint.y = m_style.LowFreqTint.y + (m_style.HighFreqTint.y - m_style.LowFreqTint.y) * freqT;
                tint.z = m_style.LowFreqTint.z + (m_style.HighFreqTint.z - m_style.LowFreqTint.z) * freqT;

                float s = m_style.FrequencyTintBlend;
                result.x = result.x * (1.0f - s) + tint.x * s;
                result.y = result.y * (1.0f - s) + tint.y * s;
                result.z = result.z * (1.0f - s) + tint.z * s;
            }
        }
        else
        {
            // --- Legacy flat coloring ---
            // Right-side bars get a slightly different color
            if (bandIndex >= totalBands * 2 / 3)
                result = m_style.SpectrumColorHighEnd;
            else
                result = m_style.SpectrumColor;
        }

        // --- Brightness boost based on energy ---
        float brightness = m_style.BarBrightnessMin + energy * (m_style.BarBrightnessMax - m_style.BarBrightnessMin);
        result.x *= brightness;
        result.y *= brightness;
        result.z *= brightness;

        // Clamp
        result.x = std::clamp(result.x, 0.0f, 1.0f);
        result.y = std::clamp(result.y, 0.0f, 1.0f);
        result.z = std::clamp(result.z, 0.0f, 1.0f);
        result.w = 1.0f;

        return result;
    }

    //==============================================================================
    // Drawing Helpers
    //==============================================================================

        void WaveVisualizer::DrawBackground(const ImVec2 &pos, const ImVec2 &size)
    {
        ImDrawList *dl = ImGui::GetWindowDrawList();
        
        // Draw gradient background if enabled
        if (m_style.UseVisualizerGradient)
        {
            dl->AddRectFilledMultiColor(
                pos, ImVec2(pos.x + size.x, pos.y + size.y),
                ImGui::GetColorU32(m_style.VisualizerGradientTop),
                ImGui::GetColorU32(m_style.VisualizerGradientTop),
                ImGui::GetColorU32(m_style.VisualizerGradientBottom),
                ImGui::GetColorU32(m_style.VisualizerGradientBottom));
        }
        else
        {
            dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                              ImGui::GetColorU32(m_style.BackgroundColor));
        }
        
        // Draw glass effect overlay if enabled
        if (m_style.UseGlassEffect && m_style.GlassOpacity > 0.0f)
        {
            ImVec4 glassColor = ImVec4(1.0f, 1.0f, 1.0f, m_style.GlassOpacity);
            dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                              ImGui::GetColorU32(glassColor));
        }
    }

    void WaveVisualizer::DrawGrid(const ImVec2 &pos, const ImVec2 &size)
    {
        ImDrawList *dl = ImGui::GetWindowDrawList();
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
    void WaveVisualizer::DrawOscilloscope(const ImVec2 &pos, const ImVec2 &size)
    {
        if (!m_hasData || m_waveformData.empty())
        {
            DrawPlaceholder(pos, size);
            return;
        }

        ImDrawList *drawList = ImGui::GetWindowDrawList();

        const int sampleCount = (int)m_waveformData.size();
        const float centerY = pos.y + size.y * 0.5f;

        const float amplitude = size.y * 0.45f * m_style.OscilloscopeScaleY;

        const float scaledWidth = size.x * m_style.OscilloscopeScaleX;
        const float xOffset = (size.x - scaledWidth) * 0.5f;

        std::vector<ImVec2> points;
        points.reserve(sampleCount);

        for (int i = 0; i < sampleCount; ++i)
        {
            float t = (sampleCount > 1)
                          ? (float)i / (sampleCount - 1)
                          : 0.0f;

            float x = pos.x + xOffset + t * scaledWidth;

            float sample = std::clamp(m_waveformData[i], -1.0f, 1.0f);

            float y = centerY - sample * amplitude;

            y = std::clamp(y, pos.y + 2.0f, pos.y + size.y - 2.0f);

            points.emplace_back(x, y);
        }

        // Draw fill if enabled
        if (m_style.EnableWaveformFill)
        {
            std::vector<ImVec2> fillPoints = points;
            fillPoints.push_back(ImVec2(points.back().x, centerY));
            fillPoints.push_back(ImVec2(points.front().x, centerY));
            drawList->AddConvexPolyFilled(fillPoints.data(), (int)fillPoints.size(),
                                          ImGui::GetColorU32(m_style.WaveformFillColor));
        }

        // Draw waveform line
        drawList->AddPolyline(
            points.data(), (int)points.size(),
            ImGui::GetColorU32(m_style.WaveformColor),
            ImDrawFlags_None, m_style.WaveformLineWidth);

        // Draw waveform gloss if enabled
        if (m_style.UseGlossyWaveform && m_style.WaveformGlossIntensity > 0.0f)
        {
            ImVec4 glossColor = ImVec4(1.0f, 1.0f, 1.0f, m_style.WaveformGlossIntensity * 0.3f);
            // Shift waveform up slightly and draw thinner semi-transparent version for gloss
            for (auto& p : points)
                p.y -= 1.0f;
            drawList->AddPolyline(
                points.data(), (int)points.size(),
                ImGui::GetColorU32(glossColor),
                ImDrawFlags_None, (std::max)(1.0f, m_style.WaveformLineWidth * 0.5f));
        }
    }

    //==============================================================================
    // DrawSpectrum
    //==============================================================================
    void WaveVisualizer::DrawSpectrum(const ImVec2 &pos, const ImVec2 &size)
    {
        if (m_smoothSpectrum.empty() || !m_hasData)
        {
            DrawPlaceholder(pos, size);
            return;
        }

        ImDrawList *dl = ImGui::GetWindowDrawList();
        const int bands = m_style.SpectrumBands;
        const float barW = m_style.BarWidth;
        const float barGap = m_style.BarGap;

        const float scaledWidth = size.x * m_style.SpectrumScaleX;
        const float xOffset = (size.x - scaledWidth) * 0.5f;

        const float totalW = bands * barW + (bands - 1) * barGap;
        const float startX = pos.x + xOffset + (scaledWidth - totalW) * 0.5f;

        const float bottomY = pos.y + size.y - m_style.BarBottomPadding;
        const float maxH = (size.y - m_style.BarTopPadding - m_style.BarBottomPadding) * m_style.SpectrumScaleY;

        for (int i = 0; i < bands; ++i)
        {
            float value = std::clamp(m_smoothSpectrum[i], 0.0f, 1.0f);
            float barH = value * maxH;
            if (barH > 0.01f && barH < 2.0f)
                barH = 2.0f;

            float y = bottomY - barH;
            if (y < pos.y + m_style.BarTopPadding)
                y = pos.y + m_style.BarTopPadding;

            ImVec4 barColor = ComputeBarColor(i, bands, value);

            float x = startX + i * (barW + barGap);

            // Draw bar
            if (m_style.RoundBarTops && m_style.BarTopRounding > 0.0f)
            {
                dl->AddRectFilled(ImVec2(x, y), ImVec2(x + barW, bottomY),
                                  ImGui::GetColorU32(barColor), m_style.BarTopRounding, ImDrawFlags_RoundCornersTop);
            }
            else
            {
                dl->AddRectFilled(ImVec2(x, y), ImVec2(x + barW, bottomY),
                                  ImGui::GetColorU32(barColor));
            }

            // Draw bar gloss if enabled
            if (m_style.UseGlossyBars && m_style.BarGlossIntensity > 0.0f)
            {
                float glossH = barH * 0.35f;
                if (glossH > 1.0f)
                {
                    ImVec4 fadeOut = ImVec4(m_style.BarGlossColor.x, m_style.BarGlossColor.y, 
                                             m_style.BarGlossColor.z, 0.0f);
                    ImVec4 glossCol = m_style.BarGlossColor;
                    glossCol.w *= m_style.BarGlossIntensity;
                    
                    ImU32 colTop = ImGui::GetColorU32(glossCol);
                    ImU32 colBot = ImGui::GetColorU32(fadeOut);
                    
                    dl->AddRectFilledMultiColor(
                        ImVec2(x, y), ImVec2(x + barW, y + glossH),
                        colTop, colTop, colBot, colBot);
                }
            }

            // Draw peak dot if enabled
            if (m_style.ShowPeaks && m_spectrumPeaks[i] > 0.01f)
            {
                float peakValue = std::clamp(m_spectrumPeaks[i], 0.0f, 1.0f);
                float peakY = bottomY - peakValue * maxH;
                if (peakY < pos.y + m_style.BarTopPadding)
                    peakY = pos.y + m_style.BarTopPadding;

                float peakX = x + barW * 0.5f;
                float peakRadius = 2.0f;

                dl->AddCircleFilled(ImVec2(peakX, peakY), peakRadius,
                                    ImGui::GetColorU32(m_style.SpectrumColorPeak));
            }
        }
    }

    void WaveVisualizer::DrawPlaceholder(const ImVec2 &pos, const ImVec2 &size)
    {
        ImDrawList *dl = ImGui::GetWindowDrawList();
        const char *text = (m_stream == 0) ? "No Audio" : "Waiting...";
        ImVec2 ts = ImGui::CalcTextSize(text);
        ImVec2 tp(pos.x + (size.x - ts.x) * 0.5f, pos.y + (size.y - ts.y) * 0.5f);
        dl->AddText(tp, ImGui::GetColorU32(m_style.PlaceholderColor), text);
    }

    void WaveVisualizer::DrawBorder(const ImVec2 &pos, const ImVec2 &size)
    {
        ImDrawList *dl = ImGui::GetWindowDrawList();
        dl->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                    ImGui::GetColorU32(m_style.BorderColor), m_style.BorderRounding,
                    ImDrawFlags_RoundCornersAll, m_style.BorderThickness);
    }

} // namespace moosic