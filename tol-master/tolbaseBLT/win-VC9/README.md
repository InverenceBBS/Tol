# Visual Studio 2008 Files (`tol-master/tolbaseBLT/win-VC9/`)

## Overview

Project files for building the tolbaseBLT library using Microsoft Visual Studio
2008. They mirror the CMake build but are kept for legacy workflows.

## Contents

- `tolbaseBLT.sln` and `.vcproj` files defining the build configuration.
- `postbuild.bat` scripts to copy the resulting DLLs to expected locations.

## Purpose

Allows developers restricted to the VC9 toolchain to compile the widget library
without CMake.

## Appendix

- **Technology:** Visual C++ 2008 project format.
- **Usage:** Open the solution in Visual Studio 2008 and build.
