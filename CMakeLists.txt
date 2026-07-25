cmake_minimum_required(VERSION 3.20)

project(
    MOOSIC_PLAYER_V2
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /Wv:18)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

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
# Architecture Selection (x64 or x86)
# =============================================================================

if(NOT DEFINED CMAKE_SIZEOF_VOID_P)
    message(FATAL_ERROR "CMAKE_SIZEOF_VOID_P not set. Run cmake with -A x64 or -A Win32")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BASS_ARCH "x64")
    set(BASS_ARCH_DIR "x64")
    message(STATUS "  Architecture      : x64 (64-bit)")
else()
    set(BASS_ARCH "x86")
    set(BASS_ARCH_DIR "x86")
    message(STATUS "  Architecture      : x86 (32-bit)")
endif()

# =============================================================================
# Platform Detection
# =============================================================================

if(WIN32)
    set(PLATFORM_DIR "windows")
    set(PLATFORM_DEFINE MOOSIC_PLATFORM_WINDOWS)
elseif(APPLE)
    set(PLATFORM_DIR "macos")
    set(PLATFORM_DEFINE MOOSIC_PLATFORM_MACOS)
elseif(UNIX)
    set(PLATFORM_DIR "linux")
    set(PLATFORM_DEFINE MOOSIC_PLATFORM_LINUX)
endif()

# =============================================================================
# Third-party Library Paths
# =============================================================================

set(SDL2_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/SDL2/${PLATFORM_DIR})
set(BASS_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/BASS)
set(STB_DIR ${CMAKE_SOURCE_DIR}/thirdparty/stb)
set(STB_DEPRECATED_DIR ${STB_DIR}/deprecated)
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
        ${BASS_ROOT}/${PLATFORM_DIR}/bass24/c
        ${BASS_ROOT}/${PLATFORM_DIR}/bass_aac24/c
        ${BASS_ROOT}/${PLATFORM_DIR}/bassflac24/c
        ${BASS_ROOT}/${PLATFORM_DIR}/bassopus24/c
        ${BASS_ROOT}/${PLATFORM_DIR}/basswm24/c
        ${STB_DIR}
        ${STB_DEPRECATED_DIR}
        ${NLOHMANN_JSON_DIR}/include
)

# =============================================================================
# SDL2 - Platform-Specific
# =============================================================================

if(WIN32)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${SDL2_ROOT}/lib/${BASS_ARCH_DIR}/SDL2.lib
            ${SDL2_ROOT}/lib/${BASS_ARCH_DIR}/SDL2main.lib
    )

    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL2_ROOT}/lib/${BASS_ARCH_DIR}/SDL2.dll
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

elseif(APPLE)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${SDL2_ROOT}/SDL2.framework
    )

elseif(UNIX)
    find_package(SDL2 2.30 REQUIRED CONFIG)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            SDL2::SDL2
    )
endif()

# =============================================================================
# BASS - Platform & Architecture Aware
# =============================================================================

if(WIN32)
    # Windows: c/x64/ for 64-bit libs, c/ for 32-bit libs
    if(BASS_ARCH STREQUAL "x64")
        set(BASS_LIB_SUBDIR "c/x64")
    else()
        set(BASS_LIB_SUBDIR "c")
    endif()

    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${BASS_ROOT}/${PLATFORM_DIR}/bass24/${BASS_LIB_SUBDIR}/bass.lib
            ${BASS_ROOT}/${PLATFORM_DIR}/bass_aac24/${BASS_LIB_SUBDIR}/bass_aac.lib
            ${BASS_ROOT}/${PLATFORM_DIR}/bassflac24/${BASS_LIB_SUBDIR}/bassflac.lib
            ${BASS_ROOT}/${PLATFORM_DIR}/bassopus24/${BASS_LIB_SUBDIR}/bassopus.lib
            ${BASS_ROOT}/${PLATFORM_DIR}/basswm24/${BASS_LIB_SUBDIR}/basswma.lib
    )

    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BASS_ROOT}/${PLATFORM_DIR}/bass24/${BASS_ARCH_DIR}/bass.dll
            ${BASS_ROOT}/${PLATFORM_DIR}/bass_aac24/${BASS_ARCH_DIR}/bass_aac.dll
            ${BASS_ROOT}/${PLATFORM_DIR}/bassflac24/${BASS_ARCH_DIR}/bassflac.dll
            ${BASS_ROOT}/${PLATFORM_DIR}/bassopus24/${BASS_ARCH_DIR}/bassopus.dll
            ${BASS_ROOT}/${PLATFORM_DIR}/basswm24/${BASS_ARCH_DIR}/basswma.dll
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

elseif(APPLE)
    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${BASS_ROOT}/macos/bass24/libbass.dylib
    )
    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BASS_ROOT}/macos/bass24/libbass.dylib
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
    )

elseif(UNIX)
    if(BASS_ARCH STREQUAL "x64")
        set(BASS_LINUX_ARCH "x86_64")
    else()
        set(BASS_LINUX_ARCH "x86")
    endif()

    target_link_libraries(
        MOOSIC_PLAYER
        PRIVATE
            ${BASS_ROOT}/linux/bass24/libs/${BASS_LINUX_ARCH}/libbass.so
            ${BASS_ROOT}/linux/bass_aac24/libs/${BASS_LINUX_ARCH}/libbass_aac.so
            ${BASS_ROOT}/linux/bassflac24/libs/${BASS_LINUX_ARCH}/libbassflac.so
            ${BASS_ROOT}/linux/bassopus24/libs/${BASS_LINUX_ARCH}/libbassopus.so
    )
    add_custom_command(
        TARGET MOOSIC_PLAYER POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BASS_ROOT}/linux/bass24/libs/${BASS_LINUX_ARCH}/libbass.so
            ${BASS_ROOT}/linux/bass_aac24/libs/${BASS_LINUX_ARCH}/libbass_aac.so
            ${BASS_ROOT}/linux/bassflac24/libs/${BASS_LINUX_ARCH}/libbassflac.so
            ${BASS_ROOT}/linux/bassopus24/libs/${BASS_LINUX_ARCH}/libbassopus.so
            $<TARGET_FILE_DIR:MOOSIC_PLAYER>
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
# nlohmann_json - Header-only
# =============================================================================

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${NLOHMANN_JSON_DIR}/include)

target_link_libraries(
    MOOSIC_PLAYER
    PRIVATE
        nlohmann_json
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

message(STATUS "")
message(STATUS "========================================")
message(STATUS " MOOSIC PLAYER Configuration")
message(STATUS "========================================")
message(STATUS "  C++ Standard      : ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type        : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Platform          : ${PLATFORM_DIR}")
message(STATUS "  Architecture      : ${BASS_ARCH}")
message(STATUS "  SDL2              : ${SDL2_ROOT}")
message(STATUS "  BASS              : ${BASS_ROOT}")
message(STATUS "  ImGui             : ${IMGUI_DIR}")
message(STATUS "  nlohmann_json     : ${NLOHMANN_JSON_DIR}")
message(STATUS "========================================")
message(STATUS "")