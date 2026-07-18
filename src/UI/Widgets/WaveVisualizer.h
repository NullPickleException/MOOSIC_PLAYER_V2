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
        float BorderRounding = 1.0f;
        float BorderThickness = 4.0f;

        // Layout Offsets
        float OffsetX = 0.0f;
        float OffsetY = 0.0f;

        // Per-mode scaling factors
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
        float BarTopRounding = 3.0f;
        bool RoundBarTops = true;

        // Waveform Settings
        int WaveformSamples = 128;
        float WaveformLineWidth = 1.5f;
        bool EnableWaveformFill = true;

        // ──────────────────────────────────────────────
        // Audio Processing
        // ──────────────────────────────────────────────

        float SpectrumSensitivity = 2.5f;
        float HighFrequencyBoost = 5.0f;
        float FrequencyBoostCurve = 2.4f;
        float DynamicRange = 0.55f;
        float AttackSpeed = 0.95f;
        float ReleaseSpeed = 0.35f;
        float PeakDecay = 0.90f;
        float NoiseFloor = 0.02f;

        float NeighborSmoothing = 0.3f;
        bool EnableNeighborBlur = true;

        bool EnableSpringAnimation = false;
        float SpringStiffness = 0.25f;
        float SpringDamping = 0.8f;

        bool EnableAutoGain = true;
        float AutoGainSpeed = 0.95f;

        float ScaleMultiplier = 0.35f;
        bool VolumeAffectsScale = false;
        bool ClampToBounds = true;

        // ──────────────────────────────────────────────
        // Base Colors (used as fallback / simple mode)
        // ──────────────────────────────────────────────

        ImVec4 BackgroundColor      = ImVec4(0.04f, 0.04f, 0.06f, 1.0f);
        ImVec4 WaveformColor        = ImVec4(0.15f, 0.45f, 0.85f, 1.0f);
        ImVec4 WaveformFillColor    = ImVec4(0.08f, 0.25f, 0.50f, 0.15f);
        ImVec4 GridColor            = ImVec4(0.08f, 0.08f, 0.10f, 0.4f);
        ImVec4 BorderColor          = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
        ImVec4 PlaceholderColor     = ImVec4(0.30f, 0.30f, 0.35f, 0.6f);

        // ──────────────────────────────────────────────
        // Spectrum Color Ramp — "peak-aware" coloring
        // ──────────────────────────────────────────────
        // Bars transition from ColorLow (quiet) → ColorMid (medium) → ColorHigh (loud)
        // based on their current energy value (0.0 to 1.0)
        // ──────────────────────────────────────────────

        bool UseColorRamp           = true;     // Enable peak-based coloring
        ImVec4 SpectrumColorLow     = ImVec4(0.12f, 0.40f, 0.80f, 1.0f);   // Quiet bars (blue)
        ImVec4 SpectrumColorMid     = ImVec4(0.20f, 0.55f, 0.95f, 1.0f);   // Medium bars
        ImVec4 SpectrumColorHigh    = ImVec4(0.35f, 0.70f, 1.00f, 1.0f);   // Loud bars (bright)
        ImVec4 SpectrumColorPeak    = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);   // Peak dot color

        // Color ramp blend thresholds (0.0 - 1.0 range of bar energy)
        float ColorRampLowThreshold  = 0.0f;    // Below this = ColorLow
        float ColorRampMidThreshold  = 0.5f;    // Blend to ColorMid starts here
        float ColorRampHighThreshold = 0.85f;   // Blend to ColorHigh starts here

        // ──────────────────────────────────────────────
        // Frequency-based tinting (optional)
        // ──────────────────────────────────────────────
        // Low frequencies can be tinted one color, high frequencies another
        // ──────────────────────────────────────────────

        bool UseFrequencyTint       = false;
        ImVec4 LowFreqTint          = ImVec4(1.0f, 0.6f, 0.3f, 1.0f);    // Warm tint for bass
        ImVec4 HighFreqTint         = ImVec4(0.3f, 0.6f, 1.0f, 1.0f);    // Cool tint for treble
        float FrequencyTintBlend    = 0.3f;   // How much the tint affects the color (0 = none, 1 = full)

        // ──────────────────────────────────────────────
        // Legacy flat colors (used when UseColorRamp is false)
        // ──────────────────────────────────────────────

        ImVec4 SpectrumColor        = ImVec4(0.12f, 0.40f, 0.80f, 1.0f);
        ImVec4 SpectrumColorHighEnd = ImVec4(0.25f, 0.60f, 1.0f, 1.0f);  // Right-side bars (legacy)

        // ──────────────────────────────────────────────
        // Brightness boost for loud bars
        // ──────────────────────────────────────────────
        
        float BarBrightnessMin      = 0.35f;   // Minimum brightness multiplier
        float BarBrightnessMax      = 1.0f;    // Maximum brightness multiplier (at peak)

        // ──────────────────────────────────────────────
        // Grid & Misc
        // ──────────────────────────────────────────────

        VisualizerMode Mode = VisualizerMode::Spectrum;
        bool ShowGrid = false;
        int GridLinesHorizontal = 2;
        int GridLinesVertical = 4;
        bool ShowPeaks = false;

        // Waveform smoothing (legacy)
        float Smoothing = 0.4f;
    };

    class WaveVisualizer
    {
    public:
        WaveVisualizer();
        explicit WaveVisualizer(const WaveVisualizerStyle &style);
        ~WaveVisualizer();

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

        // Helper: compute bar color based on energy and frequency position
        ImVec4 ComputeBarColor(int bandIndex, int totalBands, float energy) const;

        static constexpr int FFT_SIZE = 256;
        std::vector<float> m_fftData;
        std::vector<float> m_waveformData;
        std::vector<float> m_spectrumPeaks;
        std::vector<float> m_smoothSpectrum;
        std::vector<float> m_pcmData;
        std::vector<float> m_springVelocity;
        float m_runningMax = 0.01f;

        WaveVisualizerStyle m_style;
        HSTREAM m_stream = 0;
        float m_volume = 1.0f;
        float m_customWidth = 0.0f;
        bool m_hasData = false;
    };

} // namespace moosic