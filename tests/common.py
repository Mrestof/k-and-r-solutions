"""Minimal test framework."""
# ruff: noqa: T201

import os
import shlex
import subprocess
from collections.abc import Callable
from typing import LiteralString, NamedTuple

BINDIR='.bin'

type TestNum = int
type TestInp = str
type TestOut = str | Callable[[str], bool]
type TestExt = int
type TestCmd = LiteralString

class Test(NamedTuple):
    """Represent a single test."""

    no: TestNum
    input: TestInp
    exp_output: TestOut
    exp_exit_code: TestExt
    cmd: TestCmd

type Tests = tuple[Test, ...]


def _verify_output(actual: str, expected: TestOut) -> bool:
    """Verify the `actual` output with `expected` object.

    Either simply compare two strings, or feed the `actual` to
    `expected` verification function supplied by the test file.
    """
    if isinstance(expected, str):
        return actual == expected
    return expected(actual)


def _fmt(inp: str) -> str:
    return (inp
        .replace('\n', '|')
        .replace('\t', '^')
    )


def _run_test(test: Test, env: dict[str, str]) -> bool:
    tpass = False
    result = subprocess.run(  # noqa: S603 - safe, we only allow LiteralString
        shlex.split(test.cmd),
        env=env,
        capture_output=True,
        input=test.input,
        text=True,
        check=False,
    )

    if test.exp_exit_code != 0:
        tpass = result.returncode == test.exp_exit_code
    else:
        tpass = _verify_output(result.stdout, test.exp_output)

    not_pre = 'not ' if not tpass else ''
    input_fmt = test.input.replace('\n', '|')
    print(f"{not_pre}ok {test.no} - {test.cmd} \t input:'{input_fmt}'")

    if not tpass:
        if isinstance(test.exp_output, str):
            print(f'#   Expected: {_fmt(test.exp_output)}')
            print(f'#   Actual: {_fmt(result.stdout)}')
        else:
            print(f'#   Output: {_fmt(result.stdout)}')
        codes = f'{result.returncode};{test.exp_exit_code}'
        print(f'#   Exit code: {codes} (actual;expected)')

    return tpass


def run_tests(tests: Tests) -> None:
    """Run each test in `tests`, print diagnostics in (kina) TAP format."""
    tpass = tfail = 0

    env = os.environ.copy()
    env['PATH'] = f"{BINDIR}:{env['PATH']}"

    for test in tests:
        if _run_test(test, env):
            tpass += 1
        else:
            tfail += 1

    print(f"{'not ' if tfail else ''}ok:pass={tpass},fail={tfail}")
