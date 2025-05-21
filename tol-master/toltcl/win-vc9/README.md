# TolTcl Visual C++ 2008 (VC9) Build Files (`tol-master/toltcl/win-vc9/`)

## Overview

This directory contains the Microsoft Visual Studio 2008 (VC9) solution (`.sln`) and project (`.vcproj`) files needed to build the **TolTcl** binding layer as a shared library (`.dll`) on Windows using the VC++ 2008 compiler toolchain.

## Contents

- **Visual Studio Files:**
    - `toltcl.sln`: The main Visual Studio 2008 solution file for the TolTcl project.
    - `toltcl.vcproj`: The Visual Studio 2008 project file. It specifies the C/C++ source files (from `toltcl/generic/`), compiler and linker settings, and dependencies (Tcl libraries, core TOL library) required to build `toltcl.dll` using VC9.
- **Build Utility:**
    - `postbuild.bat`: A Windows batch script executed after a successful build, possibly to copy the output DLL.
- **Documentation:**
    - `ReadMe.txt`: Provides specific instructions or notes for building TolTcl using Visual Studio 2008.

## Purpose

This directory provides a self-contained build environment for compiling the TolTcl binding library using Visual Studio 2008 (VC9). It allows developers using this specific IDE on Windows to build the Tcl interface for TOL, separate from the CMake, Autotools, or VC8 build systems.

## Appendix

- **Technology:** Microsoft Visual C++ 2008 (VC9), MSBuild (via .vcproj).
- **Usage:** Open `toltcl.sln` in Visual Studio 2008 and build the project. 