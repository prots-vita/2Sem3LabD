#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "toFile.h"
#include "func.h"

int main(){
	int SIZE;
	printf("Size: \n");
	if (scan(&SIZE)) return 0;
	int msize = 8, incor;
	Table *table;
	table = NewTable(table, SIZE);
	int input, choose, n;
	while (1){
		printf("\n\nPut elem - 1\nDelete elem - 2\nPrint tabl - 3\nFind an elem - 4\nPut elems from file - 5\nmyFunc - 6\n\n");
		if (scan(&choose)) break;
		switch(choose){
			case 1:
				if (isFull(table)){
					printf("TABLE IS FULL\n");
					break;
				}
				while ((incor = add(table))!=0){
					if (incor==1)
						printf("Please, put another key\n");
					else{
						printf("\n");
						print(table);
						clearn(table);
						return 0;
					}
				}
				break;
			case 2:
				if (delete(table)){
					printf("\n");
					print(table);
					clearn(table);
					return 0;
				}
				break;
			case 3:
				print(table);
				break;
			case 4:
				printf("%s", find(table));
				break;
			case 5:

				if (isFull(table)){
					printf("TABLE IS FULL\n");
					break;
				}
				char *file = "file.txt", c;
				int keyF;
				char *elem1 = NULL, *elem2 = NULL;
				int size1 = 0, size2 = 0, flag = 1;
				FILE *fp;
				OpenRead(file, &fp);
			       	while (1){
					if (!Read(fp, &c)) break;
					do {
						if (elem1==NULL){
							elem1 = malloc(1*sizeof(char));
						} else {
							elem1 = realloc(elem1, (size1+1)*sizeof(char));
						}
						elem1[size1] = c;
						size1++;
					} while (flag && Read(fp, &c) && c!=' ');
					flag = 0;
//					if (elem1==NULL){
//						elem1 = malloc(1*sizeof(char));
//					} else {
					elem1 = realloc(elem1, (size1+1)*sizeof(char));
//					}
					elem1[size1] = '\0';
					size1++;
					while (Read(fp, &c) && c!='\n'){
						if (elem2==NULL){
							elem2 = malloc(1*sizeof(char));
						} else {
							elem2 = realloc(elem2, (size2+1)*sizeof(char));
						}
						elem2[size2] = c;
						size2++;
					}
//					if (elem2==NULL){
//						elem2 = malloc(1*sizeof(char));
//					} else {
					elem2 = realloc(elem2, (size2+1)*sizeof(char));
//					}
					elem2[size2] = '\0';
					size2++;
					flag = 1;
					if (elem1!=NULL) keyF = atoi(elem1);
					if (isFull(table)){
						printf("TABLE IS FULL\n");
						break;
					}
					input_file(table, keyF, elem2);
					if (elem1!=NULL){
						free(elem1);
						elem1 = NULL;
					}
					if (elem2!=NULL){
						free(elem2);
						elem2 = NULL;
					}
					size1 = 0;
					size2 = 0;
				}
				if (elem1!=NULL) free(elem1);
				if (elem2!=NULL) free(elem2);
				break;
			case 6:
				Table *tableCopy;
				myFunc(table, &tableCopy);
				print(tableCopy);
				clearn(tableCopy);
				break;
		}
	}
	print(table);
	clearn(table);
	return 0;
}
