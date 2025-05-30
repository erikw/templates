#!/usr/bin/env bash
# getopts template

set -e

SCRIPT_NAME=${0##*/}
# Make $(set -e) not trigger on read(1). Reference: https://unix.stackexchange.com/a/622786
IFS= read -rd '' usage <<EOF || :
Usage: $ ${SCRIPT_NAME} -h | -c {up|down} [-i increment] [-m mixer] [-- --other --args here]
-c\tCommand to use.
-i\tHow many percentes to increment.
-m\tWhich mixer to use.
EOF


opt1="def1"
opt2="def2"

# Optional: cmd is required
if [ "$#" -eq 0 ]; then
	echo -e "$usage"
	exit 1
fi

# getopts documentation: https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html
# "An option character in this string can be followed by a colon (‘:’) to indicate that it takes a required argument."
# "If an option character is followed by two colons (‘::’), its argument is optional; this is a GNU extension."
# "If the first character of options is a colon (‘:’), then getopt returns ‘:’ instead of ‘?’ to indicate a missing option argument."
# To pass args not that should not be processed by getopt, pass a '--' and everything after it will be left to $* after getopts.
while getopts ":c:i:m:h?" opt; do
	case "$opt" in
		c) cmd="$OPTARG";;
		i) opt1="$OPTARG";;
		m) opt2="$OPTARG";;
		:) echo "Option -$OPTARG requires an argument." >&2; exit 1;;
		h|?|*) echo -e "$usage"; exit 0;;
	esac
done
shift $((OPTIND - 1))

# Validate supplied option arguments.
if [ "$cmd" = "up" ]; then
	echo "> cmd is up"
elif [ "$cmd" = "down" ]; then
	echo "> cmd is down"
else
	echo "Unknow command \"$cmd\"." 1>&2
	exit 2
fi


echo "$cmd"
echo "$opt1"
echo "$opt2"
echo "remaining args:" "$@"
