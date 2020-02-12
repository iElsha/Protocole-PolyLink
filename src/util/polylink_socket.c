#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int create_socket_receiver(int TDP_port_S) {
    int sock, new_sock;
    struct sockaddr_in sa_C;
    unsigned int taille_sa_C;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    bzero((char *) &sa_C, sizeof(struct sockaddr_in));
    sa_C.sin_family = AF_INET;
    sa_C.sin_addr.s_addr = htonl(INADDR_ANY);
    sa_C.sin_port = htons(TDP_port_S);

    bind(sock, (struct sockaddr *) &sa_C, sizeof(struct sockaddr));

    listen(sock, 2);
    perror("Listen ");

    taille_sa_C = sizeof(struct sockaddr);

    new_sock = accept(sock, (struct sockaddr *) &sa_C, &taille_sa_C);
    perror("accept ");

    close(sock);


    return new_sock;
}

int create_socket_sender(char *IP_addr_S, int TDP_port_S) {
    int sock;
    struct sockaddr_in sa_S;
    unsigned int taille_sa_S;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    bzero((char *) &sa_S, sizeof(struct sockaddr_in));
    sa_S.sin_family = AF_INET;
    sa_S.sin_addr.s_addr = inet_addr(IP_addr_S);
    sa_S.sin_port = htons(TDP_port_S);

    taille_sa_S = sizeof(struct sockaddr);

    connect(sock, (struct sockaddr *) &sa_S, taille_sa_S);
    perror("Connect ");

    return sock;
}

int close_socket(int socket) {
    close(socket);
    return 1;
}