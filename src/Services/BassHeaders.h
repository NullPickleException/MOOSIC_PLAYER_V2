//==============================================================================
// Services/BassHeaders.h
//==============================================================================
// Platform-agnostic BASS audio library wrapper.
// Windows : bass + aac + flac + opus + wma
// Linux   : bass + aac + flac + opus
// macOS   : bass (CoreAudio handles codecs natively)
//==============================================================================

#pragma once

//------------------------------------------------------------------------------
// Core BASS (all platforms)
//------------------------------------------------------------------------------
#include <bass.h>

//------------------------------------------------------------------------------
// Platform-specific add-ons
//------------------------------------------------------------------------------
#if defined(_WIN32)
    // Windows: all add-ons available
    #include <bass_aac.h>
    #include <bassflac.h>
    #include <bassopus.h>
    #include <basswma.h>

#elif defined(__APPLE__)
    // macOS: CoreAudio provides AAC/MP3/ALAC codecs built-in.
    // Add-on headers exist but are optional for metadata reading.
    // Uncomment if you have the dylibs:
    // #include <bassflac.h>
    // #include <bassopus.h>

#else // Linux
    // Linux: add-ons for AAC, FLAC, OPUS (WMA not available)
    #include <bass_aac.h>
    #include <bassflac.h>
    #include <bassopus.h>
#endif