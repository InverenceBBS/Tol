# BSR Missing Inputs Test (`tol-master/tol_tests/tol/BSR/test_10/`)

## Overview

This test exercise checks the BSR (Bayesian Structural Regression) module when
required inputs are missing from certain nodes. The script references bug report
`https://www.tol-project.org/ticket/622` and replicates the original scenario.

## Contents

- `test.tol` – TOL script that defines the test case and prints diagnostic
  output.

## Purpose

Used during regression testing to ensure the BSR implementation handles absent
inputs gracefully and reports clear error messages.

## Appendix

- **Technology:** TOL scripting language.
- **Usage:** Run `test.tol` with the TOL interpreter as part of the BSR test
  suite.
