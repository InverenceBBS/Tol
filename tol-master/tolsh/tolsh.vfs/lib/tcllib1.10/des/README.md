# README - des Module (tcllib 1.10)

## Overview

This directory holds the `des` module from Tcllib 1.10, within the `tolsh` VFS. It provides an implementation of the Data Encryption Standard (DES) algorithm, including Triple DES (3DES).

## Contents

### Files

- `des.tcl`: Core implementation of the DES/3DES algorithm.
- `tcldes.tcl`: Another Tcl implementation or interface for DES.
- `tcldesjr.tcl`: Potentially a variant or specific version (jr?) of the Tcl DES implementation.
- `pkgIndex.tcl`: Standard Tcl package index file for the module.

### Subdirectories

None.

## Purpose

The purpose of this module is to provide DES and Triple DES encryption and decryption capabilities for Tcl applications needing symmetric-key cryptography.

*Note: DES is considered insecure for most modern applications due to its small key size. Triple DES offers better security but is slower and less secure than modern algorithms like AES. Use with caution and prefer AES where possible.* 

## Appendix

N/A 