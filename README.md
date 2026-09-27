# OptiCraft Heritage Edition

OptiCraft Heritage is a heavily modified, clean-room C++ implementation of classic Minecraft-era gameplay designed around portability, low-end hardware, and console-specific optimization.

This repository is not a line-for-line source translation. The runtime, platform abstraction layers, rendering paths, input backends, storage systems, user interface, asset loading, memory policies, and console support have been extensively reworked for the needs of this project.

---

## 🌟 Project Goals

- **Cross-platform portability**: Full native support for PC (Linux/Windows), PlayStation 2, Nintendo Wii, and PlayStation Portable (PSP).
- **Faithful classic experience**: Preserve classic gameplay feel, physics, and world generation while allowing ergonomic platform adaptations.
- **Extreme hardware constraints**: Engineered to run smoothly on systems with strict memory and CPU limits (such as the PSP's 32MB/64MB RAM and 333MHz MIPS CPU, and PS2's 32MB RAM).
- **Clean modular architecture**: Platform-specific code is isolated in dedicated backend modules (`src/psp/`, `src/ps2/`, `src/wii/`, `src/pc/`) without polluting shared game logic.
- **Production-ready C++17 codebase**: Debuggable, maintainable, and built with modern C++ standards.

---

## 🎮 Supported Targets

### 1. PlayStation Portable (PSP)
The PSP port features a dedicated MIPS/PSPSDK backend with custom graphics, audio, input, and memory tuning:
- **Rendering**: Custom OpenGL display list emulation and vertex caching adapted to the PSP Graphic Engine (GE).
- **Controls & Ergonomics**:
  - **Analog Stick**: Smooth 360° player movement (Walk / Strafe).
  - **Action Buttons (△, □, ✕, ○)**: Responsive camera look with exponential smoothing and acceleration ramping.
  - **R Trigger**: Attack / Mine (Primary Action).
  - **L Trigger**: Use / Place Block (Secondary Action).
  - **D-Pad**: Hotbar cycling (Left / Right), Jump (Up), Sneak (Down).
  - **Menus & Inventories**: Full virtual cursor support with analog nub, fast slot navigation, and trigger scroll (L/R).
- **Memory Footprint**: Strict chunk streaming budgets and residency management to operate within PSP RAM limits.
- **Installation Path**:
  ```text
  ms0:/PSP/GAME/OptiCraft/EBOOT.PBP
  ms0:/PSP/GAME/OptiCraft/assets.pak
  ```

### 2. PlayStation 2 (PS2)
Native PS2SDK platform backend featuring GS-specific rendering, console memory policies, asynchronous asset loading, platform storage (Memory Card / USB), controller input, and VU-assisted terrain pipelines.
- **Installation Path**:
  ```text
  mass:/OptiCraftHeritage/
  ```

### 3. Nintendo Wii
Native devkitPPC/libogc backend using GX hardware rendering, Wiimote / Classic Controller / GameCube pad inputs, and 16:9 widescreen correction.
- **Installation Path**:
  ```text
  apps/OptiCraft/
  ```

### 4. PC (Windows & Linux)
Desktop build utilizing SDL2, modern OpenGL, and the unified platform abstraction layer. A dedicated 32-bit legacy profile is provided for older SSE2-class hardware and legacy OpenGL drivers.

---

## 📂 Source Layout

```text
src/
  client/       Shared client loop, initialization, and player controllers
  java/         Java compatibility runtime helpers and math wrappers
  net/          Core Minecraft game implementation (blocks, items, entities, world, rendering)
  platform/     Abstract platform interfaces (Audio, Input, Storage, RenderAPI, Tuning)
  pc/           Desktop SDL2/OpenGL platform backends
  psp/          PlayStation Portable platform implementation (MIPS, PspPadState, Sound, Memory)
  ps2/          PlayStation 2 platform implementation (PS2SDK, GS, VU1, Memory Card)
  wii/          Nintendo Wii platform implementation (devkitPPC, GX, Wiimote)
  mods/         Built-in modular mod engine (e.g. Rei's Minimap, skin loader)
  util/         Shared compression, hashing, and string utilities

cmake/          Toolchain definitions and cross-compilation configurations
external/       Third-party dependencies (stb, fdlibm, etc.)
```

---

## 🛠️ Building

CMake 3.21 or newer is required. Presets are defined in `CMakePresets.json`.

### Building for PlayStation Portable (PSP)

#### On Windows (via WSL & PSPSDK):
Run the automated build script:
```bat
build psp.bat
```
This invokes `build_psp.sh` inside WSL using the `pspdev` toolchain, compiles the C++ codebase, and packages `EBOOT.PBP`.

#### On Linux / WSL directly:
```bash
cmake -B build/psp -DCMAKE_TOOLCHAIN_FILE=$PSPDEV/psp/share/pspdev.cmake -DPLATFORM_TARGET=PSP -DCMAKE_BUILD_TYPE=Release
cmake --build build/psp -- -j$(nproc)
```

### Building for Desktop PC

```bash
# Debug build
cmake --preset gcc-debug
cmake --build --preset gcc-debug

# Optimized Release build
cmake --preset gcc-release
cmake --build --preset gcc-release
```

#### 32-bit / Legacy PC (Windows MSYS2)
```bat
build_gcc32.bat release
```

### Building for PlayStation 2

```bash
cmake --preset ps2-release
cmake --build --preset ps2-release
```

### Building for Nintendo Wii

```bash
cmake --preset wii-release
cmake --build --preset wii-release
```

---

## 📜 Clean-Room Implementation & Disclaimer

OptiCraft Heritage is developed as a clean-room implementation. The project code is independently implemented in C/C++ and is heavily modified around its own runtime and platform architecture.

The project does not rely on original proprietary game source code as part of its implementation. Compatibility-oriented behavior is reproduced from observable behavior, documented formats, protocol specifications, and independently developed interfaces.

*OptiCraft Heritage is an independent homebrew project and is not affiliated with, endorsed by, or sponsored by Mojang Studios or Microsoft.*

---

## 📄 License & Third-Party Software

Third-party libraries are located under `external/` and retain their respective open-source licenses. Review third-party licenses independently before redistributing binaries.
