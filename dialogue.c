#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "toFile.h"
#include "func.h"
#include "dialogue.h"

int dialog(const char *msgs[], int N) {
	char *errmsg = "";
	int rc;
	int i, n;
	do{
		puts(errmsg);
		errmsg = "You are wrong. Repeate, please!";
		for(i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("Make your choice: --> ");
		n = scan(&rc);
		if(n == 1)
			rc = 0;
	} while(rc < 0 || rc >= N);
	return rc;
}

int Dshow(Table *table){
	print(table, table->iofile);
	return 0;
}


int Dfile(Table *table){
	char *file = "file.txt";
	FILE *fp;
	int elem, rel = 1;
	char *key = NULL;
	Key *prev, *sim;
	OpenRead(file, &fp);
       	while (1){
		if (Read(fp, &elem, &key)){
			if ((sim = simkey(table, key, &prev))!=NULL){
				if (sim->node!=NULL){
					rel = sim->node->release+1;
				}
			}
			add(table, key, elem, rel, 1);
			free(key);
		} else {
			break;
		}
	}
	fclose(fp);
	return 0;
}

int Dadd(Table *table){
	int elem, incor, rel = 1, max = 0;
	char *key = readline("Put an key: ");
	while (key==0){
		return 1;
	}
	Key *prev, *sim;
	if ((sim = simkey(table, key, &prev))!=NULL){
		Node *n = sim->node;
		while (n!=NULL){
			rel = n->release;
			if (rel>max) max = rel;
			n = n->next;

		}
	}
	rel = max+1;
	printf("Put a info :");
	if (scan(&elem)) return 1;
	add(table, key, elem, rel, 1);
	free(key);
	return 0;
}


int Ddelete(Table *table){
	char *key = readline("Put an key: ");
	while (key==0){
		return 1;
	}
	if (delete(table, key)){
		printf("There is no such key\n");
	}
	free(key);
	return 0;
}

int DdeleteRes(Table *table){
	int release;
	char *key = readline("Put an key: ");
	while (key==0){
		return 1;
	}
	printf("Put a release :");
	if (scan(&release)) return 1;
	if (deleteRes(table, key, release)){
		printf("There is no such key\n");
	}
	free(key);
	return 0;
}

/*int Dfind(Table *table){
	printf("Put key to find an elem\n");
	char *key = readline("Put an key: ");
	while (key==0){
		return 1;
	}
	int *arr = find(table, key);
	if (arr[0]==1){
		printf("no elem\n");
		free(key);
		free(arr);
		return 0;
	}
	for (int i = 1; i<arr[0]; i++){
		printf("key: [%s], info: [%d]\n", key, arr[i]);
	}
	free(key);
	free(arr);
	return 0;
}*/

int DfindRes(Table *table){
	int release;
	printf("Put key to find an elem\n");
	char *key = readline("Put an key: ");
	while (key==0){
		return 1;
	}
	printf("Put a release :");
	if (scan(&release)) return 1;
	int info = findRes(table, key, release);
	if (info==-1){
		printf("no elem\n");
	} else {
		printf("key: [%s], info: [%d]", key, info);
	}
	free(key);
	return 0;
}

int Dfind1(Table *table){
	Table *tableCopy;
	tableCopy = NewTable(table, table->msize);
	int release;
	printf("Put key to find an elem\n");
	char *key = readline("Put an key: ");
	while (key==0){
		return 1;
	}
	if (find1(table, tableCopy, key)){
		free(key);
	}
	print(tableCopy, table->iofile);
	clearn(tableCopy);
	return 0;
}


