#!/bin/bash

function rec_search {
	SUBDIRS=$(ls -l $1 | grep -E '^d'| tr -s " " | cut -d " " -f9)
	FILES=$(ls -l $1 | grep -E '^-' | tr -s " " | cut -d " " -f9)
	if [ "$FILES" != "" ]; then
		for f in $FILES; do
			echo $(stat -c %s $f):$f 
		done
	fi
	if [ "$SUBDIRS" != "" ]; then
		for d in ${SUBDIRS}; do
			cd $d
			rec_search .
		done
	fi
	cd ..
}

if [ $# -ne 1 ]; then
	echo Usage: $0 dir >&2
	exit 1
else
	RES=$(rec_search $1 | tr " " "\n" | sort -n | tail -n 1 | tr ":" "\n")
	SIZE=$(echo $RES | cut -d " " -f1)
	NAME=$(echo $RES | cut -d " " -f2)
	echo $NAME: ${SIZE} oct.
	exit 0
fi
