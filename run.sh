#!/bin/env bash

#TODO: allow extensions for test scripts in tests folder

FIN=fileinput.txt
FOUT=fileoutput.txt

filename=$1
if [[ -z "$filename" ]]; then
  fmt='%T@ %p\n'
  last_edited=$({
    echo "$(find src -type f -name '*.c' ! -name 'myutils.*' -printf "$fmt")";
    echo "$(find tests -type f -name 'ex*' -printf "$fmt")";
  } | sort | tail -1 | cut -d' ' -f2)
  if [[
    ! $last_edited =~ .+\.c 
    && ! "$(dirname $last_edited)" == "tests"
  ]]; then
    printf 'usage: %s FILE\n' "$0"
    printf '(or the last edited file must be *.c)\n'
    exit 1
  fi
  filename=$last_edited
fi

if [[ ! -d ".bin/lib" ]]; then
  mkdir -p ".bin/lib"
fi

filename_parent="$(dirname $filename)"
filename_parent_isolated="${filename_parent#*/}"
if [[ "$filename_parent_isolated" == "src" ]]; then
  bin_name=".bin/${filename#*/}"
elif [[ "$filename_parent_isolated" == "testfield" ]]; then
  bin_name=".bin/tf_${filename##*/}"
elif [[ "$filename_parent_isolated" == "tests" ]]; then
  bin_name=".bin/${filename##*/}"
else
  bin_name=".bin/$filename_parent_isolated"
fi

if [[ "${bin_name##*/}" == *'.'* ]]; then
  bin_name="${bin_name%.*}"
fi

if [[ -d "tests/${bin_name##*/}" ]]; then
  test_name="tests/${bin_name##*/}/main"
elif [[ -f "tests/${bin_name##*/}" ]]; then
  test_name="tests/${bin_name##*/}"
fi

compile_standalone() {
  gcc_std='-std=c23'
  gcc_warnings=\
'-Wall -Wextra -Wpedantic -Wreturn-type -Wdouble-promotion -Wfloat-conversion'
  gcc_debug_options=\
'-g -ftrivial-auto-var-init=zero -fno-omit-frame-pointer'
  gcc_includes=\
'-L.bin/lib -Isrc/lib -lmyutils -lm -lbsd'
  gcc_optimizations=\
'-O0'
  gcc_sanitizations=\
'-fsanitize=undefined'

  gcc \
    $gcc_std \
    $gcc_optimizations \
    $gcc_debug_options \
    $gcc_warnings \
    -c src/lib/myutils.c -o .bin/lib/myutils.o
  ar rcs .bin/lib/libmyutils.a .bin/lib/myutils.o
  gcc \
    $gcc_std \
    $gcc_optimizations \
    $gcc_sanitizations \
    $gcc_debug_options \
    $gcc_warnings \
    -o $bin_name $filename \
    $gcc_includes
}

compile_module() {
  make -s --directory="${filename_parent}"
  cp "${filename_parent}/main" "${bin_name}"
}

run_executable() {
  $bin_name <$FIN |& tee $FOUT
  return_code=${PIPESTATUS[0]}
  if [[ $(tail -c1 $FOUT | wc -l) -eq 0 ]]; then
    printf '\e[7m%%\e[0m\n'
  fi
}

_color_tap() {
  local GREEN='\033[0;32m'
  local YELLOW='\033[1;33m'
  local RESET='\033[0m'
  local color=""

  while IFS= read -r line; do
      [[ "$line" =~ ^ok ]] && color="$GREEN"
      [[ "$line" =~ ^not\ ok ]] && color="$YELLOW"
      echo -e "${color}${line}${RESET}"
  done
}

run_test() {
  $test_name | _color_tap | tee $FOUT
  return_code=${PIPESTATUS[0]}
  if [[ $(tail -c1 $FOUT | wc -l) -eq 0 ]]; then
    printf '\e[7m%%\e[0m\n'
  fi
}

time_it() {
  TIMEFORMAT='time: %2Rs'
  { time $1 ; } 2>&1
}

printf '###############\n'
printf '%s\n' "${bin_name##*/}"
printf '###############\n'
printf '=== compile ===\n'
set -e
# NOTE: might be an issue if test is written before bin exists, edge case idc
if [[ "$filename_parent_isolated" != 'tests' ]]; then
  if [[
    "$filename_parent_isolated" == "src"
    || "$filename_parent_isolated" == "testfield"
  ]]; then
    compile_standalone
  else
    compile_module
  fi
fi
set +e

if [[ -z "$test_name" ]]; then
  printf '=== run bin === (%s)\n' "$(date +"%H:%M:%S.%3N")"
  time_it run_executable
else
  printf '=== run tst === (%s)\n' "$(date +"%H:%M:%S.%3N")"
  time_it run_test
fi
printf '===   end   === (%s)\n' "$(date +"%H:%M:%S.%3N")"

if [[ "$return_code" = "0" ]]; then
  printf 'return code: %s\n' "$return_code"
else
  printf '\e[7mreturn code: %s\e[0m\n' "$return_code"
fi
