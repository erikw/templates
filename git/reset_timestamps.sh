#!/usr/bin/env sh
# Ref: https://stackoverflow.com/a/454750/265508

git filter-branch --env-filter '
	export GIT_AUTHOR_DATE="$(date)"
	export GIT_COMMITTER_DATE="$(date)"
	'
