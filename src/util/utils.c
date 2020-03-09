#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int calcCheckSum(char *data, int size) {
	int checksum = 0;
	for (int i = 0; i < strlen(data); i++) {
		checksum = (checksum + ((int) data[i])) % size;
	}
	return checksum;
}

int StringToInt(char *data) {
	return atoi(data);
}

char *IntToString(int data) {
	int size = (data / 10) + 1;
	char *string = (char *) malloc(sizeof(char) * (size + 1));
	sprintf(string, "%d", data);
	string[size] = '\0';
	return string;
}

char *padLeft(char *data, char c, int lenght) {
	char *string = copy(data);
	int size = (int) strlen(data);
	if (size < lenght) {
		string = (char *) malloc(sizeof(char) * (lenght + 1));
		memset(string, '\0', lenght + 1);
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
	string[lenght] = '\0';
	return string;
}

/**
 * concat two strings
 * @param s1 char*
 * @param s2 char*
 * @return char* concat string
 */
char *concat(char *s1, char *s2) {
	int l1 = (int) strlen(s1);
	int l2 = (int) strlen(s2);
	char *string = (char *) malloc(sizeof(char) * (l1 + l2 + 1));
	for (int i = 0; i < l1; i++) {
		string[i] = s1[i];
	}
	for (int i = l1; i < l1 + l2; i++) {
		string[i] = s2[i - l1];
	}
	string[l1 + l2] = '\0';
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
	string[lenght] = '\0';
	for (int i = 0; i < lenght; i++) {
		string[i] = s[i];
	}
	return string;
}

int isNumber(char *string) {
	for (int i = 0; i < strlen(string); i++) {
		if (string[i] > '9' || string[i] < '0')
			return 0;
	}
	return 1;
}
