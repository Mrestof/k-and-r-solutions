#!/bin/env bash

while true; do
  cat <(ls fileinput.txt run.sh) <(find src -type f) |entr -dr sh -c './run.sh | ts %.T | sed -E "s/^([0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{3})[0-9]*/\1|/"'
  sleep 1
done
