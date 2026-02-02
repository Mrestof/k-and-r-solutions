#!/bin/bash

source tests/common.bash

EXE="ex120"

tests=(
  1 # Single tab at beginning
  $'\thello\n'
  $'        hello\n'
  0 "$EXE"

  2 # Single tab in middle
  $'a\tb\n'
  $'a       b\n'
  0 "$EXE"

  3 # Multiple tabs
  $'a\tb\tc\n'
  $'a       b       c\n'
  0 "$EXE"

  4 # Tab alignment test
  $'ab\tcd\n'
  $'ab      cd\n'
  0 "$EXE"

  5 # Tab after 7 chars
  $'abcdefg\th\n'
  $'abcdefg h\n'
  0 "$EXE"

  6 # No tabs present
  $'hello world\n'
  $'hello world\n'
  0 "$EXE"

  7 # Empty input
  $''
  $''
  0 "$EXE"

  8 # Only tab character
  $'\t\n'
  $'        \n'
  0 "$EXE"

  9 # Consecutive tabs
  $'a\t\tb\n'
  $'a               b\n'
  0 "$EXE"

  10 # Mixed spaces and tabs
  $'a  \tb\n'
  $'a       b\n'
  0 "$EXE"
)

run_tests "${tests[@]}"
