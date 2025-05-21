# README - crc Module (tcllib 1.10)

## Overview

This directory contains the `crc` module from Tcllib 1.10, located within the `tolsh` VFS. It provides implementations for various Cyclic Redundancy Check (CRC) and checksum algorithms.

## Contents

### Files

- `crc16.tcl`: Implementation of CRC-16 algorithms (potentially multiple variants).
- `crc32.tcl`: Implementation of the CRC-32 algorithm (commonly used in zip, png, ethernet).
- `cksum.tcl`: Implementation of the POSIX `cksum` algorithm.
- `sum.tcl`: Implementation of the BSD `sum` algorithm.
- `crcc.tcl`: Likely a wrapper or interface related to a C implementation for performance.
- `pkgIndex.tcl`: Standard Tcl package index file for the various checksum and CRC packages (`crc16`, `crc32`, `cksum`, `sum`).

### Subdirectories

None.

## Purpose

The purpose of this module is to provide Tcl applications with tools for calculating data integrity checks using common CRC and checksum algorithms. These are often used to verify that data has not been corrupted during transmission or storage.

## Appendix

N/A 