#!/bin/sh

usage(){
	echo "usage: $0 dir" 1>&2
	exit 1
}
if [ $# -ne 1 ] || ! [ -d "$1" ]; then
        usage
fi

dirname=$1
cd $dirname
if ls *.txt > /dev/null 2>&1; then
	echo "$0: no *.txt files"
	exit 1
fi

ls *.txt|sed -E 's/((.).*\.txt$)/rm -f \2.output/'| \
	awk '{print $1, $2, tolower($3)}'|sort -u|sh
ls *.txt|sort| \
	sed -E 's/((.).*\.txt$)/cat \1>> \2.output/'| \
	awk '{print $1, $2, tolower($3)}'|sh

