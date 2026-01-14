#!/bin/env bash

FIN=fileinput.txt
FOUT=fileoutput.txt

# TODO: this big chunk of code that finds the latest changes can be probably
# done via Make more easier
filename=$1
if [[ -z "$filename" ]]; then
  last_edited=$(find src -type f -name '*.c' -not -name 'myutils.*' -printf '%T@ %p\n' | sort | tail -1 | cut -d' ' -f2)
  if [[ ! $last_edited =~ .+\.c ]]; then
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
else
  bin_name=".bin/$filename_parent_isolated"
fi

compile_standalone() {
  gcc_warnings=\
'-Wall -Wextra -Wpedantic -Wreturn-type -Wdouble-promotion -Wfloat-conversion'
  gcc_debug_options=\
'-g -ftrivial-auto-var-init=zero -fno-omit-frame-pointer'
  gcc_includes=\
'-L.bin/lib -Isrc/lib -lmyutils -lm'
  gcc_optimizations=\
'-O0'
  gcc_sanitizations=\
'-fsanitize=undefined'

  gcc $gcc_debug_options -c src/lib/myutils.c -o .bin/lib/myutils.o
  ar rcs .bin/lib/libmyutils.a .bin/lib/myutils.o
  gcc \
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

printf '###############\n'
printf '%s\n' "${bin_name##*/}"
printf '###############\n'
printf '=== compile ===\n'
set -e
if [[
  "$filename_parent_isolated" == "src"
  || "$filename_parent_isolated" == "testfield"
]]; then
  compile_standalone
else
  compile_module
fi
set +e
printf '===  start  === (%s)\n' "$(date +"%H:%M:%S.%3N")"

$bin_name <$FIN |& tee $FOUT
return_code=${PIPESTATUS[0]}
if [[ $(tail -c1 $FOUT | wc -l) -eq 0 ]]; then
  printf '\e[7m%%\e[0m\n'
fi

printf '===   end   === (%s)\n' "$(date +"%H:%M:%S.%3N")"
if [[ "$return_code" = "0" ]]; then
  printf 'return code: %s\n' "$return_code"
else
  printf '\e[7mreturn code: %s\e[0m\n' "$return_code"
fi
