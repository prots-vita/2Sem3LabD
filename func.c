#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "toFile.h"
#include "func.h"

Table *NewTable(Table *table, int size){
	table = malloc(1*sizeof(Table));
	table->csize = -1;
	table->msize = size;
	table->ks = malloc((table->msize)*sizeof(Key));
	for (int i = 0; i<table->msize; i++){
		table->ks[i].key = 0;
		table->ks[i].info = malloc(1*sizeof(Item));
		table->ks[i].info->info = NULL;
		table->ks[i].info->key = 0;
		table->ks[i].info->ind = 0;
	}
	return table;
}

void clearn(Table *table){
	for (int i = 0; i<table->msize; i++){
		table->ks[i].key = 0;
		if (table->ks[i].info->info!=NULL) free(table->ks[i].info->info);
		table->ks[i].info->key = 0;
		table->ks[i].info->ind = 0;
		free(table->ks[i].info);
	}
	table->msize = 0;
	table->csize = -1;
	free(table->ks);
	free(table);
}

int scan(int *elem){
	int n;
	while ((n=scanf("%d", elem))!=1 || (*elem)<0){
		if (n==-1){
			scanf("%*[^\n]");
			return 1;
		}
		printf("Sorry, again..\n");
		scanf("%*[^\n]");
	}
	scanf("%*[^\n]");
	return 0;
}

int Dshow(Table *table){
	print(table);
	return 0;
}

void print(const Table *table){
	for (int i = 0; i<=table->csize; i++){
			printf("key: [%d], info: [%s]\n", table->ks[i].key, table->ks[i].info->info);
	}
}



int simkey(Table *table, int key){	
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			return 1;
		}
	}
	return 0;
}

int Dfile(Table *table){
	char *file = "file.txt";
	FILE *fp;
	int key;
	char *str = NULL;
	OpenRead(file, &fp);
       	while (1){
		if (Read(fp, &key, &str)){
			if (isFull(table)){
				free(str);
				break;
			}
			if (simkey(table, key)) continue;
			add(table, key, str);
		} else {
			break;
		}
	}
	return 0;
}

int Dadd(Table *table){
	int key, incor;
	printf("Put a key :");
	if (scan(&key)) return 1;
	if (simkey(table, key)){
		printf("Put another key\n");
		if (Dadd(table)){
			return 1;
		}
		return 0;
		
	}
	char *str = readline("Put an info: ");
	while (str==0){
		return 1;
	}
	add(table, key, str);
	return 0;
}

int add(Table *table, int key, char *str){
	table->csize++;
	table->ks[table->csize].key = key;
	
	if (table->ks[table->csize].info->info !=NULL){
		free(table->ks[table->csize].info->info);
	}
	table->ks[table->csize].info->info = strdup(str);
	table->ks[table->csize].info->key = key;
	table->ks[table->csize].info->ind = table->csize;
	free(str);
	return 0;
}

int isFull(Table *table){
	if (table->msize==(table->csize+1)){
		return 1;
	}
	return 0;
}

int Ddelete(Table *table){
	printf("Put key to delete\n");
	int key, ind = -1, n;
	if (scan(&key)) return 1;
	if (delete(table, key)){
		printf("There is no such key\n");
	}
	return 0;
}

int idElem(Table *table, int key){
	int ind = -1;
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			ind = i;
			break;
		}
	}
	return ind;
}
	
int delete(Table *table, int key){
	int ind;
	if ((ind = idElem(table, key))==-1) return 1;
	for (int i = ind; i<table->csize; i++){
		free(table->ks[i].info->info);
		table->ks[i].info->info = strdup(table->ks[i+1].info->info);
		table->ks[i].key = table->ks[i+1].key;
		table->ks[i].info->key = table->ks[i+1].key;
		table->ks[i].info->ind = table->ks[i+1].info->ind;
	}
	table->csize--;
	return 0;
}

int Dfind(Table *table){
	printf("Put key to find an elem\n");
	int key;
	if (scan(&key)){
		printf("no elem\n");
		return 1;
	}
	printf("%s\n", find(table, key));
	return 0;
}

char* find(Table *table, int key){
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			return table->ks[i].info->info;
		}
	}
	return "no elem\n";
}

int Dtask(Table *table){
	Table *tableCopy;
	tableCopy = NewTable(table, table->msize);
	printf("Put range of keys in format int-int\n");
	int begin, end, size = 0;
	scanf("%d%*c%d", &begin, &end);
	myFunc(table, &tableCopy, begin, end);
	print(tableCopy);
	clearn(tableCopy);
	return 0;
}

void myFunc(Table *table, Table **table2, int begin, int end){
	char *s = NULL;
	int key = 0;
	for (int i = 0; i<=table->csize; i++){
		if (begin<=table->ks[i].key && table->ks[i].key<=end){
			key = table->ks[i].key;
			s = strdup(table->ks[i].info->info);
			add((*table2), key, s);
		}
	}
}


