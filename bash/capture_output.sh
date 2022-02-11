#!/usr/bin/env bash
# How to capture output from a command, while still letting it though to stdout as usual (and retain command's exit code!).

# Capture output of command to variable.
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

echo -e "> ecode: $?"
echo "> captured: $output"





printf "==========\n"
# Runs command in background using coproc.
# Reference: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Coprocesses
_capture_coproc() {
	declare -n refvar="$1"
	shift
	# Quote $@ to preserve quoted strings. Ref. https://stackoverflow.com/a/39463371/265508
	local cmd="${@@Q}"
	coproc CMDPROC (eval "$cmd" | tee /dev/tty)
	read -r refvar <&"${CMDPROC[0]}"
}

_capture output_coproc \
	printf "test %s, %s\n" \
	"arg1" \
	"arg2"

echo -e "\n> ecode: $?"
echo "> captured: $output_coproc"



printf "==========\n"
# Run coproc directly.
coproc CMDPROC (\
	printf "test %s, %s\n" \
	"arg1" \
	"arg2")

read -r output_coproc_dir <&"${CMDPROC[0]}"
echo "$output_coproc_dir"

echo -e "\n> ecode: $?"
echo "> captured: $output_coproc_dir"
