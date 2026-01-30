BINDIR='.bin'
PATH="$BINDIR:$PATH"

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
    ((PASS++))
  else
    echo -n "not "
    ((FAIL++))
  fi

  echo "ok $test_num - "${cmd[@]}" \t input:'$(echo -n "$input" | tr '\n' '|')'"

  if [ "$pass" = false ]; then
    echo "#   Expected: $(echo -en "$expected" | tr '\n' '|')"
    echo "#   Actual:   $(echo -en "$actual" | tr '\n' '|')"
    echo "#   Expected exit code: $expected_exit"
    echo "#   Actual exit code: $exit_code"
  fi
}

run_tests() {
  local tests=("$@")

  local pass=0
  local fail=0

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
  echo "ok:pass=$pass,fail=$fail"
}
