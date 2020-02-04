//
// Created by maxence on 04/02/2020.
//

#include <stdio.h>
#include "configIps.h"
#include "../util/utils.h"

const int NUMBER_OF_PC = 2;

char *ADRESSES_EMETTEUR[] = {"127.0.0.1", "127.0.0.11"};
char *ADRESSES_RECEPTEUR[] = {"127.0.0.1", "127.0.0.11"};
int PORTS_RECEPTION[] = {1920, 1920};
int PORTS_EMISSION[] = {1920, 1920};


int getConfig(int numberConfig, struct address *addr) {

	if (numberConfig > NUMBER_OF_PC - 1) {
		perror("Cette configuration n'existe pas.");
		return -1;
	}

	addr->ADRESSE_EMETTEUR = ADRESSES_EMETTEUR[numberConfig];
	addr->ADRESSE_RECEPTEUR = ADRESSES_RECEPTEUR[numberConfig];
	addr->PORT_EMISSION = PORTS_EMISSION[numberConfig];
	addr->PORT_RECEPTION = PORTS_RECEPTION[numberConfig];

	return 1;
}