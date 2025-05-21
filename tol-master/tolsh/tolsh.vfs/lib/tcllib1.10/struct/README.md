# README - struct Module Collection (tcllib 1.10)

## Overview

This directory contains the `struct` module collection from Tcllib 1.10, located within the `tolsh` VFS. It provides implementations of various common abstract data structures.

## Contents

### Files

- `struct.tcl` / `struct1.tcl`: Main package files, possibly just loading submodules.
- `graph.tcl` / `graph1.tcl` / `graph_tcl.tcl` / `graph_c.tcl`: Implementations for graph data structures (nodes, edges). May include pure Tcl and C-accelerated versions.
- `list.tcl`: Enhanced list operations beyond Tcl's built-ins, potentially including linked lists or other list variants.
- `matrix.tcl` / `matrix1.tcl`: Implementations for matrix (2D array) data structures and operations.
- `pool.tcl`: Implementation of a pool data structure, likely for managing reusable objects or resources.
- `prioqueue.tcl`: Implementation of a priority queue.
- `queue.tcl`: Implementation of a standard queue (FIFO).
- `record.tcl`: Defines mechanisms for creating and manipulating record-like structures (similar to C structs or Pascal records).
- `sets.tcl` / `sets_tcl.tcl` / `sets_c.tcl`: Implementations for set data structures. May include pure Tcl and C-accelerated versions.
- `skiplist.tcl`: Implementation of a skiplist data structure.
- `stack.tcl`: Implementation of a stack (LIFO).
- `tree.tcl` / `tree1.tcl` / `tree_tcl.tcl` / `tree_c.tcl`: Implementations for tree data structures. May include pure Tcl and C-accelerated versions.
- `pkgIndex.tcl`: Standard Tcl package index file for all the structure sub-packages.

### Subdirectories

None.

## Purpose

The purpose of this collection is to provide Tcl developers with ready-to-use implementations of fundamental data structures. These structures (graphs, matrices, queues, stacks, sets, trees, etc.) are essential building blocks for many algorithms and applications, simplifying development by offering standardized and efficient implementations.

## Appendix

N/A 