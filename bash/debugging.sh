#!/usr/bin/env bash
# Log std(out|err) to file.
# Drop this at the beginning of a shell script.

set -x
SCRIPT_NAME=${0##*/}
DATE=$(date "+%Y-%m-%d-%H%M%S")
LOG_FILE="/tmp/${SCRIPT_NAME}_${date}.log"
# Ref: http://stackoverflow.com/questions/3173131/redirect-copy-of-stdout-to-log-file-from-within-bash-script-itself
exec >  >(tee -a "$LOG_FILE")
exec 2> >(tee -a "$LOG_FILE" >&2)
