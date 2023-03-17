#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int OpenWrite(char *file, FILE **fp){
	if ((*fp = fopen(file, "w"))==NULL){
		printf("Error, occured while opening file\n");
		return 1;
	}
	return 0;
}

int OpenRead(char *file, FILE **fp){
	if ((*fp = fopen(file, "r"))==NULL){
		printf("Array not created\n");
		return 1;
	}
	return 0;
}

int Read(FILE *fp, int *key, char **str){
	char s[81];
	if (fscanf(fp, "%d %s", key, s)!=EOF){
		(*str) = strdup(s);
		return 1;
	}
	return 0;
}	

int Write(FILE *fp, char c){
	fprintf(fp, "%c", c);
}
