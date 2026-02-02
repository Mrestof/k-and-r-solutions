#!/bin/bash

source tests/common.bash

EXE="ex121"

tests=(
  1 # Seven spaces to next tab stop
  $'a       b\n'
  $'a\tb\n'
  0 "$EXE"

  2 # Leading eight spaces
  $'        hello\n'
  $'\thello\n'
  0 "$EXE"

  3 # Sixteen spaces to two tabs
  $'                b\n'
  $'\t\tb\n'
  0 "$EXE"

  4 # Partial spaces preserved
  $'a   b\n'
  $'a   b\n'
  0 "$EXE"

  5 # Six spaces to next tab stop
  $'ab      c\n'
  $'ab\tc\n'
  0 "$EXE"

  6 # No spaces present
  $'hello world\n'
  $'hello world\n'
  0 "$EXE"

  7 # Preserve existing tabs
  $'a\tb\n'
  $'a\tb\n'
  0 "$EXE"

  8 # Multiple tab stops
  $'a       b       c\n'
  $'a\tb\tc\n'
  0 "$EXE"

  9 # Mixed tabs and spaces
  $'a\tb       c\n'
  $'a\tb\tc\n'
  0 "$EXE"

  10 # Single space preserved
  $'a b\n'
  $'a b\n'
  0 "$EXE"
)

run_tests "${tests[@]}"
