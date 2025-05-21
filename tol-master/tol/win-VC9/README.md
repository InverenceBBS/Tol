# Visual C++ 2008 (VC9) Build Files (`tol-master/tol/win-VC9/`)

## Overview

This directory contains Microsoft Visual Studio 2008 (VC9) solution (`.sln`) and project (`.vcproj`) files, along with supporting configuration and source files, required to build the core TOL interpreter, console application, and database drivers on Windows using the VC++ 2008 compiler toolchain. It mirrors the structure of the `win-VC8/` directory for the previous Visual Studio version.

## Contents

- **Visual Studio Solution & Projects:**
    - `gnutol.sln`: The main solution file for VS 2008.
    - `tollib.vcproj`: Project to build the core TOL static library (`tollib.lib`) using VC9.
    - `tolcon.vcproj`: Project to build the command-line interpreter executable (`tolcon.exe`).
    - `TestUseTol.vcproj`: Project to build a test executable.
    - `libtolmysql/`, `libtolodbc/`, `libtolpgsql/`, `libtolsqlite/`: Subdirectories likely containing `.vcproj` files to build the respective database driver DLLs using VC9.
- **VC9 Specific Files:**
    - `StdAfx.h`, `StdAfx.cpp`: Support for VC9 precompiled headers (PCH).
    - `config.h`: Windows-specific configuration header for the VC9 build.
    - `win_tolinc.h`: Includes necessary Windows SDK headers and defines Windows-specific settings for VC9.
    - `inttypes.h`, `stdint.h`: Compatibility headers for standard integer types.
    - `toldll.cpp`: Possibly related to building a DLL version.
- **Build Utilities:**
    - `postbuild.bat`: Batch script run after building projects.
    - `build_date_gen/`: Utility project to embed build date/time information.
- **Documentation:**
    - `ReadMe.txt`: Contains specific instructions related to building with VC9.

## Purpose

This directory provides a self-contained build environment for developers using Visual Studio 2008 (VC9) on Windows. It allows compiling the core TOL components using the native project format of this specific IDE, separate from the Autotools, CMake, or VC8 build configurations.

## Appendix

- **Technology:** Microsoft Visual C++ 2008 (VC9), MSBuild (via .vcproj).
- **Usage:** Open `gnutol.sln` in Visual Studio 2008 and build the desired projects. 