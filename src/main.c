#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "protocole/protocole.h"
#include "config/configIps.h"
#include "util/polylink_socket.h"
#include "util/receive.h"
#include "util/send.h"
#include "protocolesStructs/protocolesStructs.h"

int main(int argc, char **argv) {

	char *end;
	char buffer[20000];
	if (argc < 2) {
		fprintf(stderr, "You didn't provide enough args. Do not forget to add the configuration IP ID.\n");
		exit(EXIT_FAILURE);
	}

	int configId = (int) strtol(argv[1], &end, 10); // get the configId ID
	struct address addr; // create an address struct
	int configError = getConfig(configId, &addr); // get the configId correspond to the ID

	if (configError == -1) {
		fprintf(stderr, "This configuration doesn't exist, your configuration ID is out of range.\n");
		exit(EXIT_FAILURE);
	}

	int receiver, sender;
	if (addr.ID_COMPUTER != NUMBER_OF_PC) {
		receiver = createSocketReceiver(addr.PORT_RECEPTION);
		sender = createSocketSender(addr.ADRESSE_EMETTEUR, addr.PORT_EMISSION);
	} else {
		sender = createSocketSender(addr.ADRESSE_EMETTEUR, addr.PORT_EMISSION);
		receiver = createSocketReceiver(addr.PORT_RECEPTION);
	}

	int start = 0;
	while (1) {
		if (addr.ID_COMPUTER != 1 || start != 0) {
			memset(buffer, '\0', sizeof(buffer));
			int receive_error = receive_data(receiver, buffer, sizeof(buffer));
			if (receive_error == -1) {
				fprintf(stderr, "Error on receive\n");
				close_sockets();
				exit(EXIT_FAILURE);
			}
		}
		start = 1;
		char *data = PolyLink(buffer, addr.ID_COMPUTER);
		send_data(sender, data, (size_t) strlen(data));
	}
}


