#!/bin/env python3

"""Test for 5-16 task."""

from functools import partial
from itertools import pairwise

from common import Test, Tests, run_tests

EXE = 'ex516'


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
    num: bool = False,
    rev: bool = False,
    icase: bool = False,
    dirord: bool = False,
) -> bool:
    cmp_fun = _cmp_num if num else _cmp_lex
    reverse_mul = -1 if rev else 1
    listlines = lines.splitlines()
    if dirord:
        listlines = [
            ''.join(c for c in line if c.isalnum() or c.isspace())
            for line in listlines
        ]
    if icase:
        listlines = map(str.lower, listlines)
    for left, right in pairwise(listlines):
        if cmp_fun(left, right) * reverse_mul > 0:
            return False
    return True


tests: Tests = (
  Test(1, # Basic directory order sort with -d
  'apple!\nbanana?\napple.\ntest123\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(2, # Directory order vs normal comparison
  'file.txt\nfile!txt\nfile@txt\n',
  'file!txt\nfile.txt\nfile@txt\n',
  0, f'{EXE}'),

  Test(3, # Directory order ignores special chars
  'file.txt\nfile!txt\nfile@txt\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(4, # Directory order with case folding
  'Apple!\napple.\nBanana?\nbanana\n',
  partial(_is_sorted, dirord=True, icase=True),
  0, f'{EXE} -df'),

  Test(5, # Directory order with reverse
  'test1\ntest!2\ntest 3\ntest@4\n',
  partial(_is_sorted, dirord=True, rev=True),
  0, f'{EXE} -dr'),

  Test(6, # Directory order with numeric
  'file10\nfile2\nfile@5\nfile 1\n',
  partial(_is_sorted, dirord=True, num=True),
  0, f'{EXE} -dn'),

  Test(7, # All flags together: -dfr
  'Test!\ntest.\nApple?\napple\n',
  partial(_is_sorted, dirord=True, icase=True, rev=True),
  0, f'{EXE} -dfr'),

  Test(8, # Directory order with punctuation heavy
  'a!!!b\na@@@b\na   b\naAAA\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(9, # Directory order preserves spaces within comparison
  'hello world\nhello\nhelloworld\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(10, # Directory order with numbers and letters only
  'abc123\ntest456\nfile789\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(11, # Directory order with mixed blanks
  'a\tb\na b\na  b\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(12, # Directory order numeric with special chars
  'file10!\nfile2@\nfile1#\n',
  partial(_is_sorted, dirord=True, num=True),
  0, f'{EXE} -dn'),

  Test(13, # Directory order case-insensitive numeric
  'Test10!\ntest2@\nTEST1#\n',
  partial(_is_sorted, dirord=True, icase=True, num=True),
  0, f'{EXE} -dfn'),

  Test(14, # Directory order with empty and special
  '\ntest!\n\nfile.\n',
  partial(_is_sorted, dirord=True),
  0, f'{EXE} -d'),

  Test(15, # Directory order single line
  'oneline!\n',
  'oneline!\n',
  0, f'{EXE} -d'),

  Test(16, # Directory order empty input
  '',
  '',
  0, f'{EXE} -d'),

  Test(17, # Invalid flag combination
  'test\n',
  '',
  2, f'{EXE} -dx'),

  Test(18, # Directory order with all flag orderings
  'Apple!\napple.\nBanana?\nbanana\n',
  partial(_is_sorted, dirord=True, icase=True, rev=True, num=True),
  0, f'{EXE} -nfrd'),
)

run_tests(tests)
