# README - page Module Plugins (tcllib 1.10)

## Overview

This directory contains various plugins for the `page` (Parser GEnearator) module within Tcllib 1.10, as used in the `tolsh` VFS. These plugins extend the core functionality of `page` by providing different readers, writers, and transformation capabilities for grammars and parse trees.

## Contents

### Files

- `config_peg.tcl`: Configuration specific to PEG plugins.
- `pkgIndex.tcl`: Standard Tcl package index file for the plugins.

**Reader Plugins:**
- `reader_hb.tcl`: Reads grammars/trees in 'hb' format.
- `reader_lemon.tcl`: Reads grammars/trees in Lemon format.
- `reader_peg.tcl`: Reads grammars/trees in standard PEG format.
- `reader_ser.tcl`: Reads serialized grammar/tree format.
- `reader_treeser.tcl`: Reads serialized tree format.

**Transformation Plugins:**
- `transform_mecpu.tcl`: Applies transformations related to the `mecpu` backend.
- `transform_reachable.tcl`: Applies reachability analysis transformations.
- `transform_realizable.tcl`: Applies realizability analysis transformations.

**Writer Plugins:**
- `writer_hb.tcl`: Writes grammars/trees in 'hb' format.
- `writer_identity.tcl`: Writes output identical to input (identity transformation).
- `writer_me.tcl`: Writes grammars/trees in 'me' format.
- `writer_mecpu.tcl`: Writes output targeting the `mecpu` backend.
- `writer_null.tcl`: A null writer (produces no output).
- `writer_peg.tcl`: Writes grammars/trees in standard PEG format.
- `writer_ser.tcl`: Writes grammars/trees in serialized format.
- `writer_tpc.tcl`: Writes grammars/trees in 'tpc' format.
- `writer_tree.tcl`: Writes parse trees.

### Subdirectories

None.

## Purpose

The purpose of this directory is to provide a collection of plugins that augment the `page` module. These plugins allow `page` to interact with different grammar formats (reading and writing) and perform various analyses and transformations on the grammars or resulting parse trees.

## Appendix

N/A 