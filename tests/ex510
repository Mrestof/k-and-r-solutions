#!/bin/env bats

setup() {
  bats_load_library bats-file
  bats_load_library bats-assert
  bats_load_library bats-support
}

# Basic functionality

@test "Simple addition: ex510 1 2 +" {
    run ex510 1 2 +
    assert_success
    assert_output "3"
}

@test "Multi-step calculation with all operators: ex510 15 7 1 1 + - / 3 '*' 2 1 1 + + -" {
    run ex510 15 7 1 1 + - / 3 '*' 2 1 1 + + -
    assert_success
    assert_output "5"
}

@test "Negative numbers: ex510 -5 3 +" {
    run ex510 -5 3 +
    assert_success
    assert_output "-2"
}

@test "Floating point arithmetic: ex510 3.5 2.5 +" {
    run ex510 3.5 2.5 +
    assert_success
    assert_output "6"
}

@test "Single operand passthrough: ex510 42" {
    run ex510 42
    assert_success
    assert_output "42"
}

@test "Modulo operation: ex510 10 3 %" {
    run ex510 10 3 %
    assert_success
    assert_output "1"
}

# Error conditions

@test "Division by zero: ex510 5 0 /" {
    run ex510 5 0 /
    assert_failure
}

@test "Insufficient operands: ex510 1 +" {
    run ex510 1 +
    assert_failure
}

@test "Invalid operator: ex510 1 2 @" {
    run ex510 1 2 @
    assert_failure
}

@test "No arguments: ex510" {
    run ex510
    assert_failure
}
