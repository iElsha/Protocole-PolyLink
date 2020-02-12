#include <unistd.h>
#include "receive.h"

int receive_data(int prise, char *buffer, size_t size) {
	if (read(prise, buffer, size) >= 0)
		return 0;
	else
		return -1;
}

