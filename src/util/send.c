#include <unistd.h>
#include "send.h"

int send_data(int prise, char *buffer, size_t taille) {
	if (write(prise, buffer, taille) == taille)
		return 0;
	else
		return -1;
}

