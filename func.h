#ifndef _func_h_
#define _func_h_

typedef struct Item {
	char *info;
	int key;
	int ind;
}Item;

typedef struct KeySpace{
	int key;
	Item *info;
}Key;

typedef struct Table{
	int msize;
	int csize;
	Key* ks;
}Table;	

Table *NewTable(Table *table, int size);

void clearn(Table *table);

int scan(int *elem);

void print(const Table *table);

int add(Table *table);

int input_file(Table *table, int key, char *str);

int isFull(Table *table);

int delete(Table *table);

char* find(Table *table);

void myFunc(Table *table, Table **table2);

#endif
