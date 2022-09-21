#!/bin/sh

FNAME=`mktemp mytemp.XXXXXX.yyy`
rm $FNAME 2>/dev/null
cd /tmp
URL=https://labs.etsit.urjc.es/parte/index.php

if ! curl --connect-timeout 3 $URL > $FNAME 2>/dev/null; then
		echo "cannot reach $URL" 1>&2
		rm $FNAME
		exit 1
fi

# File in one line, try to break by machines, match names
# fragile, but we have to be careful to select the right
# machines or the firewall will eat us.
names=`cat $FNAME |tr '\n' ' '\
        |sed -E 's/arriba/arriba\n/g'|sed 's/quina.*SSH//g'\
	|grep arriba\
        |grep -E 'f-l[0-9]+-pc[0-9]+'\
	|sed -E 's/.*(f-l[0-9]+-pc[0-9]+).*/\1/g'|sort -u`
echo $names
rm $FNAME
