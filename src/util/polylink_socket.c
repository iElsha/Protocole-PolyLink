#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "colors.h"

int receiver, sender;

void throwErrorMessage(char *msg) {
	perror(msg);
}

int createSocketReceiver(int TDP_port_S) {
	int sock, new_sock;
	struct sockaddr_in sa_C;
	unsigned int taille_sa_C;

	errno = 0; //reset errno
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (errno != 0) throwErrorMessage("/!\\ ERROR /!\\: createSocketReceiver - Socket");
	printf(ANSI_COLOR_GREEN "Receiver Socket successfully created...\n" ANSI_COLOR_RESET);

	bzero((char *) &sa_C, sizeof(struct sockaddr_in));
	sa_C.sin_family = AF_INET;
	sa_C.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_C.sin_port = htons(TDP_port_S);
	errno = 0; //reset errno
	bind(sock, (struct sockaddr *) &sa_C, sizeof(struct sockaddr));

	if (errno != 0) throwErrorMessage("/!\\ ERROR /!\\: createSocketReceiver - Bind");
	printf(ANSI_COLOR_GREEN "Receiver bind successfully created...\n" ANSI_COLOR_RESET);

	errno = 0; //reset errno
	listen(sock, 2);
	if (errno != 0) throwErrorMessage("/!\\ ERROR /!\\: createSocketReceiver - listen");
	printf(ANSI_COLOR_YELLOW "Waiting for a connection...\n" ANSI_COLOR_RESET);

	taille_sa_C = sizeof(struct sockaddr);

	errno = 0; //reset errno
	new_sock = accept(sock, (struct sockaddr *) &sa_C, &taille_sa_C);
	if (errno != 0) throwErrorMessage("/!\\ ERROR /!\\: createSocketReceiver - accept");
	printf(ANSI_COLOR_GREEN "Accepted a connection as receiver\n"ANSI_COLOR_RESET);

	close(sock);
	receiver = new_sock;

	return new_sock;
}

int createSocketSender(char *IP_addr_S, int TDP_port_S) {
	int sock;
	struct sockaddr_in sa_S;
	unsigned int taille_sa_S;

	errno = 0; //reset errno
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (errno != 0) throwErrorMessage("/!\\ ERROR /!\\: createSocketSender - socket");
	printf(ANSI_COLOR_GREEN "Sender bind successfully created\n"ANSI_COLOR_RESET);

	bzero((char *) &sa_S, sizeof(struct sockaddr_in));
	sa_S.sin_family = AF_INET;
	sa_S.sin_addr.s_addr = inet_addr(IP_addr_S);
	sa_S.sin_port = htons(TDP_port_S);

	taille_sa_S = sizeof(struct sockaddr);

	errno = 0; //reset errno
	connect(sock, (struct sockaddr *) &sa_S, taille_sa_S);
	if (errno != 0) throwErrorMessage("/!\\ ERROR /!\\: createSocketSender - connect");
	printf(ANSI_COLOR_GREEN "Connected as sender\n"ANSI_COLOR_RESET);
	sender = sock;

	return sock;
}

int close_sockets() {
	close(receiver);
	close(sender);
	exit(EXIT_SUCCESS);
}