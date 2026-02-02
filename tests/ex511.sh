#!/bin/bash

source tests/common.bash

EXE="ex511"

tests=(
  1 # Default detab (no args)
  $'a\tb\n'
  $'a       b\n'
  0 "$EXE detab"

  2 # Custom detab stops 4 8
  $'a\tb\tc\n'
  $'a   b   c\n'
  0 "$EXE detab 4 8"

  3 # Single detab stop
  $'a\tb\n'
  $'a   b\n'
  0 "$EXE detab 4"

  4 # Multiple detab stops
  $'ab\tc\td\te\n'
  $'ab c  d   e\n'
  0 "$EXE detab 3 6 10"

  5 # Default entab (no args)
  $'a       b\n'
  $'a\tb\n'
  0 "$EXE entab"

  6 # Custom entab stops 4 8
  $'a   b   c\n'
  $'a\tb\tc\n'
  0 "$EXE entab 4 8"

  7 # Single entab stop
  $'a   b\n'
  $'a\tb\n'
  0 "$EXE entab 4"

  8 # Multiple entab stops
  $'ab c  d   e\n'
  $'ab\tc\td\te\n'
  0 "$EXE entab 3 6 10"

  9 # Partial entab spaces
  $'a  b\n'
  $'a  b\n'
  0 "$EXE entab 4"

  10 # No spaces or tabs
  $'hello world\n'
  $'hello world\n'
  0 "$EXE entab 4 8"
)

run_tests "${tests[@]}"
