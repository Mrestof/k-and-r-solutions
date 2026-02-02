#!/bin/bash

source tests/common.bash

EXE="ex512"

tests=(
  1 # Detab shorthand -1 +4
  $'\thello\n'
  $' hello\n'
  0 "$EXE detab -1 +4"

  2 # Entab shorthand -1 +4
  $' hello\n'
  $'\thello\n'
  0 "$EXE entab -1 +4"

  3 # Detab shorthand -5 +8
  $'a\tb\n'
  $'a    b\n'
  0 "$EXE detab -5 +8"

  4 # Entab shorthand -5 +8
  $'a    b\n'
  $'a\tb\n'
  0 "$EXE entab -5 +8"

  5 # Detab multiple tabs with shorthand
  $'\t\thello\n'
  $'     hello\n'
  0 "$EXE detab -1 +4"

  6 # Entab multiple tab stops
  $'     hello\n'
  $'\t\thello\n'
  0 "$EXE entab -1 +4"

  7 # Detab shorthand -3 +6
  $'ab\tc\td\n'
  $'ab c     d\n'
  0 "$EXE detab -3 +6"

  8 # Entab shorthand -3 +6
  $'ab c     d\n'
  $'ab\tc\td\n'
  0 "$EXE entab -3 +6"

  9 # Detab shorthand -8 +4
  $'abcdefg\th\n'
  $'abcdefg h\n'
  0 "$EXE detab -8 +4"

  10 # Default behavior when no shorthand
  $'a       b\n'
  $'a\tb\n'
  0 "$EXE entab"
)

run_tests "${tests[@]}"
