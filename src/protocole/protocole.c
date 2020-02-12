#include "protocole.h"
#include "../protocolesStructs/protocolesStructs.h"
#include "../config/configIps.h"
#include "../util/utils.h"
#include "../util/list/linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Flag *lastMessage;
int lastDesMessage;


struct CONFIG_PACKET *configPacket;

int IDUSER;
int BROADCAST;

struct list *list_user;
struct list *list_idbroadcast;


char *PolyLink(char *stringPacket, int pc) {

    /*   INTI  */
    IDUSER = pc;
    BROADCAST = getBROADCAST();
    list_user = getIDS_COMPUTER();
    list_idbroadcast = list_create();
    for (int i = 0; i < list_lenght(list_user); i++) {
        int *j = (int *) malloc(sizeof(int));
        *j = 0;
        list_insert_header(j, list_idbroadcast);
    }

    configPacket = getConfigPacket();
    struct Container *packet;
    if (stringPacket == NULL || strlen(stringPacket) <= 1) {
        packet = createContainer();
    } else {
        packet = parseContainer(stringPacket);
    }
    /*****/


    printf("\n========= Packet =========\n");
    packet_message_ack(packet);
    int error = packet_message_error(packet);
    packet_message_read_broadcast(packet);
    packet_message_read_user(packet);

    action_user(error, packet);

    printf("\n=========================\n");
    return stringifyContainer(packet);
}

void packet_message_ack(struct Container *packet) {

    int find = 0;
    int i = 0;
    while (!find && lastMessage != NULL && i < packet->nbMessage) {
        if (list_getElem(i, packet->dests) == IDUSER || list_getElem(i, packet->dests) == BROADCAST) {
            struct Flag *f = list_getElem(i, packet->flags);
            if (f->flag == F_FLAG_ACK() || (f->flag == F_FLAG_MESSAGE() && f->headerMessage->source == IDUSER)) {
                printf("\nYour message has been transmitted\n");
                deleteMessage(i, packet);
                find = 1;
            }
        }
        i++;
    }
}

int packet_message_error(struct Container *packet) {
    int find = 0;
    int i = 0;
    while (!find && lastMessage != NULL && i < packet->nbMessage) {
        if (list_getElem(i, packet->dests) == IDUSER) {
            struct Flag *f = list_getElem(i, packet->flags);
            if (f->flag == F_FLAG_ERR()) {
                printf("\nYour message hasn't been transmitted\n");
                deleteMessage(i, packet);
                find = 1;
            }
        }
        i++;
    }
    return find;
}

void packet_message_read_broadcast(struct Container *packet) {
    int find = 0;
    int i = 0;

    // recherche est message de braodcast
    while (i < packet->nbMessage) {
        if (list_getElem(i, packet->dests) == BROADCAST) {
            struct Flag *f = list_getElem(i, packet->flags);
            // check si il y a une error
            if (calcCheckSum(f->headerMessage->message->data, configPacket->SIZE_CHECKSUM) !=
                f->headerMessage->checksum) {
                // si oui creation de l'error et suppresion du broadcast
                createError(packet, f->headerMessage->source);
                deleteMessage(i, packet);
                i--;
            } else {
                // test si deja broadcast
                int sourcepos = list_find(f->headerMessage->source, list_user);
                int *lastid = list_getElem(sourcepos, list_idbroadcast);
                if (*lastid != f->headerMessage->idBroadcast) {
                    *lastid = f->headerMessage->idBroadcast;
                    if (!find) {
                        printf("\n--- Broadcast message ---\n\n");
                        find = 1;
                    }
                    printf("%d --> %s\n", f->headerMessage->source, f->headerMessage->message->data);
                }
            }
        }
        i++;
    }
}

void packet_message_read_user(struct Container *packet) {
    int find = 0;
    int i = 0;
    while (i < packet->nbMessage) {
        if (list_getElem(i, packet->dests) == IDUSER) {
            struct Flag *f = list_getElem(i, packet->flags);
            if (calcCheckSum(f->headerMessage->message->data, configPacket->SIZE_CHECKSUM) !=
                f->headerMessage->checksum) {
                deleteMessage(i, packet);
                createError(packet, f->headerMessage->source);
                i--;
            } else {
                if (!find) {
                    printf("\n--- Your message ---\n\n");
                    find = 1;
                }
                printf("%d --> %s\n", f->headerMessage->source, f->headerMessage->message->data);
                createAck(packet, f->headerMessage->source);
                deleteMessage(i, packet);
                i--;
            }
        }
        i++;
    }
}

void action_user(int error, struct Container *packet) {
    char action[10];
    printf("\n--- User Console ---\n");
    if (error) {
        printf("\nYour last message failed:\n\n");
        printf("%d --> %s\n", IDUSER, lastMessage->headerMessage->message->data);
        printf("Do you want to send it back? [y/n] : ");
    } else {
        printf("\nDo you want to send a message? [y/n] : ");
    }
    do {
        memset(action, '\0', sizeof(action));
        fgets(action, sizeof(action), stdin);
        strtok(action, "\n");

        if (action[0] == 'y') { // write a message
            if (error) {
                addMessageB(packet, IDUSER, lastDesMessage, lastMessage->headerMessage->message->data,
                            lastMessage->headerMessage->idBroadcast);
            } else {
                printf("\nList of user:\n|");
                for (int i = 0; i < list_lenght(list_user); i++) {
                    int j = list_getElem(i, list_user);
                    if (j != IDUSER)
                        printf(" %d |", j);
                }
                printf("\nBroadcast : %d\nSelect a destination: ", BROADCAST);
                char iddest[10];
                memset(iddest, '\0', sizeof(iddest));
                fgets(iddest, sizeof(iddest), stdin);
                strtok(iddest, "\n");

                printf("Message :\n%d --> ", IDUSER);

                char msg[200];
                memset(msg, '\0', sizeof(msg));
                fgets(msg, sizeof(msg), stdin);
                strtok(msg, "\n");

                int dest = StringToInt(iddest);

                if (BROADCAST == dest) {
                    int *idbraod = list_getElem(list_find(IDUSER, list_user), list_idbroadcast);
                    (*idbraod)++;
                    addMessageB(packet, IDUSER, BROADCAST, msg, *idbraod);
                } else {
                    addMessage(packet, IDUSER, dest, msg);
                }
                lastMessage = list_getElem_footer(packet->flags);
                lastDesMessage = list_getElem_footer(packet->dests);

            }
            printf("\nMessage sent !!!\n");
        } else if (action[0] == 'h') {
            printf("Press y to write a message or resend the last message\n");
            printf("Press n if you have nothing to say\n");
        }
    } while (action[0] != 'y' && action[0] != 'n');

}