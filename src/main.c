#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config/configIps.h"
#include "util/polylink_socket.h"
#include "util/receive.h"
#include "util/send.h"
#include "protocolesStructs/protocolesStructs.h"
#include "util/utils.h"

int main(int argc, char **argv) {

	char *end;
	char buffer[200];

	if (argc < 2) {
		fprintf(stderr, "You didn't provide enough args. Do not forget the configuration IP ID.\n");
		return -1;
	}

	int configId = (int) strtol(argv[1], &end, 10); // get the configId ID
	struct address addr; // create an address struct
	int configError = getConfig(configId, &addr); // get the configId correspond to the ID

	if (configError == -1) {
		fprintf(stderr, "This configuration doesn't exist, your config ID is out of range.\n");
		return -1;
	}

	int receiver, sender;
	if (addr.ID_COMPUTER == 1) {
		receiver = create_socket_receiver(addr.PORT_RECEPTION);
//		getchar();
		sender = create_socket_sender(addr.ADRESSE_EMETTEUR, addr.PORT_EMISSION);
	} else {
		sender = create_socket_sender(addr.ADRESSE_EMETTEUR, addr.PORT_EMISSION);
//		getchar();
		receiver = create_socket_receiver(addr.PORT_RECEPTION);
	}

	int start = 1;

	while (1) {

		if (start != 1 || addr.ID_COMPUTER != 1) {
			memset(buffer, '\0', sizeof(buffer));

			int receive_error = receive_data(receiver, buffer, sizeof(buffer));

			if (receive_error == -1) {
				fprintf(stderr, "Error on receive\n");
				close_socket(receiver);
				close_socket(sender);
				return -1;
			}

			printf("Message >> '%s'\n", buffer);
		}

		if (start == 1) {
			printf("Press w to write a message\n");
			printf("Press n if you have nothing to say\n");
			printf("Press q to quit\n");
		}
		start = 0;

		char action[10];
		int nothing = 0;
		while (1) {
			printf("?> ");
			memset(action, '\0', sizeof(action));
			fgets(action, sizeof(action), stdin);
			strtok(action, "\n");

			if (action[0] == 'w') { // write a message
				break;
			} else if (action[0] == 'n') { // Nothing to say
				nothing = 1;
				send_data(sender, "Nothing to say", sizeof("Nothing to say"));
				break;
			} else if (action[0] == 'q') {
				printf("Closing the client \n");
				close_socket(receiver);
				close_socket(sender);
				return 1;
			} else if (action[0] == 'h') {
				printf("Press w to write a message\n");
				printf("Press n if you have nothing to say\n");
				printf("Press q to quit\n");
			}
		}

		if(!nothing) {

			memset(buffer, '\0', sizeof(buffer));

			printf("m> ");
			fgets(buffer, sizeof(buffer), stdin);
			strtok(buffer, "\n");

			int send_error = send_data(sender, buffer, sizeof(buffer));

			if (send_error == -1) {
				fprintf(stderr, "Error on sender\n");
				close_socket(receiver);
				close_socket(sender);
				return -1;
			}
		}
	}
}


