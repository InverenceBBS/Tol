# Function Replacements for Portability (`tol-master/tol/replace/`)

## Overview

This directory contains source code providing replacement implementations for various standard C library functions and common Unix utility functions. These replacements are typically used to ensure portability across different operating systems and environments where the native functions might be missing, buggy, or incompatible.

## Contents

The directory includes C source files (`.c`) implementing functions such as:
- **String/Memory:** `memset.c`, `strdup.c`
- **Filesystem/Stat:** `dirname.c`, `lstat.c`, `mkdir.c`, `stat.c`
- **Memory Allocation:** `malloc.c`, `realloc.c`
- **Error Reporting:** `error.c`
- **Internationalization:** `gettext.c` (a potentially complex replacement for GNU gettext functionality).
- **Time:** `strftime.c`
- **Numeric Conversion:** `strtod.c`
- **System Information:** `mountlist.c` (listing mounted filesystems), `canon-host.c` (canonicalizing hostnames).

**Build System Integration:** `Makefile.am` includes logic (likely driven by the main `configure` script) to conditionally compile these replacements only when the native system versions are deemed unsuitable or unavailable.

## Purpose

The primary goal of this directory is to enhance the portability of the TOL build process. By providing its own versions of potentially problematic standard functions, TOL can be built and run reliably on a wider range of systems, including older Unix variants or non-standard environments. The `configure` script typically performs tests to decide whether to use the system's native function or the replacement provided here.

## Appendix

- **Implementation Language:** C.
- **Build:** Conditionally compiled as part of the main `tol` library, based on results from the `configure` script. 