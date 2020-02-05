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
	struct Message* message;
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
	struct HeaderMessage* headerMessage;
};


/**
 * structure layer 2
 */
struct Container {
	int nbMessage;
    struct list* dests; // List of the dests
    struct list* sizes; // size of messages
    struct list* flags; //Liste des flags
};

struct Container* parseContainer(char *);
char* stringifyContainer (struct Container*);
struct Container* createContainer();
void addMessage(struct Container*, int, int, char*);
void addMessageB(struct Container* , int , int , char* , int);
void createAck(struct Container*, int);
void createError(struct Container*, int);
struct Message* createMessage(char *);
struct HeaderMessage* createHeaderMessage(int source,int checksum, int idBroadcast, struct Message* message);
struct HeaderMessage* createHeaderMessage_new(int source, int idBroadcast, struct Message* message);
struct Flag* createFlag1(int);
struct Flag* createFlag(int, struct HeaderMessage* );
#endif //PROTOCOLE_POLYLINK_PROTOCOLESSTRUCTS_H
