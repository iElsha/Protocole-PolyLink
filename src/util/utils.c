#include "utils.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
int getLength(void *tab) {
	return (int) sizeof(tab) / sizeof(tab[0]);
}

int calcCheckSum(char* data, int size){
    int checksum = 0;
    for(int i =0; i < getLength(data); i++){
        checksum = (checksum + ((int) data[i]))%size;
    }
    return checksum;
}

int StringToInt (char* data){
    return atoi(data);
}

char* IntToString (int data) {
    int size = (data%10) + 1;
    char * string = (char*)malloc(sizeof(char)*size);
    sprintf(string,"%d",data);
    return string;
}
char* padLeft(char* data, char c, int lenght){
    char * string = data;
    int size = strlen(data);
    if (size < lenght){
        string = (char*)malloc(sizeof(char)*lenght);
        for (int i = lenght-1; i>=lenght-size ; i--){
            string[i]=data[i-lenght+size];
        }
        for (int i = 0; i < lenght-size; i++){
            string[i] = c;
        }
    }
    return string;
}
char* substring (char * data, int start, int end){
    int lenght = end-start;
    char* string = (char*)malloc(sizeof(char)*lenght);
    for (int i = start; i < end; i++){
        string[i-start]=data[i];
    }
    return string;
}

char* concat(char* s1, char* s2){
    int l1= strlen(s1);
    int l2 = strlen(s2);
    char * string = (char*)malloc(sizeof(char)*(l1+l2));
    for (int i = 0; i < l1; i++){
        string[i]=s1[i];
    }
    for (int i = l1; i < l1+l2; i++){
        string[i]=s2[i-l1];
    }
    return string;
}
