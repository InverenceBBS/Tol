# README - base64 Module (tcllib 1.10)

## Overview

This directory contains the `base64` module from Tcllib 1.10, within the `tolsh` VFS. It provides implementations for various binary-to-text encoding schemes, primarily Base64, but also including Uuencode and Yencode.

## Contents

### Files

- `base64.tcl`: The main Tcl implementation for Base64 encoding and decoding.
- `base64c.tcl`: Likely a wrapper or interface related to a C implementation for performance.
- `uuencode.tcl`: Implementation for Uuencode and Uudecode.
- `yencode.tcl`: Implementation for Yencode and Ydecode.
- `pkgIndex.tcl`: Standard Tcl package index file for the `base64`, `uuencode`, and `yencode` packages.

### Subdirectories

None.

## Purpose

The purpose of this module is to provide standard methods for encoding binary data into text formats. Base64 is widely used in email (MIME), XML, and other protocols where transmitting raw binary data is problematic. Uuencode and Yencode are older encoding schemes often associated with Usenet newsgroups.

## Appendix

N/A 