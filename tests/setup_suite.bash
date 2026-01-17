#!/bin/env bash

setup_suite() {
  PROJECT_ROOT="$( cd "$( dirname "$BATS_TEST_FILENAME" )/.." >/dev/null 2>&1 && pwd )"
  PATH="$PROJECT_ROOT/.bin:$PATH"
  export PROJECT_ROOT
}
