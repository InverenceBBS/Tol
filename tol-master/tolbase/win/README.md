# Tolbase Windows Build Files (VC6/VC7) (`tol-master/tolbase/win/`)

## Overview

This directory contains project files and resources required for building the Tolbase component (likely the C extension or a standalone executable) on Windows using older versions of Microsoft Visual Studio, specifically Visual C++ 6.0 (VC6) and Visual Studio .NET 2002/2003 (VC7/VC7.1).

## Contents

- **Visual Studio Project Files:**
    - `tolbase.dsp`: Microsoft Visual Studio 6.0 project file.
    - `tolbase.vcproj`: Microsoft Visual Studio .NET 2002/2003 project file.
    These files define the source files, compiler settings, linker settings, and dependencies for building the Tolbase C component with these specific IDEs.
- **Windows Resources:**
    - `tolbase.rc`: Windows resource script defining application metadata (version, etc.) and potentially icons.
    - `resource.h`: Header file defining constants used in `tolbase.rc`.
    - `bayes.ico`: Icon file likely used for the application executable.
- **Documentation:**
    - `INSTALL`: Text file containing Windows-specific build or installation instructions relevant to using these Visual Studio project files.

## Purpose

This directory provides legacy support for building Tolbase on Windows using specific, older versions of Microsoft Visual Studio (VC6 and VC7). It allows developers maintaining or using these older environments to compile the necessary Tolbase components. Newer Visual Studio versions (VC8, VC9) have their own dedicated directories (`tol-master/tolbase/win-VC8/`, `tol-master/tolbase/win-VC9/`). Build configurations using CMake or Autotools likely use files from `tolbase/generic/`.

## Appendix

- **Technology:** Microsoft Visual C++ 6.0, Visual Studio .NET 2002/2003, Windows Resource Compiler.
- **Usage:** Open the `.dsp` or `.vcproj` file in the corresponding version of Visual Studio to build the Tolbase component. 