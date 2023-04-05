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

void clearn(Table *table){
	for (int i = 0; i<table->msize; i++){
		while (table->ks[i] != NULL){
			while (table->ks[i]->node!=NULL){
				Node *n = table->ks[i]->node->next;
				free(table->ks[i]->node);
				table->ks[i]->node = n;
			}
			Key* s = table->ks[i]->ksnext;
			free(table->ks[i]->key);
			free(table->ks[i]);
			table->ks[i] = s;
		}
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
		printf("[%d]\n", i);
		s = table->ks[i];
		while (s!=NULL){
			printf("	key: [%s] rel: [%d]\n", s->key, s->release);
			if (s->node!=NULL){
			Node *n = s->node;
			while (n!=NULL){
				printf("		{info: [%d], release: [%d]}\n", n->info, n->release);
				n = n->next;
			}
			}
			s = s->ksnext;
		}
		printf("\n");
	}
}


int ind(Table *table, char *str){
	return (str[0]-' ')%(table->msize);
}

Key* simkey(Table *table, char* key, Key** prev){
	int i = ind(table, key);
	if (table->ks[i]==NULL){
		return NULL;
	}
	Key *s = table->ks[i];
	while (s!=NULL){
		if (strcmp(s->key, key)==0){
			return s;
		}
		(*prev) = s;
		s = s->ksnext;
	}
	return NULL;
}



Node* newNode(int info, int rel){
	Node *new = malloc(1*sizeof(Node));
	new->release = rel;
	new->info = info;
	new->next = NULL;
	return new;
}

Key* newKey(char *str, int info, int rel){
	Key* new = malloc(1*sizeof(Key));
	new->key = str;
	new->release = 1;
	new->node = newNode(info, rel);
	new->ksnext = NULL;
	return new;
}

int add(Table *table, char *key, int elem){
	int i = ind(table, key);
	Key *sim, *prev;
	int rel = 1;
	if ((sim = simkey(table, key, &prev))!=NULL){
		if (sim->node!=NULL){
			rel = sim->node->release+1;
		}
		Node *n = sim->node;
		sim->node = newNode(elem, rel);
		sim->node->next = n;
		sim->release+=1;
		return 1;
	}
	if (table->ks[i]==NULL){
		table->ks[i] = newKey(key, elem, 1);
		return 0;
	}
	Key* s = table->ks[i];
	table->ks[i] = newKey(key, elem, 1);
	table->ks[i]->ksnext = s;
	return 0;
}


void delKey(Table *table, int i, Key* s, Key* prev){
	if (prev==NULL){
		table->ks[i] = s->ksnext;
	} else {
		prev->ksnext = s->ksnext;
	}
	free(s->key);
	free(s);
	return;
}

int deleteRes(Table *table, char *key, int release){
	Key *s, *prev = NULL;
	int i = ind(table, key);
	s = simkey(table, key, &prev);
	if (s==NULL || s->release<release){
		return 1;
	}
	int flag = 0;
	Node *n = s->node, *nprev = NULL;
	while (n!=NULL){
		if (release==n->release){
			flag = 1;
			break;
		}
//	for (int j = s->release; j>release; j--){
//		n->release--;
		nprev = n;
		n = n->next;
	}
//	s->release--;
	if (nprev!=NULL){
		nprev->next = n->next;
	} else {
		s->node = n->next;
	}
	if (s->node==NULL){
		delKey(table, i, s, prev);
	}
	free(n);
	return 0;
}
	
int delete(Table *table, char* key){
	Key *s, *sr, *prev = NULL;
	int i = ind(table, key);
	s = simkey(table, key, &prev);
	if (s==NULL){
		return 1;
	}
	Node *n = s->node, *nr;
	while (n!=NULL){
		nr = n->next;
		free(n);
		n = nr;
	}
	delKey(table, i, s, prev);
	return 0;
}


/*int* find(Table *table, char* key){
	int *ar = malloc(80*sizeof(int));
	ar[0] = 1;
	Key *s, *prev;
	s = simkey(table, key, &prev);
	if (s==NULL){
		return ar;
	}
	Node *n = s->node;
	while (n!=NULL){
		ar[0] += 1;
		ar[ar[0]-1] = n->info;
		n = n->next;
	}
	return ar;
}*/

int find1(Table *table, Table *tableCopy, char* key){
	Key *s, *prev;
	s = simkey(table, key, &prev);
	if (s==NULL){
		return 1;
	}
	Node *n = s->node;
	while (n!=NULL){
		add(tableCopy, key, n->info);
		n = n->next;
	}
	return 0;
}

int findRes(Table *table, char* key, int release){
	Key *s, *prev;
	s = simkey(table, key, &prev);
	if (s==NULL || s->release<release){
		return -1;
	}
	Node *n = s->node;
	for (int i = 1; i<release; i++){
		n = n->next;
	}
	return n->info;
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


