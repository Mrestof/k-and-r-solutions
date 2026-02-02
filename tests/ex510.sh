#!/bin/bash

source tests/common.bash

EXE="ex510"

tests=(
  1 # Simple addition
  $''
  $'3\n'
  0 "$EXE 1 2 +"

  2 # Multi-step calculation
  $''
  $'5\n'
  0 "$EXE 15 7 1 1 + - / 3 \* 2 1 1 + + -"

  3 # Negative numbers
  $''
  $'-2\n'
  0 "$EXE -5 3 +"

  4 # Floating point arithmetic
  $''
  $'6\n'
  0 "$EXE 3.5 2.5 +"

  5 # Single operand passthrough
  $''
  $'42\n'
  0 "$EXE 42"

  6 # Modulo operation
  $''
  $'1\n'
  0 "$EXE 10 3 %"

  7 # Division by zero (should fail)
  $''
  $''
  1 "$EXE 5 0 /"

  8 # Insufficient operands (should fail)
  $''
  $''
  1 "$EXE 1 +"

  9 # Invalid operator (should fail)
  $''
  $''
  1 "$EXE 1 2 @"

  10 # No arguments (should fail)
  $''
  $''
  1 "$EXE"
)

run_tests "${tests[@]}"
