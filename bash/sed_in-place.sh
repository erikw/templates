#!/usr/bin/env sh

# To be compatiable with both GNU sed and the old BSD sed that macOS uses, need to set and inplace backup extension and then remove the file.
# $(sed -i -e '...' file) works with GNU sed and modern BSD. However on macOS a backup file "file-e" will be created
# Reference: https://unix.stackexchange.com/a/131940/19909

sed -i.bak -e 'expr...' file && rm file.bak
