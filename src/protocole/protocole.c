#include "protocole.h"
#include "../protocolesStructs/protocolesStructs.h"
#include "../config/configIps.h"
#include "../util/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../util/colors.h"
#include "../util/polylink_socket.h"

struct Flag *lastMessage;
static int lastDesMessage;

struct CONFIG_PACKET *configPacket;

static int ID_USER;
static int BROADCAST;

struct list *listUser;
struct list *listIdBroadcast;


char *PolyLink(char *stringPacket, int pc) {

	/*   INTI  */
	ID_USER = pc;
	BROADCAST = getBROADCAST();
	listUser = getIDS_COMPUTER();
	listIdBroadcast = list_create();
	for (int i = 0; i < list_lenght(listUser); i++) {
		int *j = (int *) malloc(sizeof(int));
		*j = 0;
		list_insert_header(j, listIdBroadcast);
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
	printf(ANSI_COLOR_YELLOW "Waiting..." ANSI_COLOR_RESET);
	return stringifyContainer(packet);
}

void packet_message_ack(struct Container *packet) {

	int find = 0;
	int i = 0;
	while (!find && lastMessage != NULL && i < packet->nbMessage) {
		if ((int) list_getElem(i, packet->dests) == ID_USER || (int) list_getElem(i, packet->dests) == BROADCAST) {
			struct Flag *f = list_getElem(i, packet->flags);
			if (f->flag == F_FLAG_ACK() || (f->flag == F_FLAG_MESSAGE() && f->headerMessage->source == ID_USER)) {
				printf(ANSI_COLOR_GREEN "\nYour message has been transmitted\n" ANSI_COLOR_RESET);
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
		if ((int) list_getElem(i, packet->dests) == ID_USER) {
			struct Flag *f = list_getElem(i, packet->flags);
			if (f->flag == F_FLAG_ERR()) {
				printf(ANSI_COLOR_RED "\nYour message hasn't been transmitted\n" ANSI_COLOR_RESET);
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
		if ((int) list_getElem(i, packet->dests) == BROADCAST) {
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
                #pragma clang diagnostic push
                #pragma clang diagnostic ignored "-Wint-conversion"
				int sourcepos = list_find(f->headerMessage->source, listUser);
                #pragma clang diagnostic pop
				int *lastid = list_getElem(sourcepos, listIdBroadcast);
				if (*lastid != f->headerMessage->idBroadcast) {
					*lastid = f->headerMessage->idBroadcast;
					if (!find) {
						printf(ANSI_COLOR_MAGENTA"\n--- Broadcast message ---\n" ANSI_COLOR_RESET);
						find = 1;
					}
					printf(ANSI_COLOR_MAGENTA "%d --> %s\n" ANSI_COLOR_RESET, f->headerMessage->source,
					       f->headerMessage->message->data);
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
		if ((int) list_getElem(i, packet->dests) == ID_USER) {
			struct Flag *f = list_getElem(i, packet->flags);
			if (calcCheckSum(f->headerMessage->message->data, configPacket->SIZE_CHECKSUM) !=
			    f->headerMessage->checksum) {
				deleteMessage(i, packet);
				createError(packet, f->headerMessage->source);
				i--;
			} else {
				if (!find) {
					printf(ANSI_COLOR_BLUE"\n--- Your message ---\n" ANSI_COLOR_RESET);
					find = 1;
				}
				printf(ANSI_COLOR_BLUE "%d --> %s\n" ANSI_COLOR_RESET, f->headerMessage->source,
				       f->headerMessage->message->data);
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
	printf("\n--- User Console ---");
	if (error) {
		fprintf(stderr, "\nYour last message failed:\n");
		printf("> %d --> %s\n", ID_USER, lastMessage->headerMessage->message->data);
		printf("Do you want to send it back? [y/N/q] : ");
	} else {
		printf("\nDo you want to send a message? [y/N/q] : ");
	}
	do {
		memset(action, '\0', sizeof(action));
		fgets(action, sizeof(action), stdin);
		strtok(action, "\n");

		if (action[0] == 'y' || action[0] == 'Y') { // write a message
			if (error) {
				addMessageB(packet, ID_USER, lastDesMessage, lastMessage->headerMessage->message->data,
				            lastMessage->headerMessage->idBroadcast);
			} else {
				printf("\nList of user:\n|");
				for (int i = 0; i < list_lenght(listUser); i++) {
					int j = (int) list_getElem(i, listUser);
					if (j != ID_USER)
						printf(" %d |", j);
				}
				printf("\nBroadcast : %d\nSelect a destination: ", BROADCAST);
				char iddest[10];
				memset(iddest, '\0', sizeof(iddest));
				fgets(iddest, sizeof(iddest), stdin);
				strtok(iddest, "\n");

				printf("Message :\n%d --> ", ID_USER);

				char msg[200];
				memset(msg, '\0', sizeof(msg));
				fgets(msg, sizeof(msg), stdin);
				strtok(msg, "\n");

				int dest = StringToInt(iddest);

				if (BROADCAST == dest) {
                    #pragma clang diagnostic push
                    #pragma clang diagnostic ignored "-Wint-conversion"
					int *idBroadcast = list_getElem(list_find(ID_USER, listUser), listIdBroadcast);
#pragma clang diagnostic pop
					(*idBroadcast)++;
					addMessageB(packet, ID_USER, BROADCAST, msg, *idBroadcast);
				} else {
					addMessage(packet, ID_USER, dest, msg);
				}
				lastMessage = list_getElem_footer(packet->flags);
				lastDesMessage = (int) list_getElem_footer(packet->dests);

			}
			printf(ANSI_COLOR_GREEN "\nMessage sent!!!\n" ANSI_COLOR_RESET);
		} else if (action[0] == 'h' || action[0] == 'H') {
			printf("Press y to write a message or resend the last message\n");
			printf("Press n if you have nothing to say\n");
			printf("Press q if you want to quit\n");
		} else if (action[0] == 'q') {
			printf("Closing Sockets ..\n");
			close_sockets();
		}
	} while (action[0] != 'y' && action[0] != 'n' && action[0] != '\n');

}