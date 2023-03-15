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

void print(const Table *table){
	for (int i = 0; i<=table->csize; i++){
			printf("key: [%d], info: [%s]\n", table->ks[i].key, table->ks[i].info->info);
	}
}

int add(Table *table){
	int key, incor;
	printf("Put a key :");
	if (scan(&key)) return -1;
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			return 1;
		}
	}
	char *str = readline("Put an info: ");
	while (str==0){
		return -1;
	}
	table->csize++;
	table->ks[table->csize].key = key;
	
	if (table->ks[table->csize].info->info !=NULL){
		free(table->ks[table->csize].info->info);
	}
	table->ks[table->csize].info->info = str;
	table->ks[table->csize].info->key = key;
	table->ks[table->csize].info->ind = table->csize;
//	free(str);
	return 0;
}

int input_file(Table *table, int key, char *str){
	int incor;
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			return 1;
		}
	}
	table->csize++;
	table->ks[table->csize].key = key;
	
	if (table->ks[table->csize].info->info !=NULL){
		free(table->ks[table->csize].info->info);
	}
	table->ks[table->csize].info->info = str;
	table->ks[table->csize].info->key = key;
	table->ks[table->csize].info->ind = table->csize;
	return 0;
}

int isFull(Table *table){
	if (table->msize==(table->csize+1)){
		return 1;
	}
	return 0;
}

int delete(Table *table){
	printf("Put key to delete\n");
	int key, ind = -1, n;
	if (scan(&key)) return 1;
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			ind = i;
			break;
		}
	}
	if (ind==-1) return 0;
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

char* find(Table *table){
	printf("Put key to find an elem\n");
	int key;
	if (scan(&key)) return "no elem\n";
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			return table->ks[i].info->info;
		}
	}
	return "no elem\n";
}

void myFunc(Table *table, Table **table2){
	printf("Put range of keys in format int-int\n");
	int begin, end, size = 0;
	scanf("%d%*c%d", &begin, &end);
	for (int i = 0; i<=table->csize; i++){
		if (begin<=table->ks[i].key && table->ks[i].key<=end){
			size++;
		}
	}
	(*table2) = NewTable((*table2), size);
	for (int i = 0; i<=table->csize; i++){
		if (begin<=table->ks[i].key && table->ks[i].key<=end){
			input_file((*table2), table->ks[i].key, table->ks[i].info->info);
		}
	}
}


