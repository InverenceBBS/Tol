# CMake Build Configuration (`tol-master/tolbaseBLT/cmake/`)

## Overview

This directory contains the main CMake scripts used to configure and build the
tolbaseBLT widget set. The top-level `CMakeLists.txt` references modules in the
`modules/` subdirectory to locate dependencies.

## Contents

- `CMakeLists.txt` – Entry point for configuring the library.
- `modules/` – Custom `Find*.cmake` modules and helper macros.

## Purpose

These files allow tolbaseBLT to be built in a platform-independent manner using
CMake. They handle compiler flags, installation paths, and discovery of required
packages.

## Appendix

- **Technology:** CMake scripting.
- **Usage:** Run `cmake` followed by your build tool to compile the library.
