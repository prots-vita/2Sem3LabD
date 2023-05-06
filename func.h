#ifndef _func_h_
#define _func_h_

typedef struct Node{
	int release;
	int offset;
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
	FILE *iofile;
	char *file;
	int n;
}Table;	


Table *NewTable(Table *, int);

void clearn(Table *);

void returnTable(Table *, FILE *, char *);

int saveTable(Table *);

int readInfo(FILE *, int);

void GoAndBack(FILE **, int, int, int);

int scan(int *);

void print(Table *, FILE *);

Key *simkey(Table *, char *, Key**);	

void copecode(Table *, FILE *, FILE *);

int add(Table *, char *, int, int, int);

int isFull(Table *);

int idElem(Table *, int);
	
int delete(Table *, char *);

int deleteRes(Table *, char *, int);

//int* find(Table *, char *);

int find1(Table *, Table *, char *);

int findRes(Table *, char *, int);

void myFunc(Table *, Table **, int, int);

#endif
