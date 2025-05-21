# VBTOL Test Suite (`tol-master/vbtol/tests/`)

## Overview

This directory contains a suite of integration tests for the **VBTOL** component. The tests are implemented as Microsoft Excel workbooks (`.xls`) containing Visual Basic for Applications (VBA) code.

## Contents

Each `.xls` file represents a specific test case targeting different functionalities of the VBTOL bridge:

- **`test1_eval.xls`:** Tests the basic evaluation of TOL code strings from VB.
- **`test2_decompile.xls`:** Likely tests functionality related to retrieving or inspecting TOL code definitions (decompiling).
- **`test3_text.xls`:** Tests the transfer and handling of text (string) data between VB and TOL.
- **`test4_real.xls`:** Tests the transfer and handling of floating-point (real) numbers.
- **`test5_matrix.xls`:** Tests basic operations involving TOL matrices (creation, data transfer, manipulation).
- **`test6_+matrix.xls`:** Likely tests more complex or larger-scale matrix operations.

The VBA code within these Excel files uses the VBTOL COM object to interact with the TOL engine, executing test scenarios and likely verifying the results.

## Purpose

This directory provides a means to test the VBTOL component in its intended usage environment (VBA within Microsoft Office applications, primarily Excel). These tests ensure that the C++ bridge correctly exposes TOL functionality and handles data exchange with Visual Basic.

## Appendix

- **Environment:** Microsoft Excel with VBA support.
- **Dependency:** Requires the VBTOL component (DLL) to be compiled and registered on the system.
- **Technology:** VBA, Microsoft Excel Object Model, VBTOL COM component. 