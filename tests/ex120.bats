setup() {
  bats_load_library bats-file
  bats_load_library bats-assert
  bats_load_library bats-support
}

# Basic detab functionality tests

@test "Single tab at beginning: ex120 <<< '\thello'" {
    run ex120 <<< $'\thello'
    assert_success
    assert_output "        hello"
}

@test "Single tab in middle: ex120 <<< 'a\tb'" {
    run ex120 <<< $'a\tb'
    assert_success
    assert_output "a       b"
}

@test "Multiple tabs: ex120 <<< 'a\tb\tc'" {
    run ex120 <<< $'a\tb\tc'
    assert_success
    assert_output "a       b       c"
}

@test "Tab alignment test: ex120 <<< 'ab\tcd'" {
    run ex120 <<< $'ab\tcd'
    assert_success
    assert_output "ab      cd"
}

@test "Tab after 7 chars: ex120 <<< 'abcdefg\th'" {
    run ex120 <<< $'abcdefg\th'
    assert_success
    assert_output "abcdefg h"
}

@test "No tabs present: ex120 <<< 'hello world'" {
    run ex120 <<< 'hello world'
    assert_success
    assert_output "hello world"
}

@test "Empty input: ex120 <<< ''" {
    run ex120 <<< ''
    assert_success
    assert_output ""
}

@test "Only tab character: ex120 <<< '\t'" {
    run ex120 <<< $'\t'
    assert_success
    assert_output "        "
}

@test "Consecutive tabs: ex120 <<< 'a\t\tb'" {
    run ex120 <<< $'a\t\tb'
    assert_success
    assert_output "a               b"
}

@test "Mixed spaces and tabs: ex120 <<< 'a  \tb'" {
    run ex120 <<< $'a  \tb'
    assert_success
    assert_output "a       b"
}
