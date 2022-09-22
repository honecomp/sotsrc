#!/bin/sh


usage(){
	echo "usage: $0 [-d] dir..." 1>&2
	exit 1
}

exitisnotdir(){
	if ! [ -d "$1" ]; then
		echo "error dir $dir not found" 1>&2
		exit 1
	fi
}

ONLYPRINT=false
if [ $# -ge 1 ] && [ "$1" = '-d' ]; then
	shift
	ONLYPRINT=true
fi

if [ $# = 0 ]; then
	usage
fi

cd /

TOTALPIDS=''
for dir in "$@"; do
	dir=$(realpath $dir)
	exitisnotdir $dir
	if [ "$dir" = '/' ]; then
		echo "error $0: / is not valid" 1>&2
		exit 1
	fi
	listpids=$(lsof +D $dir 2>/dev/null | awk '$4 ~ /^cwd$/ {print $2}' )
	TOTALPIDS="$TOTALPIDS $listpids"
done

if echo $TOTALPIDS | grep -v '[0-9]' >/dev/null 2>&1; then
	exit 0
fi


KILLCMD='KILL -KILL'
if [ "$ONLYPRINT" = 'true' ]; then
	echo $KILLCMD $TOTALPIDS
else
	$KILLCMD $TOTALPIDS
fi

exit 0

