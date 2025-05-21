# README - md5crypt Module (tcllib 1.10)

## Overview

This directory contains the `md5crypt` module from Tcllib 1.10, part of the `tolsh` VFS. It provides an implementation of the MD5-based crypt function, commonly used for password hashing on Unix-like systems.

## Contents

### Files

- `md5crypt.tcl`: The main Tcl implementation of the MD5 crypt algorithm.
- `md5cryptc.tcl`: Likely a related implementation or component, possibly a C-accelerated version or interface.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to allow Tcl applications to generate and verify password hashes compatible with the MD5-based crypt format found on many systems. It takes a password and a salt and produces a hash string.

*Note: MD5crypt is considered cryptographically weak for password hashing by modern standards. Prefer stronger algorithms like bcrypt, scrypt, or Argon2 where possible.*

## Appendix

N/A 