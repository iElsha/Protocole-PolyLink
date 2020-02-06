//
// Created by erwan on 05/02/2020.
//

#ifndef PROTOCOLE_POLYLINK_PROTOCOLE_H
#define PROTOCOLE_POLYLINK_PROTOCOLE_H

#endif //PROTOCOLE_POLYLINK_PROTOCOLE_H
#include "../protocolesStructs/protocolesStructs.h"

char * PolyLink (char *, int);
void packet_message_ack(struct Container* );
int packet_message_error(struct Container* );
void packet_message_read_broadcast(struct Container*);
void packet_message_read_user(struct Container* );
void action_user(int, struct Container*);