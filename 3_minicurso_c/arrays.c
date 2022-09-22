#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	int i;
	char *ptr;
	char arr[10];
	char arr2[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

	for (i = 0; i < 10; i++)
		arr[i] = 'a' + i;

	for (i = 0; i < 10; i++) {
		printf("%c ", arr[i]);
	}
	printf("\n");

	ptr = arr;

	for (i = 0; i < 10; i++, ptr++)
		printf("%c ", *ptr);
	printf("\n");

	for (i = 0; i < 10; i++)
		printf("%c ", arr2[i]);
	printf("\n");
	exit(EXIT_SUCCESS);
}
