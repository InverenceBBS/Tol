# VBTOL C++ Bridge Source (`tol-master/vbtol/source/`)

## Overview

This directory contains the C++ source code that implements the **VBTOL** bridge component. This component acts as an intermediary, allowing Microsoft Visual Basic applications to communicate with the core C++ TOL engine. It is likely compiled into a Windows DLL (Dynamic Link Library), possibly functioning as a COM object.

## Contents

- **Main Bridge Logic (`vbtol.cpp`):** Implements the functions or COM methods exposed to Visual Basic. These functions receive calls from VB, interact with the TOL C++ engine API to perform the requested operations (e.g., execute code, access data), and return results back to VB.
- **Data Conversion (`datatype.cpp`):** Contains C++ code dedicated to marshalling data between Visual Basic data types (like `VARIANT`, `SAFEARRAY`, `BSTR`, basic types) and the internal C++ representations of TOL objects (`TolMatrix`, `TolSerie`, `TolDate`, etc.). This is often a complex part of language bindings.
- **Utilities (`vbutils.cpp`, `vbutils.h`):** Provides helper C++ functions specifically for the VBTOL bridge. This might include utilities for working with COM types, managing VARIANTs, simplifying interactions with the TOL API for VB, or handling COM-specific error reporting.
- **Exports Definition (`vbtol.def`):** A Windows module-definition file used during linking. It explicitly lists the functions that the compiled VBTOL DLL exports, making them callable from external applications like Visual Basic.
- **Build Integration (`CMakeLists.txt`):** CMake script defining how to compile this C++ code, link it against the core TOL library (`tollib`), and produce the final VBTOL DLL.

## Purpose

This C++ code forms the essential translation layer between the Visual Basic environment and the TOL engine. It exposes TOL's functionality in a way that VB can understand (exported DLL functions or COM methods) and handles the necessary data type conversions between the two different runtime systems.

## Appendix

- **Implementation Language:** C++.
- **Technology:** Windows DLLs, potentially COM (Component Object Model), TOL C++ API.
- **Build:** Compiled into a DLL using CMake or Visual Studio project files (`vbtol/win-vc*/`). 