#!/usr/bin/env bash

_capture() {
  declare -n refvar="$1"
  shift
  # Quote $@ to preserve quoted strings. Ref. https://stackoverflow.com/a/39463371/265508
  local cmd="${@@Q}"
  # Preserves exit code from $cmd.
  refvar=$((eval "$cmd" | tee /dev/tty; exit ${PIPESTATUS[0]})&)
}

_capture output \
	printf "test %s, %s\n" \
	"arg1" \
	"arg2"

echo "ecode: $?"
echo "captured: $output"
