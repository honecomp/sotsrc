#!/bin/sh

usage(){
	echo "usage: $0 [-r]" 1>&2
	exit 1
}


DEPTH='-maxdepth 1'
if [ $# = 1 ] && [ $1 = '-r' ]; then
	shift
	DEPTH=''
fi

if [ $# != 0 ]; then
	usage
fi
bigfile=$(find . $DEPTH -type f -exec du -b \{\} \;|sort -nr|awk '{print $2}'|sed 1q)

if ! [ -f "$bigfile" ]; then
	echo no files to print command 1>&2
	exit 1
fi
bigfile=$(realpath "$bigfile")

echo mv "$bigfile" "$bigfile.old"

exit 0
