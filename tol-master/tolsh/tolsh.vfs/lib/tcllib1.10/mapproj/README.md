# Map Projections Package (mapproj)

This directory contains the Tcllib `mapproj` package, providing procedures for performing various cartographic map projections.

## Files

*   `mapproj.tcl`: The core implementation containing procedures for different map projection algorithms (e.g., Mercator, Lambert Conformal Conic, Albers Equal Area, etc.).
*   `pkgIndex.tcl`: The package index file, enabling loading via `package require mapproj`.

## Usage

This package allows Tcl applications to convert geographic coordinates (latitude/longitude) into projected coordinates (x, y) for display on flat maps, and potentially perform the inverse projection.

```tcl
package require mapproj

# Example Usage (Conceptual - Refer to mapproj.tcl or Tcllib documentation)

# Define projection parameters (e.g., for Mercator)
# mapproj::projection config Mercator ?options...?

# Project geographic coordinates (lat, lon) to Cartesian (x, y)
# set xy [mapproj::projection forward Mercator $lat $lon]
# set x [lindex $xy 0]
# set y [lindex $xy 1]

# Perform inverse projection (x, y to lat, lon)
# set latlon [mapproj::projection inverse Mercator $x $y]
# set lat [lindex $latlon 0]
# set lon [lindex $latlon 1]

# List available projections
# set projections [mapproj::projection names]
```

Consult the `mapproj.tcl` file or the official Tcllib documentation for the list of supported projections, required parameters, and detailed usage. 