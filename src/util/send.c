#include <unistd.h>
#include "send.h"

int send_data(int prise, char *buffer, size_t size) {
    if (write(prise, buffer, size) == size)
        return 0;
    else
        return -1;
}

