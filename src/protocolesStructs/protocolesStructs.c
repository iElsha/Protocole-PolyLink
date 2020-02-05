//
// Created by maxence on 04/02/2020.
//
/* Creation d'un container */
#include <stdlib.h>
#include <stdio.h>
#include "../util/utils.h"
#include "../util/list/linked_list.h"
#include "../config/configIps.h"
#include "protocolesStructs.h"

const int FLAG_MESSAGE = 1;
const int FLAG_ACK = 2;
const int FLAG_ERR = 3;

struct Container* parseContainer(char * stringPacket){

    struct CONFIG_PACKET* config = getConfigPacket();
    struct Container* packet = createContainer();
    int headread = 0;
    packet->nbMessage = StringToInt(substring(stringPacket,headread,(config->SIZE_NBMESSAGE)+headread));
    headread += config->SIZE_NBMESSAGE;

    for (int i = 0; i < packet->nbMessage; i++){
        list_insert_footer(StringToInt(substring(stringPacket,headread,headread+config->SIZE_DEST)),packet->dests);
        headread += config->SIZE_DEST;
    }
    for (int i = 0; i < packet->nbMessage; i++){
        list_insert_footer(StringToInt(substring(stringPacket,headread,headread+config->SIZE_SIZE)),packet->sizes);
        headread += config->SIZE_SIZE;
    }
    for (int i = 0; i < packet->nbMessage; i++){
        int flag = StringToInt(substring(stringPacket,headread,headread+config->SIZE_FLAG));
        headread += config->SIZE_FLAG;
        if(flag == FLAG_ACK || flag == FLAG_ERR){
            list_insert_footer(createFlag1(flag),packet->flags);
        } else {
            int source = StringToInt(substring(stringPacket,headread,headread+config->SIZE_SOURCE));
            headread += config->SIZE_SOURCE;
            int checksum = StringToInt(substring(stringPacket,headread,headread+config->SIZE_SOURCE));
            headread += config->SIZE_SOURCE;
            int idbroadcast = StringToInt(substring(stringPacket,headread,headread+config->SIZE_SOURCE));
            headread += config->SIZE_SOURCE;
            char* msg = substring(stringPacket,headread,headread+list_getElem(i,packet->sizes));
            headread += list_getElem(i,packet->sizes);
            struct Message * message = createMessage(msg);
            struct HeaderMessage* headerMessage = createHeaderMessage(source,checksum,idbroadcast,message);
            list_insert_footer(createFlag(FLAG_MESSAGE,headerMessage),packet->flags);
        }
    }
    return packet;
}

char* stringifyContainer (struct Container* packet) {

    struct CONFIG_PACKET* config = getConfigPacket();

    char * stringpacket = padLeft(IntToString(packet->nbMessage),'0',config->SIZE_NBMESSAGE);

    for (int i = 0; i < packet->nbMessage; i++){
        stringpacket = concat(stringpacket,padLeft(IntToString(list_getElem(i,packet->dests)),'0',config->SIZE_DEST));
    }
    for (int i = 0; i < packet->nbMessage; i++){
        stringpacket = concat(stringpacket,padLeft(IntToString(list_getElem(i,packet->sizes)),'0',config->SIZE_SIZE));
    }
    for (int i = 0; i < packet->nbMessage; i++){
        struct Flag* flag = list_getElem(i,packet->flags);
        stringpacket = concat(stringpacket,padLeft(IntToString(flag->flag),'0',config->SIZE_SIZE));
        if(flag->flag != FLAG_ACK && flag->flag != FLAG_ERR){
            stringpacket = concat(stringpacket,padLeft(IntToString(flag->headerMessage->source),'0',config->SIZE_SOURCE));
            stringpacket = concat(stringpacket,padLeft(IntToString(flag->headerMessage->checksum),'0',config->SIZE_CHECKSUM));
            stringpacket = concat(stringpacket,padLeft(IntToString(flag->headerMessage->idBroadcast),'0',config->SIZE_IDBROADCAST));
            stringpacket = concat(stringpacket,flag->headerMessage->message->data);
        }
    }
    return  stringpacket;
}

struct Container* createContainer() {
    struct Container* container = (struct Container*) malloc(sizeof(struct Container));
    container->nbMessage = 0;
    container->dests = list_create();
    container->sizes = list_create();
    container->flags = list_create();
    return container;
}

/* Ajout d'un message dans le container*/
void addMessage(struct Container* packet, int source, int dest, char* msg){
    addMessageB(packet,source,dest,msg, 0);
}

/* Ajout d'un message dans le container*/
void addMessageB(struct Container* packet, int source, int dest, char* msg, int idBroadcast) {
    struct Message* message = createMessage(msg);
    struct HeaderMessage* headerMessage = createHeaderMessage_new(source,idBroadcast,message);
    struct Flag* flag = createFlag(FLAG_MESSAGE,headerMessage);
    int size = getLength(msg);
    packet->nbMessage ++;
    list_insert_footer(dest,packet->dests);
    list_insert_footer(size,packet->sizes);
    list_insert_footer(flag,packet->flags);
}

/* Creation et Ajout d'un acquittement dans le container*/
void createAck(struct Container* packet, int dest) {
    struct Flag* flag = createFlag1(FLAG_ACK);
    int size = 0;
    packet->nbMessage ++;
    list_insert_footer(dest,packet->dests);
    list_insert_footer(size,packet->sizes);
    list_insert_footer(flag,packet->flags);
}

/* Creation et Ajout d'une error dans le container*/
void createError(struct Container* packet, int dest) {
    struct Flag* flag = createFlag1(FLAG_ERR);
    int size = 0;
    packet->nbMessage ++;
    list_insert_footer(dest,packet->dests);
    list_insert_footer(size,packet->sizes);
    list_insert_footer(flag,packet->flags);
}

struct Message* createMessage(char * msg){
    struct Message* message = (struct Message*) malloc(sizeof(struct Message));
    message->data = msg;
    return message;
}

struct HeaderMessage* createHeaderMessage(int source,int checksum, int idBroadcast, struct Message* message){
    struct HeaderMessage* headerMessage = (struct HeaderMessage*) malloc(sizeof(struct HeaderMessage));
    headerMessage->source = source;
    headerMessage->idBroadcast = idBroadcast;
    headerMessage->checksum = checksum;
    headerMessage->message = message;
    return headerMessage;
}

struct HeaderMessage* createHeaderMessage_new(int source, int idBroadcast, struct Message* message){
    int checksum = calcCheckSum(message->data,getConfigPacket()->SIZE_CHECKSUM);
    return createHeaderMessage(source,checksum,idBroadcast,message);
}

struct Flag* createFlag1(int flag){
    createFlag(flag, NULL);
}

struct Flag* createFlag(int idFlag, struct HeaderMessage* headerMessage){
    struct Flag* flag = (struct Flag*) malloc(sizeof(struct Flag));
    flag->flag = idFlag;
    flag->headerMessage = headerMessage;
    return flag;
}
/*
void deleteContainer(struct Container* packet){
    list_destroy(packet->dest)
    list_destroy(packet->sizes)
    list_destroy(packet->flags)
}

void deleteFlag(struct Flag* flag){

}
void deleteHeaderMessage(struct HeaderMessage* headermessage){

}
void deleteMessage(struct Message* message){

}
 */