#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char str[] = "Hola amigo";
	char dest[20] = "HAL dice ";

	printf("La string str %s sizeof %d len %d\n",
	       str, (int)sizeof str, (int)strlen(str));
	strcat(dest, str);
	printf("La string dest %s sizeof %d len %d\n",
	       dest, (int)sizeof dest, (int)strlen(dest));
	snprintf(dest, 20, "BORRADO");	/* escrbira */
	printf("La string dest  es %s sizeof %d len %d\n",
	       dest, (int)sizeof dest, (int)strlen(dest));

	exit(EXIT_SUCCESS);
}
