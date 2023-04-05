#ifndef _func_h_
#define _func_h_

typedef struct Node{
	int release;
	int info;
	struct Node *next;
} Node;

typedef struct KeySpace{
	char *key;
	int release;
	Node *node;
	struct KeySpace *ksnext;
}Key;

typedef struct Table{
	int msize;
	int csize;
	Key** ks;
}Table;	


Table *NewTable(Table *, int);

void clearn(Table *);

int scan(int *);

void print(const Table *);

Key *simkey(Table *, char *, Key**);	

int add(Table *, char *, int);

int isFull(Table *);

int idElem(Table *, int);
	
int delete(Table *, char *);

int deleteRes(Table *, char *, int);

//int* find(Table *, char *);

int find1(Table *, Table *, char *);

int findRes(Table *, char *, int);

void myFunc(Table *, Table **, int, int);

#endif
