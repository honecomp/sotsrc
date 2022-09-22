#!/bin/sh


usage(){
	echo "usage: $0 cmd pid [pid ..]" 1>&2
	exit 1
}

if [ $# -le 1 ] || ! which "$1" >/dev/null; then
	usage
fi

cmd="$1"
shift
if ! echo $*|egrep '[0-9 ]'>/dev/null 2>&1; then
	usage
fi

regexp=$(echo $*| sed -E -e 's/[ 	]+/|/g' -e  's/^/\^/' -e 's/$/\$/')

finish=some
for i in $(seq 1 20); do
	if ! ps aux| awk '{print $2}' |egrep "$regexp">/dev/null 2>&1; then
		finish=noneexec
		break
	fi
	sleep 1
done

if [ $finish = some ]; then
	kill -KILL $* 2> /dev/null
	exit 0
fi

$cmd


