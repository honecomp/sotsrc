#!/bin/sh

usage(){
	echo "usage: $0 dir" 1>&2
	exit 1
}


if [ $# -ne 1 ] || ! [ -d "$1" ]; then
	usage
fi


dirname=$1/$(date +%d_%b_%Y)

if [ -d "$dirname" ]; then
	echo "error: dir $dirname already exists" 1>&2
	exit 1
fi
mkdir $dirname

if ! [ -d "$dirname" ]; then
        echo "error: dir $dirname could not be created" 1>&2
        exit 1
fi

isimage(){
	file --mime-type "$1"|sed 's/.*://g'|awk '{print $1}'|\
		egrep '^image/'> /dev/null 2>&1
}

for i in "$1/"*; do
       if isimage "$i"; then
               mv "$i" "$dirname/$i"
       fi
done

nfile=$(ls $dirname/|wc -l)
orignames=$(ls $dirname/)

for i in $(seq -w 1 $nfile); do
	fichname=$(echo $orignames|tr ' ' '\n'| sed "$i"q|tail -1)
	ext=$(echo "$fichname"|sed -E 's/.*(\.[^.]+)$/\1/')
	mv "$dirname/$fichname" "$dirname/$i$ext"
done

