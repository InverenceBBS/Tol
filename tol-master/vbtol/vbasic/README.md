# VBTOL Visual Basic Example (`tol-master/vbtol/vbasic/`)

## Overview

This directory contains example code for using the **VBTOL** component from Visual Basic for Applications (VBA) or standalone Visual Basic projects.

## Contents

- **`tol.bas`:** A Visual Basic module file (`.bas`). This file contains the necessary **VBA `Declare` statements** and custom **`Type` definitions** required to call functions within the compiled `VBTol.dll`. It defines the interface for:
    - Initializing the VBTOL component (`TolInit`).
    - Executing TOL code (`TolEval`).
    - Decompiling TOL objects (`TolDecompile`, `TolDecompileAll`).
    - Transferring data between VBA and TOL (Text, Real, Matrix) using functions like `TolGetText`, `TolCreateReal`, `TolGetMatrix`, `TolPutRange`, etc.

## Purpose

The primary purpose of `tol.bas` is to provide the essential **API declarations** for developers integrating TOL functionality into applications using Visual Basic or VBA (e.g., Microsoft Excel, Access). Importing this module allows VBA code to call the functions exposed by the `VBTol.dll`. It serves as the bridge between the VBA environment and the VBTOL COM component.

## Appendix

- **Environment:** Visual Basic 6, VBA (Excel, Access, Word, etc.)
- **Dependency:** Requires the VBTOL component (DLL) to be compiled and registered on the system.
- **Technology:** VBA/Visual Basic, COM Interoperability. 