# Finite Automata Grammar Package (grammar::fa)

This directory contains the Tcllib `grammar::fa` package, providing tools for working with Finite Automata (FA), including Deterministic Finite Automata (DFA) and Non-deterministic Finite Automata (NFA).

## Files

*   `dacceptor.tcl`: Procedures related to creating and using deterministic acceptors.
*   `dexec.tcl`: Procedures for executing deterministic finite automata.
*   `fa.tcl`: Core procedures for defining, manipulating, and analyzing finite automata.
*   `faop.tcl`: Operations on finite automata (e.g., union, intersection, minimization, determinization).
*   `pkgIndex.tcl`: The package index file for loading `grammar::fa` and its components.

## Usage

This package allows Tcl applications to define, manipulate, and use finite automata for tasks like pattern matching, lexical analysis, or language recognition.

```tcl
package require grammar::fa

# Example Usage (Conceptual - Refer to .tcl files or Tcllib documentation)

# Create a finite automaton
# grammar::fa create my_fa ...

# Add states and transitions
# grammar::fa add state $my_fa ...
# grammar::fa add transition $my_fa ...

# Perform operations (e.g., determinize, minimize)
# set my_dfa [grammar::fa::op determinize $my_nfa]
# set min_dfa [grammar::fa::op minimize $my_dfa]

# Check if a string is accepted
# set accepted [grammar::fa::dacceptor::accepts $min_dfa $input_string]
```

Refer to the Tcl files within this directory or the official Tcllib documentation for comprehensive details on the available procedures. 