#include <stdio.h>
#include "configIps.h"
#include "../util/utils.h"

const int NUMBER_OF_PC = 3;

char *ADRESSES_EMETTEUR[] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
char *ADRESSES_RECEPTEUR[] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
int PORTS_RECEPTION[] = {8000, 8001, 8002};
int PORTS_EMISSION[] = {8001, 8002, 8000};
int IDS_COMPUTER[] = {1, 2, 3};


int getConfig(int numberConfig, struct address *addr) {
	numberConfig = numberConfig - 1;

	if (numberConfig > NUMBER_OF_PC - 1) return -1;

	addr->ADRESSE_EMETTEUR = ADRESSES_EMETTEUR[numberConfig];
	addr->ADRESSE_RECEPTEUR = ADRESSES_RECEPTEUR[numberConfig];
	addr->PORT_EMISSION = PORTS_EMISSION[numberConfig];
	addr->PORT_RECEPTION = PORTS_RECEPTION[numberConfig];
	addr->ID_COMPUTER = IDS_COMPUTER[numberConfig];

	printf("ID: %d \tReceiver: %s:%d \tSender: %s:%d\n",
	       addr->ID_COMPUTER,
	       addr->ADRESSE_EMETTEUR,
	       addr->PORT_EMISSION,
	       addr->ADRESSE_RECEPTEUR,
	       addr->PORT_RECEPTION);

	return 1;
}