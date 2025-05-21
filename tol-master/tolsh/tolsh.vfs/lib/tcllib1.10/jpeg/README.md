# JPEG Package

This directory contains the Tcllib `jpeg` package, providing utilities for reading and possibly writing JPEG image format data.

## Files

*   `jpeg.tcl`: The core implementation for handling JPEG data. This likely includes procedures to parse JPEG headers, extract metadata (like dimensions, color space), and potentially manipulate image data.
*   `pkgIndex.tcl`: The package index file, enabling loading via `package require jpeg`.

## Usage

This package allows Tcl applications to inspect and potentially modify JPEG image files without relying on external libraries or tools (though performance might be limited compared to C-based libraries).

```tcl
package require jpeg

# Example Usage (Conceptual - Refer to jpeg.tcl or Tcllib documentation)

# Read JPEG header information from a file
# set info [jpeg::header -file image.jpg]
# puts "Dimensions: [dict get $info width]x[dict get $info height]"

# Read JPEG data from a channel
# set chan [open image.jpg rb]
# set data [jpeg::read $chan]
# close $chan

#Potentially write JPEG data (if supported)
# jpeg::write image_new.jpg $imageData ?options...?
```

Consult the `jpeg.tcl` file or the official Tcllib documentation for specific procedure names, options, and capabilities. 