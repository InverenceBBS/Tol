# Windows Development & Distribution Resources (`tol-master/windows/`)

## Overview

This directory aggregates various tools, scripts, notes, and pre-built components specifically tailored for developing, building, or distributing TOL and related components on the Microsoft Windows platform.

## Contents

- **Executables:**
    - `ActiveTOL_Base.exe`: Possibly an installer for a base "ActiveTOL" component, likely related to ActiveX/COM integration for use with languages like Visual Basic.
    - `setx.exe`: A standard Microsoft utility for setting environment variables from the command line or scripts. Included here likely for convenience during setup scripts.
    - `tol-contrib.exe`: Appears to be an installer or self-extracting archive containing contributed TOL packages, third-party libraries, or other dependencies pre-compiled for Windows.
- **Scripts:**
    - `setup_contrib.bat`: A Windows batch script likely used to install or configure the contents of `tol-contrib.exe`.
- **Subdirectories:**
    - `NSIS/`: May contain NSIS (Nullsoft Scriptable Install System) scripts used to create the `.exe` installers found in this directory (e.g., `ActiveTOL_Base.exe`, `tol-contrib.exe`), potentially separate from the main TOL installer definition.
    - `build_tools/`: Likely contains specific tools required for the Windows build process (e.g., particular versions of utilities, helper scripts, potentially pre-compiled libraries not handled by the main build).
    - `notes/`: Contains text files or documents with information specific to Windows development, build procedures, or known issues.

## Purpose

This directory serves as a collection point for resources facilitating the use and development of TOL on Windows. This includes setting up the development environment, managing dependencies (especially contributed packages), and potentially building specialized installers.

## Appendix

- **Technology:** Windows Batch scripts, NSIS, Executable installers, various build tools.
- **Usage:** Primarily for developers working on Windows or for distributing Windows-specific components and dependencies. 