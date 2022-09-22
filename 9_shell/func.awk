#!/usr/bin/awk -f

function repname(name, repetitions,    i) {
	for(i = 0; i < repetitions; i++) {
		printf("%d: %s\n", i, name);
	} 
}

{
	repname($1, 3)
}