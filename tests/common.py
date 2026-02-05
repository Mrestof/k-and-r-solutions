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
type TestExt = int
type TestCmd = LiteralString

class TestOut(NamedTuple):
    """Things that help you verify the test output.

    Always have a `string` expected test output.
    If `verifn` is None, the `string` is supposed to be used to verify the
    program output. If `verifn` is not None, feed the program output to it to
    verify it, this is useful for unstable tests.
    """

    string: str
    verifn: None | Callable[[str], bool] = None

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

    Either simply compare two strings, orfeed the `actual` to
    a verification function supplied by the test file.
    """
    if expected.verifn is None:
        return actual == expected.string
    return expected.verifn(actual)


def _fmt(inp: str) -> str:
    return (inp
        .replace('\n', '|')
        .replace('\t', '^')
    )


def run_test(test: Test) -> bool:
    """Run `test`, print diagnostics in (kind of) a TAP format."""
    tpass = False

    env = os.environ.copy()
    env['PATH'] = f"{BINDIR}:{env['PATH']}"
    result = subprocess.run(  # noqa: S603 - safe, we only allow LiteralString
        shlex.split(test.cmd),
        env=env,
        capture_output=True,
        input=test.input,
        text=True,
        check=False,
    )

    tpass = result.returncode == test.exp_exit_code
    if test.exp_exit_code == 0:
        tpass = tpass and _verify_output(result.stdout, test.exp_output)

    not_pre = 'not ' if not tpass else ''
    print(f'{not_pre}ok {test.no} - {test.cmd}')
    print(f'#   eca:{result.returncode}  inp:"{_fmt(test.input)}"')
    print(f'#   ece:{test.exp_exit_code}  out:"{_fmt(result.stdout)}"')
    print(f'#          exp:"{_fmt(test.exp_output.string)}"')

    return tpass


def run_tests(tests: Tests) -> None:
    """Run each test in `tests`, print diagnostics in (kind of) a TAP format."""
    tpass = tfail = 0

    for test in tests:
        if run_test(test):
            tpass += 1
        else:
            tfail += 1

    print(f"{'not ' if tfail else ''}ok:pass={tpass},fail={tfail}")
