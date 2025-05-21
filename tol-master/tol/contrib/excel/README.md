# TOL Excel File Interface (`tol-master/tol/contrib/excel/`)

## Overview

This directory contains C++ source code implementing functionality for reading and possibly writing Microsoft Excel files (primarily the older `.xls` BIFF format) from within the TOL environment. It appears to be based on or include code from an external library named "ExcelFormat".

## Contents

- **Excel Library Code (`BasicExcel.hpp`, `BasicExcel.cpp`, `ExcelFormat.h`, `ExcelFormat.cpp`):** These files contain the core C++ logic for parsing and handling the Excel file structure. Based on the included plain text `README`, this might be derived from the "ExcelFormat" library (potentially from `http://shell.franken.de/svn/sky/excel/trunk/ExcelFormat`).
- **TOL Binding (`tolExcel.cpp`):** This C++ file provides the interface between the Excel handling code and the TOL interpreter. It defines functions callable from TOL scripts (e.g., `ExcelRead`, `ExcelWrite`) that utilize the `BasicExcel` functionality.
- **Build Integration (`Jamfile`):** Configures the compilation of this module within the Boost Jam build system.
- **Tests (`tests/`):** Subdirectory containing test cases (likely `.tol` scripts and sample `.xls` files) to verify the Excel reading/writing functionality.
- **`README`:** Original plain text README file with notes on the source origin and Linux build considerations.

## Purpose

This contributed module allows TOL users to directly read data from `.xls` files into TOL data structures (like matrices or sets) and potentially write TOL data back to `.xls` files. This facilitates data exchange between TOL and Microsoft Excel.

## Appendix

- **Implementation Language:** C++.
- **Dependencies:** None explicitly listed besides standard C++ libraries (though the original `README` hints at `libxls` as a potential alternative).
- **Build:** Integrated via Boost Jam (`Jamfile`). 