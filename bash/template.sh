#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail
[[ "${TRACE-0}" =~ ^1|t|y|true|yes$ ]] && set -o xtrace

SCRIPT_NAME=${0##*/}
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "$SCRIPT_DIR"

IFS= read -rd '' USAGE <<EOF || :
This script ....
Usage: $ ${SCRIPT_NAME} -h [-c count]
EOF


arg_c="def_val"
while getopts ":c:h?" opt; do
	case "$opt" in
		c) arg_c="$OPTARG";;
		:) echo "Option -$OPTARG requires an argument." >&2; exit 1;;
		h|?|*) echo -e "$USAGE"; exit 0;;
	esac
done
shift $((OPTIND - 1))

echo "$arg_c"
