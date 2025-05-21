# Tolbase Visual C++ 2008 (VC9) Build Files (`tol-master/tolbase/win-VC9/`)

## Overview

This directory contains the Microsoft Visual Studio 2008 (VC9) solution (`.sln`) and project (`.vcproj`) files needed to build the Tolbase C component (Tcl extension or standalone executable) using the VC++ 2008 compiler toolchain on Windows.

## Contents

- **`tolbase.sln`:** The main Visual Studio 2008 solution file.
- **`tolbase.vcproj`:** The Visual Studio 2008 project file. This file specifies the C source files (likely from `tolbase/generic/`), compiler and linker settings, dependencies (Tcl/Tk libraries), and output type (DLL for the package or EXE for standalone) for the VC9 build.

## Purpose

This directory provides a specific build environment for compiling the Tolbase C components using Visual Studio 2008 (VC9). It complements the build configurations provided for other Visual Studio versions (`tolbase/win/`), CMake (`tolbase/CMakeLists.txt`), and Autotools (`tolbase/configure.in`).

## Appendix

- **Technology:** Microsoft Visual C++ 2008 (VC9), MSBuild (via .vcproj).
- **Usage:** Open `tolbase.sln` in Visual Studio 2008 and build the project. 