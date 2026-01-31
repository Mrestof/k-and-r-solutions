BINDIR='.bin'
PATH="$BINDIR:$PATH"

# NOTE: pass those as namerefs in case of issues due to them being global
_PASS=0
_FAIL=0

run_test() {
  local test_num="$1"
  local input="$2"
  local expected="$3"
  local expected_exit="$4"
  local cmd="$5"

  local pass=false

  local actual=$(echo -n "$input" | eval "$cmd" 2>&1; echo "x$?")
  local exit_code="${actual##*x}"
  actual=${actual%x*}

  if [[
   ( $exit_code -eq 0 && "$actual" == "$expected" )
   || ( $exit_code -ne 0 && $exit_code -eq $expected_exit )
  ]]; then
    pass=true
    ((_PASS++))
  else
    echo -n "not "
    ((_FAIL++))
  fi

  echo "ok $test_num - "${cmd[@]}" \t input:'$(echo -n "$input" | tr '\n' '|')'"

  if [ "$pass" = false ]; then
    echo "#   Expected: '$(echo -en "$expected" | tr '\n' '|')'"
    echo "#   Actual:   '$(echo -en "$actual" | tr '\n' '|')'"
    echo "#   Exit code: $exit_code;$expected_exit (actual;expected)"
  fi
}

run_tests() {
  local tests=("$@")

  for ((i=0; i<${#tests[@]}; i+=5)); do
    local test_num="${tests[$i]}"
    local input="${tests[$((i+1))]}"
    local expected="${tests[$((i+2))]}"
    local expected_exit="${tests[$((i+3))]}"
    local cmd="${tests[$((i+4))]}"

    run_test "$test_num" "$input" "$expected" "$expected_exit" "$cmd"
  done

  if [[ $fail -gt 0 ]]; then
    echo -n 'not '
  fi
  echo "ok:pass=$_PASS,fail=$_FAIL"
}
