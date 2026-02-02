#!/bin/env python3

"""Test for 5-15 task."""

from functools import partial
from itertools import pairwise

from common import Test, Tests, run_tests

EXE = 'ex515'


def _float(s: str) -> float:
    s_valid = ''
    allowed_chars = '0123456789-+.'
    for c in s:
        if c not in allowed_chars:
            break
        s_valid += c
    try:
        return float(s_valid)
    except ValueError:
        return 0.0


def _cmp_num(s1: str, s2: str) -> float:
    s1_n = _float(s1)
    s2_n = _float(s2)
    return s1_n - s2_n


def _cmp_lex(s1: str, s2: str) -> int:
    for c1, c2 in zip(s1, s2, strict=False):
        if c1 != c2:
            return ord(c1) - ord(c2)
    return 0


def _is_sorted(
    lines: str,
    *,
    numeric: bool = False,
    reverse: bool = False,
    ignore_case: bool = False,
) -> bool:
    cmp_fun = _cmp_num if numeric else _cmp_lex
    reverse_mul = -1 if reverse else 1
    listlines = lines.splitlines()
    if ignore_case:
        listlines = map(str.lower, listlines)
    for left, right in pairwise(listlines):
        if cmp_fun(left, right) * reverse_mul > 0:
            return False
    return True


tests: Tests = (
  Test(1, # Basic case-insensitive sort with -f
  'Apple\napple\nBanana\nbanana\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(2, # Mixed case without -f (case sensitive)
  'Apple\napple\nBanana\nbanana\n',
  'Apple\nBanana\napple\nbanana\n',
  0, f'{EXE}'),

  Test(3, # Case-insensitive reverse sort
  'Apple\napple\nBanana\nbanana\n',
  partial(_is_sorted, reverse=True, ignore_case=True),
  0, f'{EXE} -rf'),

  Test(4, # Case-insensitive numeric sort
  'Apple\n10\napple\n2\nBanana\n',
  partial(_is_sorted, numeric=True, ignore_case=True),
  0, f'{EXE} -fn'),

  Test(5, # All flags together: reverse case-insensitive numeric
  'Apple\n10\napple\n2\nBanana\n',
  partial(_is_sorted, numeric=True, reverse=True, ignore_case=True),
  0, f'{EXE} -rfn'),

  Test(6, # Different flag order (should work the same)
  'Apple\napple\nBanana\nbanana\n',
  partial(_is_sorted, numeric=True, ignore_case=True),
  0, f'{EXE} -nf'),

  Test(7, # Case differences at word boundaries
  'test\nTEST\nTest\ntEsT\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(8, # Case-insensitive with special characters
  'Apple!\napple?\nApple.\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(9, # Case-insensitive with numbers in strings
  'Test2\ntest1\nTEST10\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(10, # Case-insensitive numeric with mixed case numbers
  'Test\n2a\n10A\n1B\n',
  partial(_is_sorted, numeric=True, ignore_case=True),
  0, f'{EXE} -fn'),

  Test(11, # Empty lines with case-insensitive
  'Apple\n\napple\nBanana\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(12, # Single character case differences
  'a\nA\nb\nB\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(13, # Case-insensitive with whitespace
  'Apple \napple\n Apple\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(14, # Long strings with case differences
  'verylongstring\nVERYLONGSTRING\nVeryLongString\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(15, # Case-insensitive with identical content
  'same\nsame\nSAME\nSame\n',
  partial(_is_sorted, ignore_case=True),
  0, f'{EXE} -f'),

  Test(16, # Case-insensitive numeric with floats
  '-5.2\n8.9\n0.1garbage\napple2\nbanana3\n',
  partial(_is_sorted, ignore_case=True, numeric=True),
  0, f'{EXE} -fn'),

  Test(17, # Invalid flag combination
  'test\n',
  '',
  2, f'{EXE} -fx'),

  Test(18, # Case-insensitive single line
  'OneLine\n',
  'OneLine\n',
  0, f'{EXE} -f'),

  Test(19, # Case-insensitive empty input
  '',
  '',
  0, f'{EXE} -f'),
)

run_tests(tests)
