# README - textutil Module (tcllib 1.10)

## Overview

This directory contains the `textutil` module collection from Tcllib 1.10, within the `tolsh` VFS. It provides a suite of utilities for common text processing tasks.

## Contents

### Files

- `textutil.tcl`: Main package file, likely loading sub-packages.
- `adjust.tcl`: Procedures for text justification (left, right, center, full) and wrapping.
- `expander.tcl`: Handles expansion of tab characters into spaces.
- `repeat.tcl`: Procedures for repeating strings.
- `split.tcl`: Advanced string splitting capabilities (e.g., splitting by regexp, keeping delimiters).
- `string.tcl`: Miscellaneous string manipulation utilities.
- `tabify.tcl`: Procedures for converting spaces to tabs.
- `trim.tcl`: Procedures for trimming whitespace or specified characters from string ends.
- `*.tex`: TeX hyphenation pattern files (e.g., `dehypht.tex`, `eshyph_vo.tex`, `ithyph.tex`). These are likely used by the `adjust` or other formatting functions to perform language-specific hyphenation.
- `pkgIndex.tcl`: Standard Tcl package index file for the various `textutil::*` sub-packages.

### Subdirectories

None.

## Purpose

The purpose of this module collection is to offer a comprehensive set of tools for text manipulation and formatting in Tcl, going beyond the basic built-in string commands. It covers tasks like justification, wrapping, indentation, splitting, trimming, and potentially language-aware hyphenation.

## Appendix

N/A 