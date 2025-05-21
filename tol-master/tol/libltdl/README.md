# Embedded GNU Libltdl (`tol-master/tol/libltdl/`)

## Overview

This directory contains an embedded copy of **GNU Libltdl**, which is part of the GNU Libtool project. Libltdl provides a portable C interface for dynamically loading shared libraries and resolving symbols within them across different operating systems.

## Contents

- **Libltdl Source Code:** Contains the C source (`ltdl.c`, `libltdl/`, `loaders/`) and header (`ltdl.h`) files for the Libltdl library.
- **Libltdl Build System:** Includes the standard Autotools configuration files (`configure.ac`, `Makefile.am`, etc.) used to build the Libltdl library itself.
- **License:** `COPYING.LIB` contains the GNU Lesser General Public License (LGPL), under which Libltdl is distributed.
- **Internal Utilities:** Helper source files used by Libltdl (`argz.c`, `lt__*.c`, `slist.c`).

## Purpose

By embedding Libltdl, the TOL project ensures that it has a consistent and portable mechanism for dynamic library loading across all supported platforms (various Unix-like systems, Windows). This avoids potential inconsistencies between different native `dlopen`-like implementations and removes the need for users to have Libltdl pre-installed as a separate dependency.

The dynamic loading functionality implemented in `tol-master/tol/LoadDynLib/` likely acts as a C++ wrapper around the C API provided by this embedded Libltdl library.

## Appendix

- **Technology:** GNU Libltdl, C, Autotools.
- **License:** LGPL (see `COPYING.LIB`).
- **Build:** This library is likely built as part of the main TOL build process, either statically linked or as a separate shared library used internally by TOL. 