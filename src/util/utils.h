#ifndef PROTOCOLE_POLYLINK_UTILS_H
#define PROTOCOLE_POLYLINK_UTILS_H

/**
 * get the number of elements in the array
 * @return the length of an array
 */
int getLength(void *);
int calcCheckSum(char*, int);
int StringToInt (char*);
char* IntToString (int);
char* padLeft(char* , char, int);
char* substring (char *, int, int);
char* concat(char*, char*);
#endif //PROTOCOLE_POLYLINK_UTILS_H
