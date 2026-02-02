#!/bin/bash

source tests/common.bash

EXE="ex513"

tests=(
  1 # Default tail (10 lines)
  $'line1\nline2\nline3\nline4\nline5\nline6\nline7\nline8\nline9\nline10\nline11\nline12\n'
  $'line3\nline4\nline5\nline6\nline7\nline8\nline9\nline10\nline11\nline12\n'
  0 "$EXE"

  2 # Tail last 3 lines
  $'line1\nline2\nline3\nline4\nline5\n'
  $'line3\nline4\nline5\n'
  0 "$EXE -3"

  3 # Tail last 1 line
  $'line1\nline2\nline3\n'
  $'line3\n'
  0 "$EXE -1"

  4 # More lines requested than available
  $'line1\nline2\nline3\n'
  $'line1\nline2\nline3\n'
  0 "$EXE -10"

  5 # Empty input
  $''
  $''
  0 "$EXE -5"

  6 # Single line input
  $'oneline\n'
  $'oneline\n'
  0 "$EXE -3"

  7 # Zero lines requested
  $'line1\nline2\nline3\n'
  $''
  0 "$EXE -0"

  8 # Large input default
  $'a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\n'
  $'f\ng\nh\ni\nj\nk\nl\nm\nn\no\n'
  0 "$EXE"

  9 # Tail last 5 lines
  $'a\nb\nc\nd\ne\nf\ng\nh\n'
  $'d\ne\nf\ng\nh\n'
  0 "$EXE -5"

  10 # Exactly n lines available
  $'line1\nline2\nline3\n'
  $'line1\nline2\nline3\n'
  0 "$EXE -3"
)

run_tests "${tests[@]}"
