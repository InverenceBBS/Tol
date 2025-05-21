# Tolbase BLT (?) (`tol-master/tolbaseBLT/`)

## Overview

This directory appears to be a duplicate or a functionally identical copy of the `tol-master/tolbase` directory. It contains the source code and build files for **Tolbase**, the Tcl/Tk-based Graphical User Interface for TOL.

## Contents

The file and directory structure within `tolbaseBLT/` mirrors that of `tolbase/`, including:
- Tcl/Tk scripts (`generic/`, `lib/`, `conf.tcl`, `pkgIndex.tcl`).
- Build system files (Autotools, CMake).
- Documentation and informational files (`README`, `INSTALL`, `NEWS`, etc.).

The included `README` file is identical to the one in `tolbase/` and describes the Tolbase GUI without mentioning BLT specifically.

## Purpose

The exact purpose of this separate directory is unclear from the contents alone. Possible reasons include:
- An older version or experimental branch.
- A specific build variant (perhaps one intended to use the BLT Tcl extension, although not explicitly stated).
- A remnant from project refactoring.

Functionally, it seems to represent the same Tolbase GUI component found in `tol-master/tolbase/`. Refer to `tol-master/tolbase/README.md` for a detailed description of Tolbase.

## Appendix

- **Status:** Likely redundant or deprecated in favor of `tol-master/tolbase/`. Further investigation (e.g., code diff, commit history) would be needed to confirm its specific role or differences.
- **Technology:** Tcl/Tk, C (extensions), Autotools, CMake.
- **License:** GNU General Public License (GPL). See `COPYING`. 