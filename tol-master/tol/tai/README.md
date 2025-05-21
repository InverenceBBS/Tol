# TAI Time and Calendar Library (`tol-master/tol/tai/`)

## Overview

This directory contains a C library implementing precise time representation and manipulation based on the **TAI (International Atomic Time)** standard. It provides data structures and functions for handling TAI timestamps, calendar dates, UTC time, and conversions between them, with careful attention to leap seconds. This library likely forms the foundation for TOL's time-oriented features.

## Code Functionality

- **Core Data Types:** Defines C structures for:
    - `struct tai`: Represents a TAI timestamp (seconds since the TAI epoch).
    - `struct taia`: Represents TAI time with higher precision (likely including attoseconds or similar).
    - `struct caldate`: Represents a calendar date (year, month, day).
    - `struct caltime`: Represents a calendar date and time, potentially including timezone/offset information.
- **TAI Operations:** Functions for creating, comparing, adding, subtracting, packing, and unpacking `tai` and `taia` timestamps. Includes functions to get the current TAI time (`tai_now`, `taia_now`).
- **Calendar Operations:** Functions for formatting (`_fmt`), parsing (`_scan`), normalizing, and performing calculations on `caldate` and `caltime` structures. Includes conversions involving Modified Julian Dates (MJD).
- **Leap Second Management:**
    - `leapsecs.c`, `leapsecs.h`, `leapsecs.dat`: Implements logic to handle leap seconds, which define the difference between TAI and UTC. Includes functions to load (`leapsecs_read`, `leapsecs_init`) and apply (`leapsecs_add`, `leapsecs_sub`) leap second corrections.
- **UTC Conversion:** Functions (`caltime_utc`, `nowutc.c`) specifically for converting between the internal TAI/calendar representations and UTC.
- **Documentation (`*.3`):** Man pages documenting the library's public API.
- **Build System (`Makefile.am`):** Autotools configuration to build this library.

## Purpose

This library provides TOL with a robust and precise timekeeping foundation based on the TAI standard. Its key features are:
- Unambiguous time representation (TAI doesn't have leap second discontinuities).
- Accurate conversions between TAI, UTC, and human-readable calendar dates/times.
- Correct handling of leap seconds, essential for accurate time series analysis and data alignment.
This functionality is critical for a "Time-Oriented Language".

## Appendix

- **Implementation Language:** C.
- **Standard:** Based on TAI (International Atomic Time).
- **Build:** Compiled likely as a static or shared library linked into the core TOL interpreter. 