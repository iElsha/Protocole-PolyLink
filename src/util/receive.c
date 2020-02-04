#include <unistd.h>
#include "receive.h"

int receive_data(int prise, char *buffer, size_t taille) {
	if (read(prise, buffer, taille) >= 0)
		return 0;
	else
		return -1;
}

