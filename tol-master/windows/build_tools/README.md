# TOL Windows Build Tools (`tol-master/windows/build_tools/`)

## Overview

This directory contains a collection of scripts and utilities specifically designed to facilitate the build, testing, packaging, and distribution process for the TOL project on the Microsoft Windows platform. The primary tool is `uptol.bat`, which automates the process of fetching source code, compiling, and generating standardized binary releases.

## Contents

*   **`uptol.bat` / `_uptol.bat` / `uptol_new.bat` / `_uptol_new.bat`:** Core batch scripts for updating and building TOL components (TOL, TolTcl, Tolbase). They handle fetching source code (originally from CVS), compilation (using Visual C++ via the `STARTENV` environment), testing, and potentially packaging/distribution. The `README` (plain text file) in this directory provides detailed help for `uptol.bat`.
*   **`README`:** Plain text help file for the `uptol.bat` script.
*   **`startenv.lnk`:** Windows shortcut likely used to launch the necessary development command prompt environment (`STARTENV`) required by `uptol.bat`.
*   **`sdkenv.bat`:** Batch script probably used to set up environment variables specific to a particular SDK version needed for compilation.
*   **`build_tol_sdk/`:** A subdirectory, potentially containing tools or scripts related to building a TOL Software Development Kit (SDK).
*   **`postbuild.bat`:** Batch script executed after the main build process, possibly for cleanup or final packaging steps.
*   **`create_tag_build.bat`:** Batch script for creating build tags, likely in the version control system (originally CVS).
*   **`download_default_packages.bat`:** Script to download necessary default TOL packages.
*   **`exclude.lst`:** A list of file/directory patterns to be excluded during certain operations (e.g., copying, packaging).
*   **`log2clog.exe`:** An executable utility, likely used to convert build or commit logs into a standard ChangeLog format.
*   **`mailtdt.exe`:** An executable utility; its exact purpose is unclear but might involve emailing build reports or test data (`tdt`).
*   **`send_win-tol-contrib_2web.bat`:** Batch script presumably for uploading the `win-tol-contrib` package to a web server.
*   **`NSIS` Dependency (Implied):** The `uptol.bat` script uses NSIS (Nullsoft Scriptable Install System) for packaging, indicating `.nsi` script files might be present elsewhere or generated dynamically.
*   **Other Dependencies (Implied):** `uptol.bat` requires external tools like `WGET` and `PuTTY` (`plink`, `pscp`) to be available in the system `PATH`.

## Purpose

The primary purpose of this directory is to provide the necessary automation and tooling for developers maintaining the Windows builds of TOL. It centralizes scripts for common tasks like updating from version control, compiling different components, running tests, creating installers, and distributing releases. The `uptol.bat` script is the central orchestrator for these tasks.

## Appendix

*   **Technology:** Batch Scripting (Windows), NSIS, External Utilities (WGET, PuTTY)
*   **Build System:** Relies on Visual C++ compiler invoked via batch scripts within a specific command-line environment (`STARTENV`).
*   **Version Control:** Originally designed for CVS. 