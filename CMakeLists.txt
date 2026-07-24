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
    src/UI/Data/SettingsDataModel.cpp

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
    src/UI/Widgets/TrackSearchBar.cpp
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

# STB
set(STB_DIR ${CMAKE_SOURCE_DIR}/thirdparty/stb)
set(STB_DEPRECATED_DIR ${STB_DIR}/deprecated)

# nlohmann_json
set(NLOHMANN_JSON_DIR ${CMAKE_SOURCE_DIR}/thirdparty/nlohmann_json)

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
        ${STB_DIR}
        ${STB_DEPRECATED_DIR}
        ${NLOHMANN_JSON_DIR}/include  # nlohmann_json include directory
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

    # Require SDL2 version 2.30 or newer from the system
    find_package(SDL2 2.30 REQUIRED CONFIG)

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


# =============================================================================
# Native File Dialog Extended
# =============================================================================

target_link_libraries(
    MOOSIC_PLAYER
    PRIVATE
        nfd
)

# =============================================================================
# nlohmann_json - Header-only library (no linking required)
# =============================================================================

# nlohmann_json is header-only, so we just need to ensure the include
# directory is added (already done in target_include_directories above).
# If you need to use it in your source files, just include:
#   #include <nlohmann/json.hpp>

# Optional: If you want to use the nlohmann_json library via a target
# for better dependency management, you can create an interface target:
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${NLOHMANN_JSON_DIR}/include)

# Then link it to your target:
target_link_libraries(
    MOOSIC_PLAYER
    PRIVATE
        nlohmann_json
)

# This approach is cleaner and more modern CMake style.

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
message(STATUS "  ImGui             : ${IMGUI_DIR}")
message(STATUS "  nlohmann_json     : ${NLOHMANN_JSON_DIR}")
message(STATUS "========================================")
message(STATUS "")