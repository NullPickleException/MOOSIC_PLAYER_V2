cmake_minimum_required(VERSION 3.20)

# =============================================================================
# Project
# =============================================================================

project(
    MOOSIC_PLAYER_V2
    VERSION 1.0.0
    DESCRIPTION "Cross-platform desktop music player"
    LANGUAGES CXX
)

# =============================================================================
# C++ Standard
# =============================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================================================================
# Compiler Warnings
# =============================================================================

if(MSVC)

    add_compile_options(
        /W4
        /permissive-
    )

else()

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )

endif()

# =============================================================================
# Source Files
# =============================================================================

set(SOURCES

    src/main.cpp

)

# =============================================================================
# Executable
# =============================================================================

add_executable(

    MOOSIC_PLAYER

    ${SOURCES}

)

# =============================================================================
# Include Directories
# =============================================================================

target_include_directories(

    MOOSIC_PLAYER

    PRIVATE

        src

)

# =============================================================================
# SDL2
# =============================================================================

if(WIN32)

    set(SDL2_ROOT
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2/windows"
    )

elseif(APPLE)

    set(SDL2_ROOT
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2/macos"
    )

elseif(UNIX)

    set(SDL2_ROOT
        "${CMAKE_SOURCE_DIR}/thirdparty/SDL2/linux"
    )

endif()

target_include_directories(

    MOOSIC_PLAYER

    PRIVATE

        "${SDL2_ROOT}/include"

)

# =============================================================================
# SDL2 Linking
# =============================================================================

if(WIN32)

    target_link_libraries(

        MOOSIC_PLAYER

        PRIVATE

            "${SDL2_ROOT}/lib/x64/SDL2.lib"
            "${SDL2_ROOT}/lib/x64/SDL2main.lib"

    )

    # Copy SDL2.dll next to the executable after build
    add_custom_command(

        TARGET MOOSIC_PLAYER POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_if_different

            "${SDL2_ROOT}/lib/x64/SDL2.dll"
            "$<TARGET_FILE_DIR:MOOSIC_PLAYER>"

    )

elseif(APPLE)

    # SDL2.framework
    target_link_libraries(

        MOOSIC_PLAYER

        PRIVATE

            "${SDL2_ROOT}/SDL2.framework"

    )

elseif(UNIX)

    #
    # Linux
    #
    # SDL2 is built from the vendored source located in:
    #
    # thirdparty/SDL2/linux
    #

    add_subdirectory(
        thirdparty/SDL2/linux
    )

    target_link_libraries(

        MOOSIC_PLAYER

        PRIVATE

            SDL2::SDL2

    )

endif()

# =============================================================================
# Platform Definitions
# =============================================================================

if(WIN32)

    target_compile_definitions(

        MOOSIC_PLAYER

        PRIVATE

        MOOSIC_PLATFORM_WINDOWS

    )

elseif(APPLE)

    target_compile_definitions(

        MOOSIC_PLAYER

        PRIVATE

        MOOSIC_PLATFORM_MACOS

    )

elseif(UNIX)

    target_compile_definitions(

        MOOSIC_PLAYER

        PRIVATE

        MOOSIC_PLATFORM_LINUX

    )

endif()