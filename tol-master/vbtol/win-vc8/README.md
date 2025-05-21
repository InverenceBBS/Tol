# VBTOL Visual Studio 2005 Project (`tol-master/vbtol/win-vc8/`)

## Overview

This directory contains the legacy Visual Studio 2005 (VC8) solution and
project files required to compile the VBTOL bridge library on Windows.

## Contents

- `vbtol.sln` – Visual Studio solution file targeting VC8.
- `vbtol.vcproj` – C++ project file for building the VBTOL DLL/COM component.
- `postbuild.bat` – Batch script executed after a successful build to copy the
  resulting binaries or register the component.

## Purpose

These files allow developers with the older VC8 toolchain to build the VBTOL
integration layer without relying on CMake. They remain for backwards
compatibility with projects still using Visual Studio 2005.

## Appendix

- **Technology:** Visual C++ 2005 project system.
- **Usage:** Open `vbtol.sln` in Visual Studio 2005 and build the solution.
