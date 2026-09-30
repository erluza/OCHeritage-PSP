#!/bin/bash
set -e

export PSPDEV=/usr/local/pspdev
export PATH="$PSPDEV/bin:$PATH"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRC_DIR="${SCRIPT_DIR}"

# If running under WSL with sources on a Windows drive (/mnt/c/...),
# building in native Linux storage (/tmp or ~/.cache) avoids 9P filesystem latency
# and speeds up compilation by up to 5x-10x!
if [[ "${SRC_DIR}" == /mnt/* ]] && [ -z "$BUILD_DIR" ]; then
    BUILD_DIR="/tmp/opticraft_psp_build"
else
    BUILD_DIR="${BUILD_DIR:-${SRC_DIR}/build/psp}"
fi

echo "=== OptiCraft Heritage Edition: Building for PSP ==="
echo "Source directory: ${SRC_DIR}"
echo "Build directory:  ${BUILD_DIR}"

# Configure ccache if present
if command -v ccache >/dev/null 2>&1; then
    echo "=== ccache detected: configuring cache settings ==="
    export CCACHE_SLOPPINESS=time_macros,include_file_mtime
    export CCACHE_COMPRESS=1
    export CCACHE_COMPRESSLEVEL=6
    export CCACHE_MAXSIZE=5G
    export CCACHE_BASEDIR="${SRC_DIR}"
    export CCACHE_NOHASHDIR=1
    ccache -s 2>/dev/null || true
fi

# Select CMake generator: prefer Ninja when available
CMAKE_GEN=()
if command -v ninja >/dev/null 2>&1; then
    echo "=== Ninja build generator detected ==="
    CMAKE_GEN=("-G" "Ninja")
fi

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

cmake "${SRC_DIR}" \
    "${CMAKE_GEN[@]}" \
    -DCMAKE_TOOLCHAIN_FILE="${PSPDEV}/psp/share/pspdev.cmake" \
    -DPLATFORM=PSP

cmake --build . --parallel $(nproc)

if command -v ccache >/dev/null 2>&1; then
    echo "=== ccache statistics after build ==="
    ccache -s || true
fi

echo "=== Copying EBOOT.PBP to project root and bin/psp ==="
mkdir -p "${SRC_DIR}/bin/psp"
cp -f "${BUILD_DIR}/bin/psp/EBOOT.PBP" "${SRC_DIR}/bin/psp/EBOOT.PBP" 2>/dev/null || cp -f "${BUILD_DIR}/EBOOT.PBP" "${SRC_DIR}/bin/psp/EBOOT.PBP" 2>/dev/null || true
cp -f "${SRC_DIR}/bin/psp/EBOOT.PBP" "${SRC_DIR}/EBOOT.PBP" 2>/dev/null || true

# Deploy to PPSSPP if user folder exists
PPSSPP_DIR="/mnt/c/Users/user/Documents/PPSSPP/PSP/GAME/OptiCraft"
if [ -d "$PPSSPP_DIR" ]; then
    echo "=== Deploying EBOOT.PBP to PPSSPP ($PPSSPP_DIR) ==="
    cp -f "${SRC_DIR}/EBOOT.PBP" "$PPSSPP_DIR/EBOOT.PBP" 2>/dev/null || true
fi

echo "=== Build Complete! ==="
ls -lh "${SRC_DIR}/EBOOT.PBP"
