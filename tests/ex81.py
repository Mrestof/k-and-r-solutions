#!/bin/env python3

"""Test for 8-1 task."""

from common import Test, TestFile, TestOut, Tests, run_tests

EXE = 'ex81'

tests: Tests = (
    Test(1, # stdin to stdout, simple text
    'hello world\n',
    TestOut('hello world\n'),
    0, f'{EXE}'),

    Test(2, # empty stdin
    '',
    TestOut(''),
    0, f'{EXE}'),

    Test(3, # multiline stdin
    'line1\nline2\nline3\n',
    TestOut('line1\nline2\nline3\n'),
    0, f'{EXE}'),

    Test(4, # single file arg
    '',
    TestOut('alpha\nbeta\ngamma\n'),
    0, f'{EXE} {{tmp}}/a', (
    TestFile('a', 'alpha\nbeta\ngamma\n'),
    )),

    Test(5, # two files concatenated in order
    '',
    TestOut('file-a\nfile-b\n'),
    0, f'{EXE} {{tmp}}/a {{tmp}}/b', (
    TestFile('a', 'file-a\n'),
    TestFile('b', 'file-b\n'),
    )),

    Test(6, # three files order preserved
    '',
    TestOut('first\nsecond\nthird\n'),
    0, f'{EXE} {{tmp}}/a {{tmp}}/b {{tmp}}/c', (
    TestFile('a', 'first\n'),
    TestFile('b', 'second\n'),
    TestFile('c', 'third\n'),
    )),

    Test(7, # empty file
    '',
    TestOut(''),
    0, f'{EXE} {{tmp}}/a', (
    TestFile('a', ''),
    )),

    Test(8, # file without trailing newline
    '',
    TestOut('no newline'),
    0, f'{EXE} {{tmp}}/a', (
    TestFile('a', 'no newline'),
    )),

    Test(9, # same file twice
    '',
    TestOut('line\nline\n'),
    0, f'{EXE} {{tmp}}/a {{tmp}}/a', (
    TestFile('a', 'line\n'),
    )),

    Test(10, # stdin without trailing newline
    'no newline',
    TestOut('no newline'),
    0, f'{EXE}'),

    Test(11, # missing file
    '',
    TestOut(''),
    1, f'{EXE} /definitely/missing/file'),
)

run_tests(tests)
