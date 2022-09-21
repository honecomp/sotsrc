#!/bin/sh

if test $# -gt 0 && test $1 = '-d'
then
	shift
	dflag=yes
fi

test $# -eq 0 && exit 0

dirs=''
for i in "$@"
do
	if ! test -d $i
	then
		echo error: dir $i not found >&2
		exit 1
	fi
	dir=$(realpath "$i")
	if [ $dir = '/' ]
	then
		echo error: / in params >&2
		exit 2
	fi
	dirs="$dir $dirs"
done

cd /
rexp=$(echo $dirs |sed -E 's/([^ a-zA-Z0-9`'\''])/\\\1/g'| sed 's/ /|/g')
p=$(ls -l /proc/[0-9]*/cwd 2> /dev/null | \
		awk '{print $9 ":" $11}' | \
		egrep -- ":($rexp)" | \
		sed -E -e  's/^\/proc\///' -e 's/\/.*//')

if echo $p | egrep -q '[0-9]'
then
	if test $dflag
	then
		echo kill -9 $p
	else
		kill -9 $p
	fi
fi

