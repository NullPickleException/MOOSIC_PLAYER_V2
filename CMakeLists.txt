cmake_minimum_required(VERSION 3.20)

project(
    MOOSIC_PLAYER_V2
    VERSION 1.0.0
    LANGUAGES CXX
)

# =============================================================================
# C++ Standard
# =============================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================================================================
# Compiler Warnings
# =============================================================================

if(MSVC)
    add_compile_options(/W4 /permissive- /Wv:18)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# =============================================================================
# Application Sources
# =============================================================================

set(APP_SOURCES
    src/main.cpp
    
    src/Core/Application.cpp
    src/Core/Input/InputManager.cpp
    
    src/Models/MusicLibrary.cpp
    src/Models/MusicTrack.cpp

    src/Services/DirectoryScanner.cpp
    src/Services/SavingSystem.cpp
    src/Services/AudioEngine.cpp
    src/Services/PlaybackController.cpp
    src/Services/ImageLoader.cpp

    src/Services/Metadata/MetadataReader.cpp
    src/Services/Metadata/Mp3MetadataParser.cpp
    src/Services/Metadata/FlacMetadataParser.cpp
    src/Services/Metadata/Mp4MetadataParser.cpp
    src/Services/Metadata/OggMetadataParser.cpp
    src/Services/Metadata/WavMetadataParser.cpp
    src/Services/Metadata/AiffMetadataParser.cpp
    src/Services/Metadata/WavPackMetadataParser.cpp
    
    src/UI/UI.cpp

    src/UI/Data/LibraryDataModel.cpp
    src/UI/Data/DirectoryDataModel.cpp
    src/UI/Data/PlaylistDataModel.cpp

    src/UI/Layouts/MainLayout.cpp
    src/UI/Layouts/SidebarLeftLayout.cpp
    src/UI/Layouts/CompactLayout.cpp
    src/UI/Layouts/MiniPlayerLayout.cpp
    src/UI/Layouts/TheaterLayout.cpp
    src/UI/Layouts/StandardArtLeftLayout.cpp
    
    src/UI/Windows/WindowContentPanel.cpp
    src/UI/Windows/LibraryWindow.cpp
    src/UI/Windows/PlaylistWindow.cpp
    src/UI/Windows/DirectoryWindow.cpp
    src/UI/Windows/SettingsWindow.cpp

    src/UI/Widgets/PlayerBar/IPlayerBar.cpp
    src/UI/Widgets/PlayerBar/StandardPlayerBar.cpp
    src/UI/Widgets/PlayerBar/CompactPlayerBar.cpp
    src/UI/Widgets/PlayerBar/StandardArtLeftPlayerBar.cpp
    src/UI/Widgets/PlayerBar/SidePlayerBar.cpp
    src/UI/Widgets/PlayerBar/MiniPlayerBar.cpp
    src/UI/Widgets/PlayerBar/TheaterPlayerBar.cpp
    src/UI/Widgets/TitleBar/TitleBar.cpp    
    src/UI/Widgets/TrackTable.cpp
    src/UI/Widgets/AlbumArtLightBox.cpp
    src/UI/Widgets/AlbumArtBox.cpp
    src/UI/Widgets/WaveVisualizer.cpp

)

# =============================================================================
# Dear ImGui
# =============================================================================

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

# =============================================================================
# Third-party Libraries - Platform Detection
# =============================================================================

if(WIN32)
    set(PLATFORM_DIR "windows")
    set(PLATFORM_DEFINE MOOSIC_PLATFORM_WINDOWS)
    set(SDL2_LIB_SUBDIR "x64")
elseif(APPLE)
    set(PLATFORM_DIR "macos")
    set(PLATFORM_DEFINE MOOSIC_PLATFORM_MACOS)
elseif(UNIX)
    set(PLATFORM_DIR "linux")
    set(PLATFORM_DEFINE MOOSIC_PLATFORM_LINUX)
endif()

# =============================================================================
# Third-party Libraries - Paths
# =============================================================================

# SDL2
set(SDL2_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/SDL2/${PLATFORM_DIR})

# BASS
set(BASS_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/BASS)

# FFmpeg
set(FFMPEG_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/ffmpeg/${PLATFORM_DIR})

# STB
set(STB_DIR ${CMAKE_SOURCE_DIR}/thirdparty/stb)
set(STB_DEPRECATED_DIR ${STB_DIR}/deprecated)

# TagLib
set(TAGLIB_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/taglib-2.3)

# =============================================================================
# Native File Dialog Extended
# =============================================================================

add_subdirectory(thirdparty/nativefiledialog-extended)

# =============================================================================
# Executable
# =============================================================================

add_executable(
    MOOSIC_PLAYER
    ${APP_SOURCES}
    ${IMGUI_SOURCES}
)

# =============================================================================
# Include Directories
# =============================================================================

target_include_directories(
    MOOSIC_PLAYER
    PRIVATE
        src
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${SDL2_ROOT}/include
        ${BASS_ROOT}/include
        ${FFMPEG_ROOT}/include
        ${STB_DIR}
        ${STB_DEPRECATED_DIR}
)

# =============================================================================
# Platform-Specific Linking
# =============================================================================

# SDL2
if(WIN32)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${SDL2_ROOT}/lib/${SDL2_LIB_SUBDIR}/SDL2.lib
            ${SDL2_ROOT}/lib/${SDL2_LIB_SUBDIR}/SDL2main.lib
    )

    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL2_ROOT}/lib/${SDL2_LIB_SUBDIR}/SDL2.dll
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

elseif(APPLE)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${SDL2_ROOT}/SDL2.framework
    )

elseif(UNIX)
    find_package(SDL2 REQUIRED)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            SDL2::SDL2
    )
endif()

# BASS
if(WIN32)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bass.lib
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bass_aac.lib
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bassflac.lib
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bassopus.lib
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/basswma.lib
    )

    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bass.dll
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bass_aac.dll
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bassflac.dll
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/bassopus.dll
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/x64/basswma.dll
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

elseif(APPLE)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/libbass.dylib
    )

elseif(UNIX)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${BASS_ROOT}/lib/${PLATFORM_DIR}/libbass.so
    )
endif()

# FFmpeg
if(WIN32)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${FFMPEG_ROOT}/lib/avformat.lib
            ${FFMPEG_ROOT}/lib/avcodec.lib
            ${FFMPEG_ROOT}/lib/avutil.lib
            ${FFMPEG_ROOT}/lib/swresample.lib
    )

    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${FFMPEG_ROOT}/bin/avformat-62.dll
            ${FFMPEG_ROOT}/bin/avcodec-62.dll
            ${FFMPEG_ROOT}/bin/avutil-60.dll
            ${FFMPEG_ROOT}/bin/swresample-6.dll
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

elseif(APPLE)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${FFMPEG_ROOT}/lib/libavformat.dylib
            ${FFMPEG_ROOT}/lib/libavcodec.dylib
            ${FFMPEG_ROOT}/lib/libavutil.dylib
            ${FFMPEG_ROOT}/lib/libswresample.dylib
    )

elseif(UNIX)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${FFMPEG_ROOT}/lib/libavformat.so
            ${FFMPEG_ROOT}/lib/libavcodec.so
            ${FFMPEG_ROOT}/lib/libavutil.so
            ${FFMPEG_ROOT}/lib/libswresample.so
    )
endif()

# =============================================================================
# TagLib (from thirdparty/taglib-2.3/windows/) - Shared (DLL) build
# =============================================================================

if(WIN32)
    # Determine architecture
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(TAGLIB_VARIANT "taglib_x64-windows")
    else()
        set(TAGLIB_VARIANT "taglib_x86-windows")
    endif()
    
    # Add TagLib include directory
    target_include_directories(
        MOOSIC_PLAYER
        PRIVATE
            ${TAGLIB_ROOT}/windows/${TAGLIB_VARIANT}/include
    )

    # Determine Debug/Release library path
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(TAGLIB_LIB_DIR ${TAGLIB_ROOT}/windows/${TAGLIB_VARIANT}/debug/lib)
    else()
        set(TAGLIB_LIB_DIR ${TAGLIB_ROOT}/windows/${TAGLIB_VARIANT}/lib)
    endif()

    # Link TagLib (import library for DLL)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${TAGLIB_LIB_DIR}/tag.lib
    )

    # Copy TagLib DLL to output directory
    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TAGLIB_ROOT}/windows/${TAGLIB_VARIANT}/bin/tag.dll
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

    # No TAGLIB_STATIC needed - this is a shared (DLL) build
endif()

# Native File Dialog Extended
target_link_libraries(
    MOOSIC_PLAYER
    PRIVATE
        nfd
)

# =============================================================================
# Platform Defines
# =============================================================================

target_compile_definitions(
    MOOSIC_PLAYER
    PRIVATE
        ${PLATFORM_DEFINE}
        $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>
)

# =============================================================================
# Configuration Summary
# =============================================================================

message(STATUS "")
message(STATUS "========================================")
message(STATUS " MOOSIC PLAYER Configuration")
message(STATUS "========================================")
message(STATUS "  C++ Standard      : ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type        : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform          : ${PLATFORM_DIR}")
message(STATUS "  SDL2              : ${SDL2_ROOT}")
message(STATUS "  BASS              : ${BASS_ROOT}")
message(STATUS "  FFmpeg            : ${FFMPEG_ROOT}")
message(STATUS "  ImGui             : ${IMGUI_DIR}")

if(WIN32)
    message(STATUS "  TagLib Variant    : ${TAGLIB_VARIANT}")
    message(STATUS "  TagLib Include    : ${TAGLIB_ROOT}/windows/${TAGLIB_VARIANT}/include")
    message(STATUS "  TagLib Library    : ${TAGLIB_LIB_DIR}/tag.lib")
    message(STATUS "  TagLib Type       : Shared (DLL)")
endif()

message(STATUS "========================================")
message(STATUS "")