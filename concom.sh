#!/bin/env bash

run_cmd_fmt='./run.sh | ts %.T | sed -E "s/([0-9]{3})[0-9]*/\1|/"'

while true; do
  {
    echo "$(ls fileinput.txt run.sh)";
    echo "$(find src -type f -name '*.[ch]')";
    echo "$(find tests -type f ! -name '*.pyc')";
  } | entr -dr sh -c "$run_cmd_fmt"
  sleep 1
done
