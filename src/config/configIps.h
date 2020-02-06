//
// Created by maxence on 04/02/2020.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef PROTOCOLE_POLYLINK_CONFIGIPS_H
#define PROTOCOLE_POLYLINK_CONFIGIPS_H

/**
 * data struct which handle IP config
 */
struct address {
	char *ADRESSE_EMETTEUR;
	char *ADRESSE_RECEPTEUR;
	int PORT_RECEPTION;
	int PORT_EMISSION;
	int ID_COMPUTER;
};

struct CONFIG_PACKET {
    int SIZE_NBMESSAGE;
    int SIZE_DEST;
    int SIZE_SIZE;
    int SIZE_FLAG;
    int SIZE_SOURCE;
    int SIZE_IDBROADCAST;
    int SIZE_CHECKSUM;
};
/**
 * select the user config if possible
 * @return the config of the user depending on what he asked, -1 if there was an error, 1 if it worked.
 */
int getConfig(int, struct address *);

struct CONFIG_PACKET* getConfigPacket();
struct list* getIDS_COMPUTER();

#endif //PROTOCOLE_POLYLINK_CONFIGIPS_H
#pragma clang diagnostic pop