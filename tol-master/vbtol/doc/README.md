# VBTOL Documentation (`tol-master/vbtol/doc/`)

## Overview

This directory contains documentation files specifically for the **VBTOL** component, which provides an interface between Visual Basic and the TOL engine.

## Contents

- **`VBTol_distribution.txt`:** Provides information about distributing and installing the VBTOL component, likely covering the use of the NSIS installer found in `vbtol/distribution/`.
- **`dll_installation.txt`:** Contains specific instructions for installing and registering the core VBTOL DLL (the C++ bridge component). This might include manual registration steps using `regsvr32.exe` as an alternative or supplement to the installer.
- **`vb_programmer.txt`:** The primary guide for Visual Basic developers using VBTOL. This document likely describes:
    - How to add a reference to the VBTOL component (COM library) in a VB project (VB6/VBA).
    - The VBTOL object model (classes, interfaces).
    - Available methods, properties, and events for interacting with the TOL engine.
    - How to pass data (variables, arrays) between VB and TOL.
    - How TOL data types (Matrix, Serie, Date, etc.) are represented in VB (e.g., as Variants, specific object types).
    - Example code snippets.

## Purpose

This documentation provides essential information for users and developers working with VBTOL. It covers installation procedures and, most importantly, guides Visual Basic programmers on how to integrate and utilize TOL functionalities within their VB applications.

## Appendix

- **Format:** Plain text files (`.txt`). 