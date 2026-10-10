# psp.cmake - PlayStation Portable (Allegrex) build branch for OptiCraft.
cmake_minimum_required(VERSION 3.21)

include(${CMAKE_SOURCE_DIR}/cmake/SourceSelection.cmake)

set(MC_LOG_LEVEL "0" CACHE STRING "Unified diagnostic verbosity: 0=off, 1=info, 2=debug, 3=trace")
set_property(CACHE MC_LOG_LEVEL PROPERTY STRINGS 0 1 2 3)

# SDK roots
if(NOT DEFINED PSPDEV)
    if(DEFINED ENV{PSPDEV})
        set(PSPDEV "$ENV{PSPDEV}")
    else()
        set(PSPDEV "/usr/local/pspdev")
    endif()
endif()

message(STATUS "PSP build: PSPDEV=${PSPDEV}")

# Enable ccache for fast compilation if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "PSP build: Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

# Collect common and PSP platform sources recursively
mcbeta_collect_platform_sources(PSP_SOURCES psp)
mcbeta_exclude_remote_stats_sources(PSP_SOURCES)

# Minizip sources
set(PSP_MINIZIP_SOURCES
    "${CMAKE_SOURCE_DIR}/external/zlib/contrib/minizip/ioapi.c"
    "${CMAKE_SOURCE_DIR}/external/zlib/contrib/minizip/unzip.c"
)
list(APPEND PSP_SOURCES ${PSP_MINIZIP_SOURCES})
set_source_files_properties(${PSP_MINIZIP_SOURCES}
    PROPERTIES COMPILE_DEFINITIONS USE_FILE32API
)

# Platform backends
mcbeta_select_platform_backends(PSP_SOURCES PSP GL PSP)

# Exclude unused network code
mcbeta_exclude_sources(PSP_SOURCES "[/\\]java[/\\]JavaNetwork\\.cpp$")

# Target executable
add_executable(OptiCraft ${PSP_SOURCES})

set_target_properties(OptiCraft PROPERTIES
    SUFFIX ".elf"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
if(CCACHE_PROGRAM)
    set_target_properties(OptiCraft PROPERTIES
        C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
        CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
    )
endif()

target_include_directories(OptiCraft PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/pc"
    "${CMAKE_SOURCE_DIR}/src/psp"
    "${CMAKE_SOURCE_DIR}/src/net/minecraft/src"
    "${CMAKE_SOURCE_DIR}/src/mods"
    "${PSPDEV}/psp/include"
    "${PSPDEV}/psp/include/SDL2"
    "${PSPDEV}/psp/sdk/include"
    "${CMAKE_SOURCE_DIR}/external/stb"
    "${CMAKE_SOURCE_DIR}/external/miniaudio"
    "${CMAKE_SOURCE_DIR}/external/zlib/contrib/minizip"
)

target_compile_definitions(OptiCraft PRIVATE
    PSP=1
    __PSP__=1
    PSP_PLATFORM=1
    PLATFORM_PSP=1
    _PSP_FW_VERSION=600
    NO_SOUND=1
    MC_LOG_LEVEL=1
)

target_compile_options(OptiCraft PRIVATE
    -O2
    -pipe
    $<$<COMPILE_LANGUAGE:CXX>:-frtti>
    -fno-math-errno
    -fno-trapping-math
)

target_link_directories(OptiCraft PRIVATE
    "${PSPDEV}/psp/lib"
    "${PSPDEV}/psp/sdk/lib"
)

target_link_libraries(OptiCraft PRIVATE
    -Wl,-zmax-page-size=128
    SDL2main
    SDL2
    GL
    GLU
    pspvram
    pspaudio
    pspvfpu
    pspdisplay
    pspgu
    pspge
    psphprm
    pspctrl
    psppower
    atomic
    z
    m
    stdc++
)

# Generate EBOOT.PBP target
include("${PSPDEV}/psp/share/CreatePBP.cmake")
create_pbp_file(
    TARGET OptiCraft
    TITLE "OptiCraft Heritage"
    MEMSIZE 1
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/psp"
)
