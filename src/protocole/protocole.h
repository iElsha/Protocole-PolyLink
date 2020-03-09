#include "../protocolesStructs/protocolesStructs.h"

#ifndef PROTOCOLE_POLYLINK_PROTOCOLE_H
#define PROTOCOLE_POLYLINK_PROTOCOLE_H

char *PolyLink(char *, int);

void packet_message_ack(struct Container *);

int packet_message_error(struct Container *);

void packet_message_read_broadcast(struct Container *);

void packet_message_read_user(struct Container *);

void action_user(int, struct Container *);

#endif //PROTOCOLE_POLYLINK_PROTOCOLE_H