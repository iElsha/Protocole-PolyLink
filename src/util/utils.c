#include "utils.h"

int getLength(void *tab) {
	return (int) sizeof(tab) / sizeof(tab[0]);
}
