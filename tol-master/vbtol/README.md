# VBTOL: TOL to Visual Basic Binding (`tol-master/vbtol/`)

## Overview

This directory contains **VBTOL**, the components needed to integrate the **TOL C++ engine** (`tol-master/tol/`) with **Microsoft Visual Basic** (likely VB6 and/or VBA). It appears to provide both Visual Basic code modules and a C/C++ helper library (potentially a COM object or a DLL) to bridge the gap between VB and the native TOL engine. It also includes scripts for creating a Windows installer.

## Code Functionality

- **Visual Basic Modules (`vbasic/`):** Contains Visual Basic source files (`.bas`, `.cls`, etc.) that define functions, classes, and types for VB developers to use. These VB functions likely wrap calls to the underlying C/C++ component.
- **C/C++ Bridge (`source/`):** Contains C/C++ source code that:
    - Exposes functions callable from Visual Basic (either through standard DLL exports or via a COM interface).
    - Uses the internal C++ API of the TOL engine to execute TOL operations.
    - Handles data conversion between Visual Basic types (Variant, Integer, Double, String, Arrays) and TOL's internal C++ types.
- **Build System:** Uses CMake (`CMakeLists.txt`) and specific Visual C++ project files/configurations (`win-vc8/`, `win-vc9/`) to compile the C/C++ bridge library.
- **Installer (`VBTol.nsi`, `makensis.bat`, `distribution/`):** Provides an NSIS script and batch file to build a Windows installer package (`.exe`). This installer likely registers the COM component (if applicable) and places the necessary files for VB integration.

## Potential API Functionality (Visual Basic Functions/Objects)

The API would consist of public `Function`, `Sub`, and potentially `Property` members within the VB modules/classes provided in `vbasic/`, possibly accessed via a main VBTOL object:
- **Object Creation:** `Set tol = CreateObject("VBTOL.Interpreter")` or similar if using COM.
- **Interpreter Control:** `tol.Init()`, `tol.Eval("...")`, `tol.Source("...")`.
- **Data Handling:** Functions/Methods to:
    - Pass VB variables (arrays, strings, numbers) to TOL functions or set TOL variables.
    - Retrieve results from TOL execution back into VB variables.
    - `GetMatrix`, `SetMatrix`, `GetSerie`, etc.

## Appendix

- **Implementation Language:** Visual Basic, C/C++.
- **Platform:** Primarily Windows.
- **Dependencies:** Requires a Visual Basic development environment, a Visual C++ compiler (for building the bridge), and the compiled core TOL library (`tol-master/tol/`).
- **Distribution:** Intended to be packaged as a Windows installer using NSIS.
- **License:** (License file missing, likely inherits - presumably GPL). 