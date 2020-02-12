#include "utils.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int calcCheckSum(char *data, int size) {
	int checksum = 0;
	for (int i = 0; i < strlen(data); i++) {
		checksum = (checksum + ((int) data[i])) % size;
	}
	return checksum;
}

int StringToInt(char *data) {
	char *endptr = NULL; // pointer to additional chars
	int base = 10; // numeric base
	long number = 0; // variable holding return

	// reset errno to 0 before call
	errno = 0;

	// call to strtol assigning return to number and it automatically set errno
	number = strtol(data, &endptr, base);

	// output original string of characters considered
	//printf("\n string : %s\n base   : %d\n endptr : %s\n\n", data, base, endptr);

	// test return to number and errno values
	if (data == endptr)
		fprintf(stderr, " number : %lu  invalid  (no digits found, 0 returned)\n", number);
	else if (errno == ERANGE && number == LONG_MIN)
		fprintf(stderr, " number : %lu  invalid  (underflow occurred)\n", number);
	else if (errno == ERANGE && number == LONG_MAX)
		fprintf(stderr, " number : %lu  invalid  (overflow occurred)\n", number);
	else if (errno != 0 && number == 0)
		fprintf(stderr, " number : %lu  invalid  (unspecified error occurred)\n", number);
//	else if (errno == 0 && data && !*endptr)
//		printf(" number : %lu    valid  (and represents all characters read)\n", number);
	else if (errno == 0 && data && *endptr != 0)
		printf(" number : %lu    valid  (but additional characters remain)\n", number);

	return (int) number;
}

char *IntToString(int data) {
	int size = (data / 10) + 1;
	char *string = (char *) malloc(sizeof(char) * (size + 1));
	sprintf(string, "%d", data);
	return string;
}

char *padLeft(char *data, char c, int lenght) {
	char *string = copy(data);
	int size = (int) strlen(data);
	if (size < lenght) {
		string = (char *) malloc(sizeof(char) * (lenght + 1));
		for (int i = lenght - 1; i >= lenght - size; i--) {
			string[i] = data[i - lenght + size];
		}
		for (int i = 0; i < lenght - size; i++) {
			string[i] = c;
		}
	}
	return string;
}

char *substring(const char *data, int start, int end) {
	int lenght = end - start;
	char *string = (char *) malloc(sizeof(char) * (lenght + 1));
	for (int i = start; i < end; i++) {
		string[i - start] = data[i];
	}
	return string;
}

/**
 * concat two strings
 * @param s1 char*
 * @param s2 char*
 * @return char* concat string
 */
char *concat(char *s1, char *s2) {
	char *string = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	strcpy(string, s1);
	strcat(string, s2);
	return string;
}

/**
 * copy one string in another one
 * @param string
 * @return
 */
char *copy(char *s) {
	int lenght = (int) strlen(s);
	char *string = (char *) malloc(sizeof(char) * (lenght + 1));
	for (int i = 0; i < lenght; i++) {
		string[i] = s[i];
	}
	return string;
}
