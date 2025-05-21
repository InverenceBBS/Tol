# Tolbase Launch Scripts (`tol-master/tolbase/bin/`)

## Overview

This directory contains scripts used to launch the Tolbase Graphical User Interface (GUI).

## Contents

- **`tolbase.sh`:** A shell script designed for Unix-like systems (Linux, macOS) to start Tolbase. It likely performs tasks such as:
    - Setting up the environment (e.g., sourcing `confenv.sh` from `tol/bin/`, adding necessary library paths).
    - Locating the appropriate Tcl/Tk shell executable (`wish`).
    - Executing the main Tolbase Tcl script (possibly `tolbase.tcl` or another script within the Tolbase library).
- **`tolbase.tcl`:** A minimal Tcl script. It might serve as the initial bootstrap script executed by `tolbase.sh` or `wish`, responsible for loading the main Tolbase Tcl package (`pkgIndex.tcl` in the parent directory) and starting the GUI.
- **`CMakeLists.txt`:** A CMake script, probably used to install the `tolbase.sh` script into the system's executable path during installation.

## Purpose

These scripts provide a standard and user-friendly way to start the Tolbase GUI application from the command line, ensuring that the necessary environment variables and Tcl/Tk interpreter settings are correctly configured.

## Appendix

- **Implementation Language:** Shell script (sh/bash), Tcl.
- **Platform:** `tolbase.sh` for Unix-like systems. `tolbase.tcl` is cross-platform but needs a Tcl/Tk interpreter (`wish`).
- **Usage:** Execute `tolbase.sh` on Unix-like systems to start the GUI. 