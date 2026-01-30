BINDIR='.bin'
PATH="$BINDIR:$PATH"

run_test() {
  local test_num="$1"
  local input="$2"
  local expected="$3"
  shift 3
  local cmd=("$@")

  local pass=false

  local actual=$(echo -n "$input" | "${cmd[@]}" 2>&1; echo x); actual=${actual%x}
  local exit_code=$?

  if [[ $exit_code -eq 0 && "$actual" == "$expected" ]]; then
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
    echo "#   Exit code: $exit_code"
  fi
}

run_tests() {
  local tests=("$@")

  local pass=0
  local fail=0

  # Run tests (every 3 elements = one test)
  for ((i=0; i<${#tests[@]}; i+=4)); do
    test_num="${tests[$i]}"
    input="${tests[$((i+1))]}"
    expected="${tests[$((i+2))]}"
    cmd="${tests[$((i+3))]}"

    eval "run_test $test_num \"\$input\" \"\$expected\" $cmd"
  done

  if [[ $fail -gt 0 ]]; then
    echo -n 'not '
  fi
  echo "ok:pass=$pass,fail=$fail"
}
