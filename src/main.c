#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

    char buffer[200];

    while (1) {
        char action;
        while (1) {
            printf("> ");
            action = getchar();

            if (action == 'w') { // write a message

                break;
            } else if (action == 'n') { // Nothing to say
                // TODO
            } else if (action == 'c') {
                printf("close the client \n");
                return 1;
            } else if (action == 'h') {
                printf("Press w to write a message\n");
                printf("Press n if you have nothing to say\n");
                printf("Press q to quit\n");
            }

            getchar();
        }

        memset(buffer, '\0', sizeof(buffer));

//        sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "nouveauBlabla");
//
//        envoie(priseEmission, buffer, strlen(buffer));

    }

    return 0;
}


