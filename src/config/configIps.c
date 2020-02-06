#include <stdio.h>
#include <stdlib.h>
#include "configIps.h"
#include "../util/utils.h"

const int NUMBER_OF_PC = 3;

const char *ADRESSES_EMETTEUR[] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
const char *ADRESSES_RECEPTEUR[] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
const int PORTS_RECEPTION[] = {8000, 8001};
const int PORTS_EMISSION[] = {8001, 8000};
const int IDS_COMPUTER[] = {1, 2};

const int SIZE_NBMESSAGE = 2;
const int SIZE_DEST = 2;
const int SIZE_SIZE = 2;
const int SIZE_FLAG = 1;
const int SIZE_SOURCE = 2;
const int SIZE_IDBROADCAST = 1;
const int SIZE_CHECKSUM = 3;

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

struct CONFIG_PACKET* getConfigPacket() {
	struct CONFIG_PACKET * configPacket = (struct CONFIG_PACKET*) malloc(sizeof(struct CONFIG_PACKET));
	configPacket->SIZE_CHECKSUM= SIZE_CHECKSUM;
	configPacket->SIZE_DEST= SIZE_DEST;
	configPacket->SIZE_FLAG = SIZE_FLAG;
	configPacket->SIZE_IDBROADCAST = SIZE_IDBROADCAST;
	configPacket->SIZE_NBMESSAGE = SIZE_NBMESSAGE;
	configPacket->SIZE_SIZE = SIZE_SIZE;
	configPacket->SIZE_SOURCE = SIZE_SOURCE;
	return configPacket;
}