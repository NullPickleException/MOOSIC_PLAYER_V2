//==============================================================================
// WaveVisualizer.h
//==============================================================================
// A waveform/spectrum visualizer for audio playback using BASS FFT
//==============================================================================

#pragma once

#include <imgui.h>
#include <vector>
#include <bass.h>

namespace moosic
{

    enum class VisualizerMode
    {
        Oscilloscope,
        Spectrum
    };

    struct WaveVisualizerStyle
    {
        // Box Sizing
        float BoxWidth = 137.0f;
        float BoxHeight = 45.0f;
        float BorderRounding = 3.0f;
        float BorderThickness = 3.0f;

        // Layout Offsets
        float OffsetX = 0.0f;
        float OffsetY = 0.0f;

        //------------------------------------------------------------------
        // Per-mode scaling factors
        //------------------------------------------------------------------
        float OscilloscopeScaleX = 1.0f;
        float OscilloscopeScaleY = 1.0f;
        float SpectrumScaleX = 1.0f;
        float SpectrumScaleY = 1.0f;

        // Spectrum Bar Layout
        int SpectrumBands = 16;
        float BarWidth = 3.2f;
        float BarGap = 5.0f;
        float BarBottomPadding = 3.0f;
        float BarTopPadding = 2.0f;
        float BarTopRounding = 2.0f;
        bool RoundBarTops = true;

        // Waveform Settings
        int WaveformSamples = 128;
        float WaveformLineWidth = 1.5f;
        bool EnableWaveformFill = true;

        // Audio Processing
        float SpectrumSensitivity = 2.0f;
        float SpectrumDecay = 0.7f;
        float Smoothing = 0.6f;
        float ScaleMultiplier = 3.3f;
        bool VolumeAffectsScale = false;
        bool ClampToBounds = true;

        // Colors
        ImVec4 BackgroundColor = ImVec4(0.04f, 0.04f, 0.06f, 1.0f);
        ImVec4 WaveformColor = ImVec4(0.15f, 0.45f, 0.85f, 1.0f);
        ImVec4 WaveformFillColor = ImVec4(0.08f, 0.25f, 0.50f, 0.15f);
        ImVec4 SpectrumColor = ImVec4(0.12f, 0.40f, 0.80f, 1.0f);
        ImVec4 SpectrumColorHigh = ImVec4(0.25f, 0.60f, 1.0f, 1.0f);
        ImVec4 GridColor = ImVec4(0.08f, 0.08f, 0.10f, 0.4f);
        ImVec4 BorderColor = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
        ImVec4 PlaceholderColor = ImVec4(0.30f, 0.30f, 0.35f, 0.6f);

        // Grid & Misc
        VisualizerMode Mode = VisualizerMode::Spectrum;
        bool ShowGrid = false;
        int GridLinesHorizontal = 2;
        int GridLinesVertical = 4;
        bool ShowPeaks = false;
    };

    class WaveVisualizer
    {
    public:
        WaveVisualizer();
        explicit WaveVisualizer(const WaveVisualizerStyle &style);
        ~WaveVisualizer();

        // Theme application - inline
        void ApplyTheme(const WaveVisualizerStyle &style) { m_style = style; }
        
        void SetAudioStream(HSTREAM stream);
        void SetVolume(float volume);
        void SetMode(VisualizerMode mode);
        void SetScaleMultiplier(float multiplier);
        void SetVolumeAffectsScale(bool affects);

        void SetBoxSize(float width, float height);
        void SetBoxWidth(float width);
        void SetBoxHeight(float height);
        void SetOffset(float x, float y);
        void SetBarDimensions(float width, float gap);
        void SetBarWidth(float width);
        void SetBarGap(float gap);
        void SetBarCount(int count);
        void SetPadding(float top, float bottom);

        // Per-mode scaling
        void SetOscilloscopeScale(float scaleX, float scaleY);
        void SetSpectrumScale(float scaleX, float scaleY);

        VisualizerMode GetMode() const { return m_style.Mode; }
        bool IsActive() const { return m_stream != 0; }
        const WaveVisualizerStyle &GetStyle() const { return m_style; }

        void Draw(float width = 0.0f);
        void Reset();

    private:
        void ProcessAudioData();
        void ProcessWaveform();
        void UpdateSpectrumPeaks();

        void DrawBackground(const ImVec2 &pos, const ImVec2 &size);
        void DrawGrid(const ImVec2 &pos, const ImVec2 &size);
        void DrawOscilloscope(const ImVec2 &pos, const ImVec2 &size);
        void DrawSpectrum(const ImVec2 &pos, const ImVec2 &size);
        void DrawPlaceholder(const ImVec2 &pos, const ImVec2 &size);
        void DrawBorder(const ImVec2 &pos, const ImVec2 &size);

        static constexpr int FFT_SIZE = 256;
        std::vector<float> m_fftData;
        std::vector<float> m_waveformData;
        std::vector<float> m_spectrumPeaks;
        std::vector<float> m_smoothSpectrum;
        std::vector<float> m_pcmData;

        WaveVisualizerStyle m_style;
        HSTREAM m_stream = 0;
        float m_volume = 1.0f;
        float m_customWidth = 0.0f;
        bool m_hasData = false;
    };

} // namespace moosic