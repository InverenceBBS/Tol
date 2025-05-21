# TOL CMake Support Files (`tol-master/tol/cmake/`)

## Overview

This directory contains helper files for the CMake build system used by the TOL project. It includes toolchain files for specific compilation targets and custom CMake modules providing project-specific build logic.

## Contents

- **Toolchain Files (`*.toolchain.cmake`):** These files are used to configure CMake for specific compilers, architectures, or cross-compilation scenarios. Examples include:
    - `linux-i686.toolchain.cmake`: For targeting 32-bit Linux.
    - `mingw-*.toolchain.cmake`: Various configurations for using the MinGW compiler to target 32-bit or 64-bit Windows, potentially specifying optimization levels.
    Toolchain files are typically passed to CMake using the `CMAKE_TOOLCHAIN_FILE` variable.
- **Custom Modules (`modules/`):** This subdirectory contains project-specific CMake modules (`.cmake` files). These modules likely define custom functions, macros, or variables to:
    - Find required libraries or tools that CMake doesn't support natively (e.g., `FindTOLDependency.cmake`).
    - Implement complex configuration logic.
    - Define common sets of compiler flags or build options.
    - Perform other helper tasks during the CMake configuration process.
    These modules are made available to the main `CMakeLists.txt` files via `list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)`.

## Purpose

This directory helps make the TOL CMake build system more robust, portable, and maintainable by:
- Providing standard configurations for different target platforms and compilers (toolchain files).
- Encapsulating reusable or complex build logic into custom modules.

## Appendix

- **Technology:** CMake scripting language.
- **Usage:** Used internally by the TOL CMake build process. Toolchain files are selected via the `CMAKE_TOOLCHAIN_FILE` variable, while modules are automatically found if added to `CMAKE_MODULE_PATH`. 