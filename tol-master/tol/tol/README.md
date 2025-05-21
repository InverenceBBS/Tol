# Autotools Header Link Directory (`tol-master/tol/tol/`)

## Overview

This directory contains only a `Makefile.am` used by the Autotools build process. It does not contain source code itself but defines targets to manage symbolic links to header files from other core TOL directories.

## Contents

- **`Makefile.am`:** Defines custom `make` targets:
    - `header-links`: Creates symbolic links in this directory (`tol-master/tol/tol/`) pointing to all `.h` and `.hpp` header files located in `tol-master/tol/` and its main subdirectories (`bbasic`, `bmath`, `bparser`, `btol`, `OIS`, `lang`).
    - `remove-links`: Deletes the symbolic links created above.
    - Standard targets (`all`, `clean`, `distclean`) are modified to ensure links are created before building and removed during cleaning.
    - Includes commented-out code related to generating precompiled headers (`.h.gch`), suggesting a potentially deprecated optimization attempt.

## Purpose

This directory and its `Makefile.am` serve as a helper for the Autotools build. By creating a temporary directory containing links to all relevant project headers, it might simplify the include paths used during compilation (allowing the compiler to use `-I.` relative to this directory). This is primarily an internal mechanism of the Autotools build setup for the core TOL library.

## Appendix

- **Technology:** GNU Make, Automake, Symbolic Links.
- **Usage:** Used internally by the `make` process when building TOL with Autotools. Not typically interacted with directly by users or developers unless modifying the core Autotools build structure. 