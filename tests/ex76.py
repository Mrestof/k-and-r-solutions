#!/bin/env python3

"""Test for 7-6 task."""

from common import Test, TestFile, TestOut, Tests, run_tests

EXE = 'ex76'

tests: Tests = (
    Test(1, # First differing line in middle
    '',
    TestOut(''),
    1, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'line1\nline5\nline3\n'),
    TestFile('b', 'line1\nline2\nline3\n'),
    )),

    Test(2, # First line differs
    '',
    TestOut(''),
    1, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'first-left\nline2\nline3\n'),
    TestFile('b', 'first-right\nline2\nline3\n'),
    )),

    Test(3, # Last line differs
    '',
    TestOut(''),
    1, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'line1\nline2\nlast-left\n'),
    TestFile('b', 'line1\nline2\nlast-right\n'),
    )),

    Test(4, # Whitespace-only difference
    '',
    TestOut(''),
    1, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'line1\nline two\nline3\n'),
    TestFile('b', 'line1\nline  two\nline3\n'),
    )),

    Test(5, # Right file has extra trailing line
    '',
    TestOut(''),
    1, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'line1\nline2\n'),
    TestFile('b', 'line1\nline2\nline3\n'),
    )),

    Test(6, # Left file has extra trailing line
    '',
    TestOut(''),
    1, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'line1\nline2\nline3\n'),
    TestFile('b', 'line1\nline2\n'),
    )),

    Test(7, # Identical normal files
    '',
    TestOut(''),
    0, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'alpha\nbeta\ngamma\n'),
    TestFile('b', 'alpha\nbeta\ngamma\n'),
    )),

    Test(8, # Identical empty files
    '',
    TestOut(''),
    0, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', ''),
    TestFile('b', ''),
    )),

    Test(9, # Identical files without trailing newline
    '',
    TestOut(''),
    0, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'oneline'),
    TestFile('b', 'oneline'),
    )),

    Test(10, # No arguments
    '',
    TestOut(''),
    3, f'{EXE}'),

    Test(11, # One argument only
    '',
    TestOut(''),
    3, f'{EXE} {{tmp}}/a', (
    TestFile('a', 'line1\n'),
    )),

    Test(12, # Missing left file
    '',
    TestOut(''),
    2, f'{EXE} /definitely/missing/a {{tmp}}/b', (
    TestFile('b', 'line1\n'),
    )),

    Test(13, # Missing right file
    '',
    TestOut(''),
    2, f'{EXE} {{tmp}}/a /definitely/missing/b', (
    TestFile('a', 'line1\n'),
    )),
)

run_tests(tests)
