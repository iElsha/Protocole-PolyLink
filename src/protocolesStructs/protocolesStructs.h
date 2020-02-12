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
	struct Message *message;
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
	struct HeaderMessage *headerMessage;
};


/**
 * structure layer 2
 */
struct Container {
	int nbMessage;
	struct list *dests; // List of the dests
	struct list *sizes; // size of messages
	struct list *flags; //Liste des flags
};

int F_FLAG_MESSAGE();

int F_FLAG_ACK();

int F_FLAG_ERR();

struct Container *parseContainer(char *);

char *stringifyContainer(struct Container *);

struct Container *createContainer();

void addMessage(struct Container *, int, int, char *);

void addMessageB(struct Container *, int, int, char *, int);

void deleteMessage(int pos, struct Container *packet);

void createAck(struct Container *, int);

void createError(struct Container *, int);

struct Message *createMessage(char *);

struct HeaderMessage *createHeaderMessage(int source, int checksum, int idBroadcast, struct Message *message);

struct HeaderMessage *createHeaderMessage_new(int source, int idBroadcast, struct Message *message);

struct Flag *createFlag1(int);

struct Flag *createFlag(int, struct HeaderMessage *);

void deleteContainer(struct Container *packet);

void deleteFlag(struct Flag *flag);

void deleteHeaderMessage(struct HeaderMessage *headermessage);

void deleteMessage_layout(struct Message *message);

#endif //PROTOCOLE_POLYLINK_PROTOCOLESSTRUCTS_H
