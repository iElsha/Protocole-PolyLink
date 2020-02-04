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
int IDS_COMPUTER[] = {1, 2};


int getConfig(int numberConfig, struct address *addr) {

	if (numberConfig > NUMBER_OF_PC - 1) return -1;

	numberConfig = numberConfig - 1;
	addr->ADRESSE_EMETTEUR = ADRESSES_EMETTEUR[numberConfig];
	addr->ADRESSE_RECEPTEUR = ADRESSES_RECEPTEUR[numberConfig];
	addr->PORT_EMISSION = PORTS_EMISSION[numberConfig];
	addr->PORT_RECEPTION = PORTS_RECEPTION[numberConfig];
	addr->ID_COMPUTER = IDS_COMPUTER[numberConfig];

	printf("ID: %d \tIP: %s:%d \tDest: %s:%d\n",
	       addr->ID_COMPUTER,
	       addr->ADRESSE_EMETTEUR,
	       addr->PORT_EMISSION,
	       addr->ADRESSE_RECEPTEUR,
	       addr->PORT_RECEPTION);

	return 1;
}