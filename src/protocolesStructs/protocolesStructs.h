//
// Created by maxence on 04/02/2020.
//
#include "../util/list/linked_list.h"

#ifndef PROTOCOLE_POLYLINK_PROTOCOLESSTRUCTS_H
#define PROTOCOLE_POLYLINK_PROTOCOLESSTRUCTS_H

/**
 * structure layer 5
 */
struct Message {
	char *data;
};

/**
 * structure layer 4
 */
struct HeaderMessage {
	int source;
	int idBroadcast;
	int checksum;
};

/**
 * structure layer 3
 * flag ==>
 * 			1 : message
 * 			2 : ACK
 * 			3 : Error
 */
struct Flag {
	int flag;
};


/**
 * structure layer 2
 */
struct Container {
	int nbMessage;
	LIST dests; // List of the dests
	LIST sizes; // size of messages
};


#endif //PROTOCOLE_POLYLINK_PROTOCOLESSTRUCTS_H
