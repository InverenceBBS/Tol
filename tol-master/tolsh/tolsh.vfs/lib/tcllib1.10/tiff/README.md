# TIFF Package

This directory contains the Tcllib `tiff` package, providing utilities for reading and possibly writing Tagged Image File Format (TIFF) images.

## Files

*   `tiff.tcl`: The core implementation for handling TIFF files. It likely includes procedures for parsing the TIFF structure (IFDs - Image File Directories), extracting tags (metadata like dimensions, compression, resolution, color space), and potentially decoding image data for common compression types.
*   `pkgIndex.tcl`: The package index file, making the `tiff` package loadable via Tcl's `package require tiff` command.

## Purpose

This package allows Tcl applications to interact with TIFF image files. It enables reading metadata and potentially image data from TIFFs, which are commonly used in scanning, faxing, and graphic arts due to their ability to store image data losslessly and handle multiple images within a single file.

## Usage

```tcl
package require tiff

# Example Usage (Conceptual - Refer to tiff.tcl or Tcllib documentation)

# Open and parse a TIFF file
# set tiff_handle [tiff::open filename]

# Get image dimensions
# set width [tiff::info $tiff_handle width]
# set height [tiff::info $tiff_handle height]

# Get other tags
# set compression [tiff::info $tiff_handle compression]

# Access image data (if supported)
# set image_data [tiff::getdata $tiff_handle]

# Close the file
# tiff::close $tiff_handle
``` 