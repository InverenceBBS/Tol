# Visual C++ 2005 (VC8) Build Files (`tol-master/tol/win-VC8/`)

## Overview

This directory contains Microsoft Visual Studio 2005 (VC8) solution (`.sln`) and project (`.vcproj`) files, along with supporting configuration and source files, required to build the core TOL interpreter, console application, and database drivers on Windows using this specific compiler toolchain.

## Contents

- **Visual Studio Solution & Projects:**
    - `gnutol.sln`: The main solution file, organizing the various TOL projects.
    - `tollib.vcproj`: Project to build the core TOL functionality as a static library (`tollib.lib`). Includes references to source files from `tol/`, `bbasic/`, `bmath/`, `bparser/`, `btol/`, `lang/`, `OIS/`, `tai/`, etc.
    - `tolcon.vcproj`: Project to build the command-line interpreter executable (`tolcon.exe`). Links against `tollib.lib`.
    - `TestUseTol.vcproj`: Project to build a test executable using the TOL library.
    - `libtolmysql/`, `libtolodbc/`, `libtolpgsql/`: Subdirectories likely containing `.vcproj` files to build the respective database driver DLLs.
- **VC8 Specific Files:**
    - `StdAfx.h`, `StdAfx.cpp`: Support for Visual C++ precompiled headers (PCH).
    - `config.h`: A Windows-specific configuration header, defining preprocessor macros for the build.
    - `win_tolinc.h`: Includes necessary Windows SDK headers and defines Windows-specific macros or types.
    - `inttypes.h`, `stdint.h`: Compatibility headers for standard integer types.
    - `toldll.cpp`: Possibly related to building a DLL version (though main project is static).
- **Build Utilities:**
    - `postbuild.bat`: Batch script run after building projects, e.g., to copy build outputs.
    - `build_date_gen/`: Likely a utility project to embed build date/time information.
- **Documentation:**
    - `ReadMe.txt`: Contains specific instructions related to building with VC8.

## Purpose

This directory provides a self-contained build environment for developers using Visual Studio 2005 (VC8) on Windows. It allows compiling the core TOL components without relying on Autotools or CMake, using the native project format of this older IDE.

## Appendix

- **Technology:** Microsoft Visual C++ 2005 (VC8), MSBuild (via .vcproj).
- **Usage:** Open `gnutol.sln` in Visual Studio 2005 and build the desired projects (e.g., `tollib`, `tolcon`). 