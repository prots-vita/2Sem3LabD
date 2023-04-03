#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
//#include "toFile.h"
#include "func.h"
#include "dialogue.h"

Table *NewTable(Table *table, int size){
	table = malloc(1*sizeof(Table));
	table->csize = -1;
	table->msize = size;
	table->ks = malloc((table->msize)*sizeof(Key *));
	for (int i = 0; i<table->msize; i++){
		table->ks[i] = NULL;
	}
	return table;
}

/*void clearn(Table *table){
	for (int i = 0; i<table->msize; i++){
		if (table->ks[i]->key != NULL){
			free(table->ks[i]->key);
		}
		table->ks[i]->release = 0;
		if (table->ks[i]->key != NULL){
			free(table->ks[i]->key);
		}
	}
	table->msize = 0;
	table->csize = -1;
	if (table->ks!=NULL) free(table->ks);
	if (table!=NULL) free(table);
}*/

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

int strint(int elem){
	int in = 0;
	while (elem!=0){
		in+=1;
		elem/=10;
	}
	return in;
}


void print(const Table *table){
	Key* s = NULL;
	for (int i = 0; i<table->msize; i++){
		if (table->ks[i]==NULL){
			continue;
		}
		printf("%d\n", i);
		s = table->ks[i];
		while (s!=NULL){
			printf("{key: [%s], info: [%d], release: [%d]}\n", s->key, s->info, s->release);
			if (s->node!=NULL){
			Node *n = s->node;
			while (n!=NULL){
				printf("{key: [%s], info: [%d], release: [%d]}\n", s->key, n->info, n->release);
				n = n->next;
			}
			}
			s = s->ksnext;
		}
		printf("\n");
	}
}



Key* simkey(Table *table, char* key, int i){
	if (table->ks[i]==NULL){
		return NULL;
	}
	Key *s = table->ks[i];
	while (s!=NULL){
		if (strcmp(s->key, key)==0){
			return s;
		}
		s = s->ksnext;
	}
	return NULL;
}

/*int index(Table *table, char *str){
	return (str[0]-' ')%(table->msize);
}*/

Key* newKey(char *str, int info){
	Key* new = malloc(1*sizeof(Key));
	new->key = strdup(str);
	new->info = info;
	new->release = 1;
	new->node = NULL;
	new->ksnext = NULL;
	return new;
}

Node* newNode(int info, int rel){
	Node *new = malloc(1*sizeof(Node));
	new->release = rel;
	new->info = info;
	new->next = NULL;
	return new;
}

int add(Table *table, char *key, int elem){
	int i = (key[0]-' ')%(table->msize);
	Key *sim;
	int rel = 1;
	if ((sim = simkey(table, key, i))!=NULL){
		if (sim->node!=NULL){
			rel = sim->node->release+1;
		}
		Node *n = sim->node;
		sim->node = newNode(elem, rel);
		sim->node->next = n;
		sim->release+=1;
		return 0;
	}
	if (table->ks[i]==NULL){
	//	table->csize+=1;
		table->ks[i] = newKey(key, elem);
		return 0;
	}
	Key* s = table->ks[i];
	table->ks[i] = newKey(key, elem);
	table->ks[i]->ksnext = s;
	return 0;
}

/*int isFull(Table *table){
	if (table->msize==(table->csize+1)){
		return 1;
	}
	return 0;
}*/


/*int idElem(Table *table, int key){
	int ind = -1;
	for (int i = 0; i<=table->csize; i++){
		if (table->ks[i].key==key){
			ind = i;
			break;
		}
	}
	return ind;
}*/
	
/*int delete(Table *table, int key){
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
}*/


char* find(Table *table, char* key){
	for (int i = 0; i<table->msize; i++){
		if (table->ks[i]==NULL) continue;
		if (strcmp(table->ks[i].key, key)){
			return table->ks[i].info->info;
		}
	}
	return "no elem\n";
}


/*void myFunc(Table *table, Table **table2, int begin, int end){
	char *s = NULL;
	int key = 0;
	for (int i = 0; i<=table->csize; i++){
		if (begin<=table->ks[i].key && table->ks[i].key<=end){
			key = table->ks[i].key;
			s = strdup(table->ks[i].info->info);
			add((*table2), key, s);
		}
	}
}*/


