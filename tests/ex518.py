#!/bin/env python3
# ruff: noqa: E501

"""Test for 5-18 task."""

from common import Test, TestOut, Tests, run_tests

EXE = 'ex518'

tests: Tests = (
    Test(1, # Simple int variable
    'int x\n',
    TestOut('x: int\n'),
    0, f'{EXE} dwc'),

    Test(2, # Pointer to char
    'char *p\n',
    TestOut('p: pointer to char\n'),
    0, f'{EXE} dwc'),

    Test(3, # Array of int
    'int arr[10]\n',
    TestOut('arr: array[10] of int\n'),
    0, f'{EXE} dwc'),

    Test(4, # Function returning int
    'int func()\n',
    TestOut('func: function returning int\n'),
    0, f'{EXE} dwc'),

    Test(5, # Pointer to array from book
    'int (*daytab)[13]\n',
    TestOut('daytab: pointer to array[13] of int\n'),
    0, f'{EXE} dwc'),

    Test(6, # Pointer to function
    'int (*pf)()\n',
    TestOut('pf: pointer to function returning int\n'),
    0, f'{EXE} dwc'),

    Test(7, # Missing closing paren
    'int (*ptr\n',
    TestOut('error: missing )\n'),
    0, f'{EXE} dwc'),

    Test(8, # Missing closing bracket
    'int arr[10\n',
    TestOut('error: missing ]\n'),
    0, f'{EXE} dwc'),

    Test(9, # Missing name after type
    'int *\n',
    TestOut('error: expected name or (dcl)\n'),
    0, f'{EXE} dwc'),

    Test(10, # Missing name in parens
    'int (*)\n',
    TestOut('error: expected name or (dcl)\n'),
    0, f'{EXE} dwc'),

    Test(11, # Double opening paren no close
    'int ((*p)\n',
    TestOut('error: missing )\n'),
    0, f'{EXE} dwc'),

    Test(12, # Empty parens where name expected
    'int ()\n',
    TestOut('error: expected name or (dcl)\n'),
    0, f'{EXE} dwc'),

    Test(13, # Recover and continue to next line
    'int (*ptr\nchar *p\n',
    TestOut('error: missing )\nptr: pointer to int\np: pointer to char\n'),
    0, f'{EXE} dwc'),

    Test(14, # Multiple errors recovery
    'int *\nint arr[10\nchar c\n',
    TestOut('error: expected name or (dcl)\n: pointer to int\nerror: missing ]\narr: array[10 of int\nc: char\n'),
    0, f'{EXE} dwc'),

    Test(15, # Syntax error junk after declaration
    'int x y\n',
    TestOut('syntax error\nx: int\n'),
    0, f'{EXE} dwc'),

    Test(16, # Valid after error
    'int [\nint x\n',
    TestOut('error: expected name or (dcl)\n: array[ of int\nx: int\n'),
    0, f'{EXE} dwc'),

    Test(17, # wdc simple pointer
    'x * int\n',
    TestOut('int (*x)\n'),
    0, f'{EXE} wdc'),

    Test(18, # wdc array
    'arr [10] int\n',
    TestOut('int arr[10]\n'),
    0, f'{EXE} wdc'),

    Test(19, # wdc function
    'func () int\n',
    TestOut('int func()\n'),
    0, f'{EXE} wdc'),

    Test(20, # wdc invalid token
    'x @ int\n',
    TestOut('invalid input at @\nint x\n'),
    0, f'{EXE} wdc'),

    Test(21, # No arguments exits with 1
    '',
    TestOut(''),
    1, f'{EXE}'),

    Test(22, # Invalid mode argument
    '',
    TestOut(''),
    1, f'{EXE} invalid'),
)

run_tests(tests)
