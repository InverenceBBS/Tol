# URI / URN Packages

This directory contains Tcllib packages for handling Uniform Resource Identifiers (URIs) and Uniform Resource Names (URNs).

## Files

*   `uri.tcl`: Core implementation for parsing and manipulating URIs (including URLs). It likely handles components like scheme, authority, path, query, and fragment according to relevant RFCs.
*   `urn-scheme.tcl`: Specific handling for the URN scheme (Uniform Resource Name) as defined in RFC 2141 and related RFCs.
*   `pkgIndex.tcl`: Package index file for loading the `uri` and potentially `urn` packages.

## Purpose

These packages provide tools for working with standard internet resource identifiers. `uri.tcl` offers general URI parsing and manipulation, essential for web clients, servers, and other network applications. `urn-scheme.tcl` provides specialized functions for dealing with the persistent, location-independent nature of URNs.

## Usage

```tcl
package require uri
# or package require uri::urn

# Example URI usage (Conceptual)
# set url "http://user:pass@example.com:8080/path/to/resource?query=val#fragment"
# set parts [uri::split $url]
# puts [dict get $parts scheme] ; # http
# puts [dict get $parts host]   ; # example.com
# set newUrl [uri::join {scheme https host new.example.com}]

# Example URN usage (Conceptual)
# package require uri::urn
# set urn "urn:isbn:0451450523"
# if {[uri::urn::is_urn $urn]} {
#    set nid [uri::urn::nid $urn] ; # isbn
#    set nss [uri::urn::nss $urn] ; # 0451450523
# }
```

Refer to the `.tcl` files or Tcllib documentation for detailed commands. 