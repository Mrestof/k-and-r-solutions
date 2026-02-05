"""Minimal test framework."""
# ruff: noqa: T201

import os
import shlex
import subprocess
import sys
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
    timeout_s: int = 2

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


def _print_result(
    test: Test,
    result: subprocess.CompletedProcess | None = None,
    *,
    tpass: bool,
) -> None:
    not_pre = 'not ' if not tpass else ''
    print(f'{not_pre}ok {test.no} - {test.cmd}')

    res_ret = '?' if result is None else result.returncode
    res_out = '?' if result is None else result.stdout
    print(f'#   ece:{test.exp_exit_code}  inp:"{_fmt(test.input)}"')
    print(f'#   eca:{res_ret}  out:"{_fmt(res_out)}"')
    print(f'#          exp:"{_fmt(test.exp_output.string)}"')

    sys.stdout.flush()


def run_test(test: Test) -> bool:
    """Run `test`, print diagnostics in (kind of) a TAP format."""
    env = os.environ.copy()
    env['PATH'] = f"{BINDIR}:{env['PATH']}"
    try:
        # the noqa below is safe, we only allow LiteralString for test.cmd
        result = subprocess.run(  # noqa: S603
            shlex.split(test.cmd),
            env=env,
            capture_output=True,
            timeout=test.timeout_s,
            input=test.input,
            text=True,
            check=False,
        )
    except subprocess.TimeoutExpired:
        # in case the process goes into an infinite loop, might cause an OOM
        _print_result(test, tpass=False)
        return False

    tpass = result.returncode == test.exp_exit_code
    if test.exp_exit_code == 0:
        tpass = tpass and _verify_output(result.stdout, test.exp_output)

    _print_result(test, result, tpass=tpass)

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
