#include <stdlib.h>
#include <stdio.h>

struct Coordenada {
	int x;
	int y;
};

struct Cita {
	struct Coordenada lugar;
	int dia;
	int hora;
};

typedef struct Cita Cita;

int
main(int argc, char *argv[])
{
	struct Coordenada c1;
	Cita cita;
	Cita *pc;

	c1.x = 33;
	c1.y = 44;
	pc = &cita;
	pc->lugar = c1;
	pc->dia = 12;
	pc->hora = 5;

	printf("La cita es en %d,%d el dia %d a las %d\n",
	       cita.lugar.x, cita.lugar.y, cita.dia, cita.hora);

	printf("sizeof Cita: %ld sizeof Coordenada %ld, sizeof *pc: %ld\n",
	       sizeof(Cita), sizeof c1, sizeof pc);

	exit(EXIT_SUCCESS);
}
