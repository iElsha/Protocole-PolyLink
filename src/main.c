#include <stdio.h>
#include <string.h>
#include "config/configIps.h"
#include <stdlib.h>

int main(int argc, char **argv) {
	char *end;
	char buffer[200];

	if (argc < 2) {
		fprintf(stderr, "You didn't provide enough args. Do not forget the configuration IP ID.\n");
		return -1;
	}

	int configId = (int) strtol(argv[1], &end, 10); // get the configId ID
	struct address addr; // create an address struct
	int configError = getConfig(configId, &addr); // get the configId correspond to the ID

	if (configError == -1) {
		fprintf(stderr, "This configuration doesn't exist, your config ID is out of range.\n");
		return -1;
	}

	while (1) {
		char action;
		while (1) {
			printf("> ");
			action = getchar();

			if (action == 'w') { // write a message

				break;
			} else if (action == 'n') { // Nothing to say
				// TODO
			} else if (action == 'c') {
				printf("close the client \n");
				return 1;
			} else if (action == 'h') {
				printf("Press w to write a message\n");
				printf("Press n if you have nothing to say\n");
				printf("Press q to quit\n");
			}

			getchar();
		}

		memset(buffer, '\0', sizeof(buffer));

//        sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "nouveauBlabla");
//
//        envoie(priseEmission, buffer, strlen(buffer));

	}

	return 1;
}


