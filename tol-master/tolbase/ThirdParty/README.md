# Tolbase Third-Party Tcl/Tk Extensions (`tol-master/tolbase/ThirdParty/`)

## Overview

This directory contains source code archives for third-party Tcl/Tk extensions that are dependencies for the **Tolbase** GUI (`tol-master/tolbase/`). Bundling these sources allows them to be built as part of the Tolbase compilation process, ensuring their availability even if not pre-installed on the target system.

## Contents

- **Source Archives:** Compressed source code for various Tcl/Tk extensions:
    - `Img-Source-1.4.6.tar.gz`: **Tcl Img** library (v1.4.6) for expanded image format support (PNG, JPEG, etc.).
    - `Tktable2.10.tar.gz`: **TkTable** extension (v2.10) providing a table/grid widget.
    - `rbc0.1.zip`: **RBC** library (v0.1) potentially for plotting/charting widgets.
    - `tclodbc2.5_bayes.tar.gz`: **TclODBC** extension (v2.5, possibly modified) for database access via ODBC from Tcl.
    - `tktreectrl-2.4.1.tar.gz`: **TkTreeCtrl** extension (v2.4.1) providing an advanced tree list widget.
- **Build Integration (`CMakeLists.txt`):** A CMake script that likely handles:
    - Unpacking the source archives.
    - Configuring and building each Tcl/Tk extension using their respective build systems (often Autotools or simple Makefiles).
    - Ensuring the compiled extensions are available for Tolbase to use.

## Purpose

This directory serves to vendor the source code of essential Tcl/Tk extensions required by Tolbase. By including them directly and integrating their build with CMake, the project simplifies the build process for users, as they don't need to manually find, download, and install these specific versions of the extensions separately. This enhances the portability and reproducibility of the Tolbase build.

## Appendix

- **Technology:** Tcl/Tk C extensions, CMake.
- **Usage:** Used internally by the CMake build process for Tolbase. Source archives are unpacked and compiled automatically. 