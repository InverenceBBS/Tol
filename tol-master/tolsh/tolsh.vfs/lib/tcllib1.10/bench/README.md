# Bench Package

This directory contains the Tcllib `bench` package, providing tools for benchmarking Tcl code performance.

## Files

*   `bench.tcl`: Main script, likely for running benchmark suites.
*   `bench_read.tcl`: Utilities for reading benchmark results.
*   `bench_wcsv.tcl`: Utilities for writing benchmark results in CSV format.
*   `bench_wtext.tcl`: Utilities for writing benchmark results in plain text format.
*   `libbench.tcl`: Core library containing benchmark procedures.
*   `pkgIndex.tcl`: The package index file for loading the `bench` package.

## Usage

To use this package, load the core library into your Tcl script:

```tcl
package require bench::core
# Or potentially other sub-packages depending on need

# Example Usage (Conceptual - Refer to the .tcl files or Tcllib documentation)

# Define benchmark tests
# bench::test testName { script-to-benchmark }

# Run the defined tests
# set results [bench::run tests ?options...?]

# Format and output the results
# bench::report results ?format...? ?options...?
```

This package allows developers to systematically measure and compare the execution time of different Tcl code snippets or procedures. 