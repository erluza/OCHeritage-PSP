# ATENCION: ARCHIVO assets.pak OBLIGATORIO

# ES TOTALMENTE NECESARIO CONTAR CON EL ARCHIVO assets.pak PARA QUE EL JUEGO ARRANQUE SIN ERRORES

## Se puede encontrar en la comunidad de Discord oficial disponible en:
## https://ocheritage.vercel.app/

***

# ATTENTION: assets.pak FILE REQUIRED

# IT IS ABSOLUTELY REQUIRED TO HAVE THE assets.pak FILE FOR THE GAME TO LAUNCH WITHOUT ERRORS

## It can be found in the official Discord community available at:
## https://ocheritage.vercel.app/

***

# OptiCraft Heritage Edition: PlayStation Portable (PSP)

Read this in English | Leer en Español

# English

## Overview

OptiCraft Heritage Edition (PSP Port) is an optimized, clean room C++17 port of classic Minecraft gameplay specifically crafted for the Sony PlayStation Portable (PSP) and the PPSSPP emulator.

Built directly against the bare metal PSPSDK and Allegrex MIPS architecture, this port brings the authentic classic sandbox experience to Sony legendary handheld while strictly respecting its tight hardware limitations (MIPS R4000 at 333 MHz, 32MB / 64MB RAM).

## Features and Optimizations

**PS2 Parity 2D Heightmap World Generator**
Uses the lightweight 2D heightmap generator (ChunkProviderGenerateLite) and fast biome sampling (WorldChunkManagerFast), mirroring the generation of the PlayStation 2 edition. Replaces heavy 3D double precision Perlin noise with single precision float mathematics for ultra fast chunk generation on MIPS without CPU stalls.

**Optimized 256x256 Bounded Worlds**
Authentic console sized worlds (16x16 chunks) with seamless edge physics. Outward velocity decomposition ensures the player can smoothly slide along world borders and walk back towards the center with zero friction, eliminating the classic stuck sensation.

**Custom Dual Mode Control Layout**
Gameplay Mode: Smooth analog nub movement, responsive face button camera look with exponential ramp curves, quick hotbar cycling, and dedicated trigger actions.
Menu Mode: Dual navigation featuring both intuitive D Pad grid jumping and a fast analog virtual pointer for inventories and crafting.

**Auto Jump Built In**
Automatic single block elevation step up enabled by default, complete with an in game toggle in Heritage Options and Host Options.

**Fixed Function 16 bit Depth Optimization**
Engineered specifically for the PSP Graphic Engine (GE) to avoid coplanar Z fighting in 2D overlays, preserving vibrant full hearts, hunger icons, and pixel perfect button glyphs.

**Memory Footprint and Chunk Streaming**
Configured memory ring buffers and chunk load ceilings to guarantee rock solid stability on both retail hardware and emulators.

## Controller Layout

### Gameplay Controls

Analog Stick: Walk / Strafe (360° Movement)
△ (Triangle): Look Up
✕ (Cross): Look Down
□ (Square): Look Left
○ (Circle): Look Right
R Trigger: Primary Action (Attack / Mine Block)
L Trigger: Secondary Action (Use / Place Block)
D Pad Up: Jump
D Pad Down: Sneak / Crouch
D Pad Left / Right: Hotbar Item Selection (Previous / Next)
START: Pause Menu / Host Options
SELECT: Inventory / Crafting Menu
R + SELECT: Open Host Options Directly

### Menu and Inventory Controls

D Pad: Navigate UI buttons and inventory slots
Analog Stick: Move virtual pointer cursor
✕ (Cross): Select / Confirm / Left Click
□ (Square): Split Stack / Right Click
△ (Triangle): Quick Move (Shift + Click)
○ (Circle): Back / Cancel / Exit Menu
L / R Triggers: Scroll Container / Change Creative Tabs

## Installation

### 1. Requirements
A PlayStation Portable (PSP 1000, 2000, 3000, Go, or Street) running custom firmware (PRO, ME, or ARK4), a PS Vita with Adrenaline, or the PPSSPP emulator.
Note: On PSP 1000 (32MB RAM), limited 256x256 worlds are strongly recommended.

### 2. File Placement
Copy the game folder to your Memory Stick under PSP/GAME/:

```text
ms0:/
 └── PSP/
      └── GAME/
           └── OptiCraft/
                ├── EBOOT.PBP
                └── assets.pak
```

**PPSSPP Path (Windows)**:
C:\Users\<YourUser>\Documents\PPSSPP\PSP\GAME\OptiCraft\

**PPSSPP Path (Android)**:
/storage/emulated/0/PSP/GAME/OptiCraft/

## Compiling from Scratch

You can compile OptiCraft for PSP using Windows (WSL2), Linux, or Docker.

### Building on Windows or Linux

1. From Windows in the project directory, run:
   "build psp.bat"

2. Or inside WSL / Linux terminal, run:
   bash ./build_psp.sh

The resulting EBOOT.PBP will be located in the project root and in build/psp/bin/psp/EBOOT.PBP.

***

# Español

## Descripcion General

OptiCraft Heritage Edition (Port PSP) es un port limpio y altamente optimizado en C++17 de la era clasica de Minecraft, diseñado especificamente para la consola portatil Sony PlayStation Portable (PSP) y el emulador PPSSPP.

Desarrollado directamente sobre el PSPSDK nativo y la arquitectura Allegrex MIPS, este port traslada la experiencia sandbox clasica a la legendaria consola de Sony respetando estrictamente sus limitaciones de hardware (CPU MIPS R4000 a 333 MHz y 32MB / 64MB de memoria RAM).

## Caracteristicas y Optimizaciones

**Generador de Terreno 2D Heightmap (Paridad con PS2)**
Utiliza el generador de mapa de alturas (ChunkProviderGenerateLite) y muestreo rapido de biomas (WorldChunkManagerFast), exactamente igual a la version de PlayStation 2. Reemplaza el pesado ruido 3D Perlin de doble precision por matematicas en coma flotante de precision simple, logrando una generacion de chunks instantanea sin congelamientos en la CPU MIPS.

**Mundos Delimitados de 256x256 Optimizados**
Mundos autenticos de consola (16x16 chunks) con fisica de bordes suave. La descomposicion de velocidad radial anula unicamente la componente de movimiento que intenta salir del mapa, permitiendo deslizarse por el borde y regresar hacia el interior con total fluidez, eliminando el clasico problema de quedarse enganchado o pegado en el limite.

**Sistema de Control Dual Adaptado**
Modo En Juego: Movimiento fluido en 360° con el joystick analogico, control de camara suave mediante los botones frontales con curva de aceleracion exponencial, cambio rapido de barra de acceso y gatillos de accion.
Modo Menus: Navegacion combinada mediante cruceta direccional (salto entre botones) y puntero virtual analogico para inventarios y crafteo.

**Salto Automatico (Auto Jump) Integrado**
Deteccion y subida automatica de obstaculos de un bloque activada por defecto, con interruptor de activacion o desactivacion en las opciones de pausa (Host Options) y de sistema (Heritage Options).

**Ajuste de Buffer de Profundidad de 16 bits**
Optimizado para el Graphic Engine (GE) de la PSP para evitar colisiones coplanares en el buffer de profundidad, asegurando corazones y comida con relleno visible y tipografias e iconos nitidos.

**Presupuesto Estricto de Memoria**
Administracion dinamica de memoria y streaming acotado de chunks para garantizar estabilidad total tanto en consolas reales como en emuladores.

## Esquema de Controles

### Durante la Partida

Stick Analogico: Caminar / Desplazarse (Movimiento 360°)
△ (Triangulo): Mirar hacia arriba
✕ (Cruz): Mirar hacia abajo
□ (Cuadrado): Mirar hacia la izquierda
○ (Circulo): Mirar hacia la derecha
Gatillo R: Accion Principal (Atacar / Romper bloque)
Gatillo L: Accion Secundaria (Usar / Colocar bloque)
Cruceta Arriba: Saltar
Cruceta Abajo: Agacharse / Sigilo
Cruceta Izq / Der: Cambiar objeto en la barra rapida
START: Menu de Pausa / Opciones de Anfitrion
SELECT: Inventario / Crafteo
R + SELECT: Abrir directamente Opciones de Anfitrion

### En Menus e Inventarios

Cruceta: Navegar botones y casillas de inventario
Stick Analogico: Mover cursor puntero virtual
✕ (Cruz): Seleccionar / Confirmar / Clic Izquierdo
□ (Cuadrado): Dividir monton / Clic Derecho
△ (Triangulo): Movimiento rapido (Shift + Clic)
○ (Circulo): Volver / Cancelar / Salir del menu
Gatillos L / R: Desplazar lista / Cambiar pestaña creativa

## Guia de Instalacion

### 1. Requisitos
Una consola PlayStation Portable (PSP 1000, 2000, 3000, Go o Street) con Custom Firmware instalado (PRO, ME o ARK4), una PS Vita con Adrenaline, o el emulador PPSSPP.
Nota: En PSP 1000 (32MB de RAM), se recomienda encarecidamente jugar en mundos antiguos de 256x256.

### 2. Ubicacion de Archivos
Copia la carpeta del juego en la Memory Stick bajo PSP/GAME/:

```text
ms0:/
 └── PSP/
      └── GAME/
           └── OptiCraft/
                ├── EBOOT.PBP
                └── assets.pak
```

**Ruta en PPSSPP (Windows)**:
C:\Usuarios\<TuUsuario>\Documentos\PPSSPP\PSP\GAME\OptiCraft\

**Ruta en PPSSPP (Android)**:
/storage/emulated/0/PSP/GAME/OptiCraft/

## Compilacion desde Cero

Puedes compilar OptiCraft para PSP en Windows (via WSL2), Linux o Docker.

### Compilacion en Windows o Linux

1. Desde Windows en la carpeta del proyecto, ejecuta:
   "build psp.bat"

2. O dentro de la terminal de WSL / Linux, ejecuta:
   bash ./build_psp.sh

El archivo compilado se encontrara en la raiz y en build/psp/bin/psp/EBOOT.PBP.

## Licencia

Este proyecto esta bajo los terminos de la licencia GPL v3 (LICENSE).
Minecraft es una marca registrada de Mojang Synergies AB / Microsoft. Este proyecto es una reimplementacion independiente desarrollada con fines educativos y de preservacion historica.
