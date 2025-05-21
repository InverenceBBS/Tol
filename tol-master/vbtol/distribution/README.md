# VBTOL NSIS Installer Definition (`tol-master/vbtol/distribution/`)

## Overview

This directory contains the core files used to build the NSIS (Nullsoft Scriptable Install System) installer for the **VBTOL** component (Visual Basic binding for TOL).

## Contents

- **`VBTol.nsi`:** The main NSIS script file. This script contains instructions for the NSIS compiler, defining:
    - Installer pages and user interface elements.
    - Files to be included in the installer (e.g., the VBTOL COM DLL/OCX, VB modules, core TOL DLLs, documentation).
    - Installation logic (e.g., target directories, Start Menu shortcuts).
    - Actions to perform during installation/uninstallation (e.g., registering/unregistering the VBTOL COM component using `regsvr32`).
    - License agreements, version information.
- **`makensis.bat`:** A simple Windows batch script that invokes the NSIS compiler (`makensis.exe`) with the `VBTol.nsi` script as input, automating the process of generating the final `VBTOL_Setup.exe` (or similar) installer file.
- **`MIN.EXE`:** An executable file whose specific purpose within the distribution context is unclear. It might be a minimal required dependency or a helper tool used by the installer or the installed component.

## Purpose

This directory provides the necessary configuration and automation (`.nsi` script and `.bat` file) to package the VBTOL components (compiled C++ bridge, VB modules) into a user-friendly Windows installer (`.exe`). This allows Visual Basic developers to easily install and register the VBTOL component on their system.

## Appendix

- **Technology:** NSIS (Nullsoft Scriptable Install System), Windows Batch scripting.
- **Usage:** Run `makensis.bat` (requires NSIS to be installed and in the PATH) to build the VBTOL installer executable. 