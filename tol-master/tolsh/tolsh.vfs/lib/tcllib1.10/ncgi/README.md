# ncgi Package

This directory contains the Tcllib `ncgi` package, providing utilities for handling CGI (Common Gateway Interface) requests and generating responses, particularly focusing on forms and URL parsing.

## Files

*   `ncgi.tcl`: The core implementation of the `ncgi` library. It includes procedures for parsing incoming CGI data (from environment variables and standard input), decoding form data (GET and POST, including multipart/form-data), managing cookies, and generating HTTP headers and content.
*   `pkgIndex.tcl`: The package index file, making the `ncgi` package loadable via Tcl's `package require ncgi` command.

## Usage

This package simplifies writing CGI scripts in Tcl.

```tcl
package require ncgi

# Example Usage (Conceptual - Refer to ncgi.tcl or Tcllib documentation)

# Initialize and parse CGI data
# ncgi::parse

# Get form field values
# set username [ncgi::value "user"]
# set password [ncgi::value "pass"]
# set options [ncgi::value "opts"]

# Get information about uploaded files
# set fileInfo [ncgi::value "uploadfile"]
# set filename [ncgi::fileParam $fileInfo name]
# set tmpPath [ncgi::fileParam $fileInfo tmpfile]
# set mimeType [ncgi::fileParam $fileInfo type]

# Set cookies
# ncgi::cookie -name sessionID -value $newSession

# Output HTTP headers
# puts [ncgi::header "text/html"]

# Output content
# puts "<html>..."

# Cleanup (especially for file uploads)
# ncgi::reset
```

It provides a convenient interface for accessing form data, cookies, and uploaded files within a CGI environment. 