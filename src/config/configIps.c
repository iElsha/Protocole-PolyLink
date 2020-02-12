#include <stdio.h>
#include <stdlib.h>
#include "configIps.h"
#include "../util/utils.h"
#include "../util/list/linked_list.h"

const int NUMBER_OF_PC = 3;

const char *ADRESSES_EMETTEUR[] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
const char *ADRESSES_RECEPTEUR[] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
const int IDS_COMPUTER[] = {1, 2, 3};
int BROADCAST = 99;
const int SIZE_NBMESSAGE = 2;
const int SIZE_DEST = 2;
const int SIZE_SIZE = 2;
const int SIZE_FLAG = 1;
const int SIZE_SOURCE = 2;
const int SIZE_IDBROADCAST = 1;
const int SIZE_CHECKSUM = 3;
const int BASE_ADDRESS = 9001;

int getConfig(int numberConfig, struct address *addr) {
	numberConfig = numberConfig - 1;

	if (numberConfig > NUMBER_OF_PC - 1) return -1;

	addr->ADRESSE_EMETTEUR = ADRESSES_EMETTEUR[numberConfig];
	addr->ADRESSE_RECEPTEUR = ADRESSES_RECEPTEUR[numberConfig];
	addr->PORT_EMISSION = BASE_ADDRESS + ((numberConfig + 1) % NUMBER_OF_PC);
	addr->PORT_RECEPTION = BASE_ADDRESS + numberConfig;
	addr->ID_COMPUTER = IDS_COMPUTER[numberConfig];
	printf("Network Configuration:\n");
	printf("ID: %d \tReceiver: %s:%d \tSender: %s:%d\n\n",
	       addr->ID_COMPUTER,
	       addr->ADRESSE_RECEPTEUR,
	       addr->PORT_RECEPTION,
	       addr->ADRESSE_EMETTEUR,
	       addr->PORT_EMISSION);

	return 1;
}

struct CONFIG_PACKET *getConfigPacket() {
	struct CONFIG_PACKET *configPacket = (struct CONFIG_PACKET *) malloc(sizeof(struct CONFIG_PACKET));
	configPacket->SIZE_CHECKSUM = SIZE_CHECKSUM;
	configPacket->SIZE_DEST = SIZE_DEST;
	configPacket->SIZE_FLAG = SIZE_FLAG;
	configPacket->SIZE_IDBROADCAST = SIZE_IDBROADCAST;
	configPacket->SIZE_NBMESSAGE = SIZE_NBMESSAGE;
	configPacket->SIZE_SIZE = SIZE_SIZE;
	configPacket->SIZE_SOURCE = SIZE_SOURCE;
	return configPacket;
}

struct list *getIDS_COMPUTER() {
	struct list *l = list_create();
	for (int i = 0; i < NUMBER_OF_PC; i++) {
		list_insert_footer(IDS_COMPUTER[i], l);
	}
	return l;
}

int getBROADCAST() {
	return BROADCAST;
}