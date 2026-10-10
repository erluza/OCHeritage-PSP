# OptiCraft Heritage Edition — PlayStation Portable (PSP)

[![Build PlayStation Portable](https://github.com/erluza/OCHeritage-PSP/actions/workflows/psp.yml/badge.svg)](https://github.com/erluza/OCHeritage-PSP/actions/workflows/psp.yml)
[![Platform](https://img.shields.io/badge/Platform-Sony%20PSP%20%2F%20PPSSPP-003791?logo=playstation)](https://github.com/erluza/OCHeritage-PSP)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![License](https://img.shields.io/badge/License-GPL%20v3-green.svg)](LICENSE)

*Read this in [English](#-english) | Leer en [Español](#-español)*

---

# 🇬🇧 English

## 📖 Overview

**OptiCraft Heritage Edition (PSP Port)** is an optimized, clean-room C++17 port of classic Minecraft-era gameplay specifically crafted for the **Sony PlayStation Portable (PSP)** and the **PPSSPP** emulator.

Built directly against the bare-metal **PSPSDK** and Allegrex MIPS architecture, this port brings the authentic classic sandbox experience to Sony's legendary handheld while strictly respecting its tight hardware limitations (MIPS R4000 @ 333 MHz, 32MB / 64MB RAM).

---

## ✨ Features & Optimizations

- **PS2-Parity 2D Heightmap World Generator**:
  Uses the lightweight 2D heightmap generator (`ChunkProviderGenerateLite`) and fast biome sampling (`WorldChunkManagerFast`), mirroring the generation of the PlayStation 2 edition. Replaces heavy 3D double-precision Perlin noise with single-precision float mathematics for ultra-fast chunk generation on MIPS without CPU stalls.
- **Optimized 256×256 Bounded Worlds**:
  Authentic console-sized worlds (16×16 chunks) with seamless edge physics. Outward velocity decomposition ensures the player can smoothly slide along world borders and walk back towards the center with zero friction, eliminating the classic "glue" or stuck sensation.
- **Custom Dual-Mode Control Layout**:
  - **Gameplay Mode**: Smooth analog nub movement, responsive face-button camera look with exponential ramp curves, quick hotbar cycling, and dedicated trigger actions.
  - **Menu Mode**: Dual navigation featuring both intuitive D-Pad grid jumping and a fast analog virtual pointer for inventories and crafting.
- **Auto-Jump Built-In**:
  Automatic single-block elevation step-up enabled by default, complete with an in-game toggle in **Heritage Options** and **Host Options**.
- **Fixed-Function 16-bit Depth Optimization**:
  Engineered specifically for the PSP Graphic Engine (GE) to avoid coplanar Z-fighting in 2D overlays, preserving vibrant full hearts, hunger icons, and pixel-perfect button glyphs.
- **Memory Footprint & Chunk Streaming**:
  Configured memory ring buffers and chunk load ceilings to guarantee rock-solid stability on both retail hardware and emulators.

---

## 🎮 Controller Layout

### Gameplay Controls

| Button | Action |
| :--- | :--- |
| **Analog Stick** | Walk / Strafe (360° Movement) |
| **△ (Triangle)** | Look Up |
| **✕ (Cross)** | Look Down |
| **□ (Square)** | Look Left |
| **○ (Circle)** | Look Right |
| **R Trigger** | Primary Action (Attack / Mine Block) |
| **L Trigger** | Secondary Action (Use / Place Block) |
| **D-Pad Up** | Jump |
| **D-Pad Down** | Sneak / Crouch |
| **D-Pad Left / Right** | Hotbar Item Selection (Previous / Next) |
| **START** | Pause Menu / Host Options |
| **SELECT** | Inventory / Crafting Menu |
| **R + SELECT** | Open Host Options Directly |

### Menu & Inventory Controls

| Button | Action |
| :--- | :--- |
| **D-Pad** | Navigate UI buttons and inventory slots |
| **Analog Stick** | Move virtual pointer cursor |
| **✕ (Cross)** | Select / Confirm / Left Click |
| **□ (Square)** | Split Stack / Right Click |
| **△ (Triangle)** | Quick-Move (Shift + Click) |
| **○ (Circle)** | Back / Cancel / Exit Menu |
| **L / R Triggers** | Scroll Container / Change Creative Tabs |

---

## 📥 Installation

### 1. Requirements
- A **PlayStation Portable** (PSP 1000*, 2000, 3000, Go, or Street) running custom firmware (PRO, ME, or ARK-4), a **PS Vita** with Adrenaline, or the **PPSSPP** emulator.
- *Note: On PSP-1000 (32MB RAM), limited 256×256 worlds are strongly recommended.*

### 2. File Placement
Copy the game folder to your Memory Stick under `PSP/GAME/`:

```text
ms0:/
 └── PSP/
      └── GAME/
           └── OptiCraft/
                ├── EBOOT.PBP
                └── assets.pak
```

- **PPSSPP Path (Windows)**:
  `C:\Users\<YourUser>\Documents\PPSSPP\PSP\GAME\OptiCraft\`
- **PPSSPP Path (Android)**:
  `/storage/emulated/0/PSP/GAME/OptiCraft/`

---

## 🛠️ Compiling from Scratch

You can compile OptiCraft for PSP using Linux, WSL2 (Windows), or Docker.

### Method A: Automated Build using Docker (Recommended)

The easiest and cleanest method requires only [Docker](https://www.docker.com/):

```bash
# Clone the repository
git clone https://github.com/erluza/OCHeritage-PSP.git
cd OCHeritage-PSP

# Run build using the official PSPSDK container
docker run --rm -v "$(pwd):/work" -w /work pspdev/pspdev:latest bash -c "./build_psp.sh"
```
The compiled `EBOOT.PBP` will be generated in the project root.

---

### Method B: Compiling on Windows with WSL2

1. **Install Ubuntu on WSL2**:
   Open PowerShell as Administrator:
   ```powershell
   wsl --install -d Ubuntu
   ```

2. **Install PSP Toolchain (PSPSDK)** inside WSL:
   ```bash
   sudo apt update
   sudo apt install -y build-essential cmake ninja-build ccache git python3 curl libreadline-dev libusb-dev
   
   # Download and install precompiled PSP toolchain or build via pspdev
   # Ensure PSPDEV is exported in your environment:
   echo 'export PSPDEV=/usr/local/pspdev' >> ~/.bashrc
   echo 'export PATH="$PSPDEV/bin:$PATH"' >> ~/.bashrc
   source ~/.bashrc
   ```

3. **Compile using the provided script**:
   From Windows PowerShell in the project directory, simply run:
   ```bat
   "build psp.bat"
   ```
   Or inside WSL:
   ```bash
   bash ./build_psp.sh
   ```

---

### Method C: Manual CMake Configuration (Linux / macOS)

If you already have `pspdev` installed:

```bash
export PSPDEV=/usr/local/pspdev
export PATH="$PSPDEV/bin:$PATH"

mkdir -p build/psp && cd build/psp

cmake ../.. \
    -DCMAKE_TOOLCHAIN_FILE="${PSPDEV}/psp/share/pspdev.cmake" \
    -DPLATFORM=PSP \
    -DCMAKE_BUILD_TYPE=Release

cmake --build . --parallel $(nproc)
```

The resulting `EBOOT.PBP` will be located at:
`build/psp/bin/psp/EBOOT.PBP`

---

# 🇪🇸 Español

## 📖 Descripción General

**OptiCraft Heritage Edition (Port PSP)** es un port limpio y altamente optimizado en C++17 de la era clásica de Minecraft, diseñado específicamente para la consola portátil **Sony PlayStation Portable (PSP)** y el emulador **PPSSPP**.

Desarrollado directamente sobre el **PSPSDK** nativo y la arquitectura Allegrex MIPS, este port traslada la experiencia sandbox clásica a la legendaria consola de Sony respetando estrictamente sus limitaciones de hardware (CPU MIPS R4000 a 333 MHz y 32MB / 64MB de memoria RAM).

---

## ✨ Características y Optimizaciones

- **Generador de Terreno 2D Heightmap (Paridad con PS2)**:
  Utiliza el generador de mapa de alturas (`ChunkProviderGenerateLite`) y muestreo rápido de biomas (`WorldChunkManagerFast`), exactamente igual a la versión de PlayStation 2. Reemplaza el pesado ruido 3D Perlin de doble precisión por matemáticas en coma flotante de precisión simple, logrando una generación de chunks instantánea sin congelamientos en la CPU MIPS.
- **Mundos Delimitados de 256×256 Optimizados**:
  Mundos auténticos de consola (16×16 chunks) con física de bordes suave. La descomposición de velocidad radial anula únicamente la componente de movimiento que intenta salir del mapa, permitiendo deslizarse por el borde y regresar hacia el interior con total fluidez, eliminando el clásico problema de quedarse "enganchado" o pegado en el límite.
- **Sistema de Control Dual Adaptado**:
  - **Modo En Juego**: Movimiento fluido en 360° con el joystick analógico, control de cámara suave mediante los botones frontales con curva de aceleración exponencial, cambio rápido de barra de acceso y gatillos de acción.
  - **Modo Menús**: Navegación combinada mediante cruceta direccional (salto entre botones) y puntero virtual analógico para inventarios y crafteo.
- **Salto Automático (Auto-Jump) Integrado**:
  Detección y subida automática de obstáculos de un bloque activada por defecto, con interruptor de activación/desactivación en las opciones de pausa (**Host Options**) y de sistema (**Heritage Options**).
- **Ajuste de Buffer de Profundidad de 16 bits**:
  Optimizado para el Graphic Engine (GE) de la PSP para evitar colisiones coplanares en el buffer de profundidad, asegurando corazones y comida con relleno visible y tipografías/íconos nítidos.
- **Presupuesto Estricto de Memoria**:
  Administración dinámica de memoria y streaming acotado de chunks para garantizar estabilidad total tanto en consolas reales como en emuladores.

---

## 🎮 Esquema de Controles

### Durante la Partida

| Botón | Acción |
| :--- | :--- |
| **Stick Analógico** | Caminar / Desplazarse (Movimiento 360°) |
| **△ (Triángulo)** | Mirar hacia arriba |
| **✕ (Cruz)** | Mirar hacia abajo |
| **□ (Cuadrado)** | Mirar hacia la izquierda |
| **○ (Círculo)** | Mirar hacia la derecha |
| **Gatillo R** | Acción Principal (Atacar / Romper bloque) |
| **Gatillo L** | Acción Secundaria (Usar / Colocar bloque) |
| **Cruceta Arriba** | Saltar |
| **Cruceta Abajo** | Agacharse / Sigilo |
| **Cruceta Izq / Der** | Cambiar objeto en la barra rápida |
| **START** | Menú de Pausa / Opciones de Anfitrión |
| **SELECT** | Inventario / Crafteo |
| **R + SELECT** | Abrir directamente Opciones de Anfitrión |

### En Menús e Inventarios

| Botón | Acción |
| :--- | :--- |
| **Cruceta** | Navegar botones y casillas de inventario |
| **Stick Analógico** | Mover cursor puntero virtual |
| **✕ (Cruz)** | Seleccionar / Confirmar / Clic Izquierdo |
| **□ (Cuadrado)** | Dividir montón / Clic Derecho |
| **△ (Triángulo)** | Movimiento rápido (Shift + Clic) |
| **○ (Círculo)** | Volver / Cancelar / Salir del menú |
| **Gatillos L / R** | Desplazar lista / Cambiar pestaña creativa |

---

## 📥 Guía de Instalación

### 1. Requisitos
- Una consola **PlayStation Portable** (PSP 1000*, 2000, 3000, Go o Street) con Custom Firmware instalado (PRO, ME o ARK-4), una **PS Vita** con Adrenaline, o el emulador **PPSSPP**.
- *Nota: En PSP-1000 (32MB de RAM), se recomienda encarecidamente jugar en mundos antiguos de 256×256.*

### 2. Ubicación de Archivos
Copia la carpeta del juego en la Memory Stick bajo `PSP/GAME/`:

```text
ms0:/
 └── PSP/
      └── GAME/
           └── OptiCraft/
                ├── EBOOT.PBP
                └── assets.pak
```

- **Ruta en PPSSPP (Windows)**:
  `C:\Usuarios\<TuUsuario>\Documentos\PPSSPP\PSP\GAME\OptiCraft\`
- **Ruta en PPSSPP (Android)**:
  `/storage/emulated/0/PSP/GAME/OptiCraft/`

---

## 🛠️ Compilación desde Cero

Puedes compilar OptiCraft para PSP en Linux, Windows (vía WSL2) o mediante Docker.

### Método A: Compilación Automática con Docker (Recomendado)

No requiere configurar el toolchain localmente, solo tener [Docker](https://www.docker.com/) instalado:

```bash
# Clonar el repositorio
git clone https://github.com/erluza/OCHeritage-PSP.git
cd OCHeritage-PSP

# Compilar dentro del contenedor oficial de PSPSDK
docker run --rm -v "$(pwd):/work" -w /work pspdev/pspdev:latest bash -c "./build_psp.sh"
```
El archivo `EBOOT.PBP` resultante se generará en la raíz del repositorio.

---

### Método B: Compilación en Windows con WSL2

1. **Instalar Ubuntu en WSL2**:
   Abre PowerShell como Administrador:
   ```powershell
   wsl --install -d Ubuntu
   ```

2. **Configurar el entorno PSPDEV** dentro de WSL:
   ```bash
   sudo apt update
   sudo apt install -y build-essential cmake ninja-build ccache git python3 curl
   
   # Configurar la ruta de PSPDEV en el perfil
   echo 'export PSPDEV=/usr/local/pspdev' >> ~/.bashrc
   echo 'export PATH="$PSPDEV/bin:$PATH"' >> ~/.bashrc
   source ~/.bashrc
   ```

3. **Ejecutar el script de compilación**:
   Desde PowerShell en la carpeta del proyecto:
   ```bat
   "build psp.bat"
   ```
   O dentro del terminal de WSL:
   ```bash
   bash ./build_psp.sh
   ```

---

### Método C: CMake Manual (Linux / macOS)

Si ya cuentas con `pspdev` configurado en el sistema:

```bash
export PSPDEV=/usr/local/pspdev
export PATH="$PSPDEV/bin:$PATH"

mkdir -p build/psp && cd build/psp

cmake ../.. \
    -DCMAKE_TOOLCHAIN_FILE="${PSPDEV}/psp/share/pspdev.cmake" \
    -DPLATFORM=PSP \
    -DCMAKE_BUILD_TYPE=Release

cmake --build . --parallel $(nproc)
```

El archivo compilado se encontrará en:
`build/psp/bin/psp/EBOOT.PBP`

---

## 📄 Licencia

Este proyecto está bajo los términos de la licencia [GPL v3](LICENSE).
Minecraft es una marca registrada de Mojang Synergies AB / Microsoft. Este proyecto es una reimplementación independiente desarrollada con fines educativos y de preservación histórica.
