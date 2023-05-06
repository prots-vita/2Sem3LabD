#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
//#include "toFile.h"
#include "func.h"
#include "dialogue.h"

Table *NewTable(Table *table, int size){
	table = malloc(1*sizeof(Table));
	table->n = 0;
	table->csize = -1;
	table->msize = size;
	table->file = "info.bin";
	table->iofile = NULL;
	table->ks = malloc((table->msize)*sizeof(Key *));
	for (int i = 0; i<table->msize; i++){
		table->ks[i] = NULL;
	}
	return table;
}

void clearn(Table *table){
	saveTable(table);
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

int saveTable(Table *table){
	Key* s = NULL;
	FILE *keyfile = fopen("key.bin", "w+b");
	fwrite(&(table->msize), sizeof(int), 1, keyfile);
	int vector = ftell(keyfile), keySpace = 0, len, offsetNext = 0, offsetRealKey = 0, offsetReal = 0, noda = 0, nul = 0, offsetNoda = 0, NodaReal = 0, real = 0;
	int a = 5;
	fseek(keyfile, table->msize*4, SEEK_CUR);
	for (int i = 0; i<table->msize; i++){
		keySpace = ftell(keyfile);
		if (table->ks[i]!=NULL){
		len = strlen(table->ks[i]->key);
		s = table->ks[i];
		while (s!=NULL){
			fwrite(&len, sizeof(int), 1, keyfile);
//			printf("[%s]\n", s->key);
			fwrite(s->key, sizeof(char), len, keyfile);
			offsetNext = ftell(keyfile);
//			fseek(keyfile, 4, SEEK_CUR);
			fwrite(&nul, sizeof(int), 1, keyfile);
			if (s->node!=NULL){
				Node *n = s->node;
				int elem;
				while (n!=NULL){
					offsetNoda = ftell(keyfile);
//					printf("dd: [%d]: ", ftell(keyfile));
					fwrite(&(n->release), sizeof(int), 1, keyfile);
//					printf("%d \n", n->release);
					fwrite(&(n->offset), sizeof(int), 1, keyfile);
					if (n->next!=NULL) NodaReal = ftell(keyfile)+4;
					else NodaReal = 0;
					fwrite(&NodaReal, sizeof(int), 1, keyfile);
					n = n->next;
				}
				real = ftell(keyfile);
				if (s->ksnext!=NULL) offsetRealKey = ftell(keyfile);
				else offsetRealKey = 0;
				GoAndBack(&keyfile, offsetNext, offsetRealKey, real);
			}
			s = s->ksnext;
			offsetRealKey = ftell(keyfile);
		}
		offsetRealKey = ftell(keyfile);
		GoAndBack(&keyfile, vector+i*4, keySpace, offsetRealKey);
		}
	}
	fclose(keyfile);
}

void GoAndBack(FILE **keyfile, int go, int elem, int back){
	fseek(*keyfile, go, SEEK_SET);
	fwrite(&elem, sizeof(int), 1, *keyfile);
	fseek(*keyfile, back, SEEK_SET);
}

void returnTable(Table *table, FILE *keyfile, char *s){
	FILE *file = fopen(s, "r+b");
	int offsetVector, nextKey, len, release, elem, node, elemreal;
	char *key;
	int *Vector = malloc(table->msize*sizeof(int));
	for (int i = 0; i<table->msize; i++){
		fread(&(Vector[i]), sizeof(int), 1, keyfile);
	}
	for (int i = 0; i<table->msize; i++){
		if (Vector[i]==0){
			continue;
		}
		for (int j = 1; j<(table->msize-i); j++){
			if (Vector[i+j]==0) continue;
			copecode(table, keyfile, file);
			break;
		}
	}
	copecode(table, keyfile, file);
	free(Vector);
	fclose(file);
	return;
}

void copecode(Table *table, FILE *keyfile, FILE *file){
	int offsetVector, nextKey, len, release, elem, node, elemreal;
	char *key;
	do {
		if (fread(&len, sizeof(int), 1, keyfile)==0) continue;
		key = malloc((len+1)*sizeof(char));
		fread(key, sizeof(char), len, keyfile);
		key[len] = '\0';
		fread(&nextKey, sizeof(int), 1, keyfile);
		do {
			fread(&(release), sizeof(int), 1, keyfile);
			fread(&(elem), sizeof(int), 1, keyfile);
			elemreal = readInfo(file, elem);
			fread(&(node), sizeof(int), 1, keyfile);
			add(table, key, elemreal, release, 1);
//			printf("%s %d %d\n", key, elem, release);
		} while (node!=0);
		free(key);
	} while (nextKey!=0);
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

int readInfo(FILE *file, int offset){
	int elem;
	fseek(file, offset, SEEK_SET);
	fread(&elem, 1, sizeof(int), file);
	return elem;
}


void print(Table *table, FILE* file){
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
			int elem;
			while (n!=NULL){
				elem = readInfo(file, n->offset);
				printf("		{info: [%d], release: [%d]}\n", elem, n->release);
				n = n->next;
			}
			}
			s = s->ksnext;
		}
		printf("\n");
	}
}


int ind(Table *table, char *str){
	return str[0]%(table->msize);
}

/*int ind(Table *table, char *str){
	int seed = 131, hash = 0;
	for (int i = 0; i<strlen(str); i++){
		hash = (hash*seed)+str[i];
	}
	return hash%(table->msize);
}*/

/*int ind(Table *table, char *str){
	int hash = 1315423911;
	for (int i = 0; i<strlen(str); i++){
		hash ^= ((hash << 5) + str[i] + (hash >> 2));
	}
	return (hash & 0x7FFFFFFF);
}*/

Key* simkey(Table *table, char* key, Key** prev){
	int i = ind(table, key);
	if (table->ks[i]==NULL){
		return NULL;
	}
	Key *s = table->ks[i];
	while (s!=NULL){
//		printf(" %s ", s->key);
//		printf(" %s ", key);
		if (strcmp(s->key, key)==0){
			return s;
		}
		(*prev) = s;
		s = s->ksnext;
	}
	return NULL;
}



Node* newNode(int offset, int rel){
	Node *new = malloc(1*sizeof(Node));
	new->release = rel;
	new->offset = offset;
	new->next = NULL;
	return new;
}

Key* newKey(char *str, int offset, int rel){
	Key* new = malloc(1*sizeof(Key));
	new->key = strdup(str);
	new->release = 1;
	new->node = newNode(offset, rel);
	new->ksnext = NULL;
	return new;
}

int add(Table *table, char *key, int elem, int rel, int dob){
	int offset;
	if (dob==1){
		fseek(table->iofile, table->n, SEEK_SET);
		offset = ftell(table->iofile);
		fwrite(&elem, sizeof(int), 1, table->iofile);
		table->n = ftell(table->iofile);
	} else {
		offset = elem;
	}
	int i = ind(table, key);
	Key *sim, *prev;
	if ((sim = simkey(table, key, &prev))!=NULL){
		Node *n = sim->node;
		sim->node = newNode(offset, rel);
		sim->node->next = n;
		sim->release+=1;
		return 1;
	}
	if (table->ks[i]==NULL){
		table->ks[i] = newKey(key, offset, rel);
		return 0;
	}
	Key* s = table->ks[i];
	table->ks[i] = newKey(key, offset, rel);
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
		nprev = n;
		n = n->next;
	}
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



int find1(Table *table, Table *tableCopy, char* key){
	Key *s, *prev;
	s = simkey(table, key, &prev);
	if (s==NULL){
		return 1;
	}
	Node *n = s->node;
	int elem;
	while (n!=NULL){
		add(tableCopy, key, n->offset, n->release, 0);
		n = n->next;
	}
	free(key);
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
	int elem = readInfo(table->iofile, n->offset);
	return elem;
}



