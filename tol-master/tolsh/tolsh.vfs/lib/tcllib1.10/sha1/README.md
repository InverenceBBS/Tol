# README - sha1 / sha256 Modules (tcllib 1.10)

## Overview

This directory contains implementations of the SHA-1 and SHA-256 cryptographic hash functions from Tcllib 1.10, within the `tolsh` VFS.

## Contents

### Files

- `sha1.tcl`: Pure Tcl implementation of the SHA-1 algorithm.
- `sha1v1.tcl`: An older version (v1) of the SHA-1 implementation.
- `sha1c.tcl`: Likely a wrapper or interface for a C-accelerated SHA-1 implementation.
- `sha256.tcl`: Pure Tcl implementation of the SHA-256 algorithm.
- `sha256c.tcl`: Likely a wrapper or interface for a C-accelerated SHA-256 implementation.
- `pkgIndex.tcl`: Standard Tcl package index file for the `sha1` and `sha256` packages.

### Subdirectories

None.

## Purpose

The purpose of these modules is to provide Tcl applications with the ability to compute SHA-1 and SHA-256 message digests. These hash functions are widely used for data integrity verification, digital signatures, and other cryptographic applications.

*Note: SHA-1 is considered cryptographically broken and should not be used for security-sensitive applications. SHA-256 is still considered secure.*

## Appendix

N/A 