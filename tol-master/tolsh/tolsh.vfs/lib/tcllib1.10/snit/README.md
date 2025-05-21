# Snit Package

This directory contains the Tcllib `snit` package (Snit's Not Incr Tcl), a pure-Tcl object-oriented programming (OOP) framework.

## Files

*   `snit.tcl`: Main entry point or loader for Snit version 1.
*   `snit2.tcl`: Main entry point or loader for Snit version 2.
*   `main1.tcl`, `main1_83.tcl`: Core implementation files for Snit version 1 (with compatibility for Tcl 8.3).
*   `main2.tcl`: Core implementation file for Snit version 2.
*   `snit_tcl83_utils.tcl`: Utility functions specifically for Tcl 8.3 compatibility within Snit version 1.
*   `validate.tcl`: Procedures for validating Snit type definitions and options.
*   `pkgIndex.tcl`: The package index file for loading different versions of the `snit` package.

## Purpose

Snit provides a powerful yet lightweight object system for Tcl, implemented entirely in Tcl script. It allows defining types (classes) with methods, attributes (variables), inheritance (via delegation), and other OO features without requiring compiled extensions. It's designed to be simple to learn and use while providing significant organizational benefits for larger Tcl applications.

## Usage

```tcl
package require snit

# Example (Snit version 1 or 2 - syntax differs slightly)
snit::type MyType {
    variable myData 0

    constructor {args} {
        # initialization code
    }

    method doSomething {value} {
        set myData $value
        return "Done with $myData"
    }
}

MyType obj1
puts [obj1 doSomething 42]
```

Refer to the official Snit documentation within Tcllib for detailed syntax and features of each version. 