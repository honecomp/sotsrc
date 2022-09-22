#!/bin/sh


usage(){
	echo "usage: $0 fich [fich ..]" 1>&2
	exit 1
}

badgrade(){
	echo "bad grade"
	exit 1
}


baddni(){
        echo "bad dni"
        exit 1
}
if [ $# -lt 1 ]; then
	usage
fi

if [ -e NOTAS ]; then
	echo "error: NOTAS already exists" 1>&2
	exit 1
fi

cat $@| awk '($2<0.0 || $2>10.0)|| ($2 !~ /\./ ) {exit (1);}' || badgrade

cat $@|awk '$1 !~ /^[0-9]+[a-zA-Z]$/ {exit(1);}'||baddni

names=$(cat $@|awk '{print $1}' | sort -u)

for i in $names; do
	nota=''
	nfiles=$(grep \^$i'[	 ]' $@ /dev/null| \
		awk -F: '{print $1}'|sort -u|wc -l)
	if ! [ $nfiles = $# ]; then
		nota=NP
	fi
	if ! [ "$nota" = NP ]; then
		nota=$(grep $i $@| \
			awk '{avg+=$2}END{avg/=NR; printf("%2.1f", avg);}')
	fi
	echo "$i	$nota" >> NOTAS
done


