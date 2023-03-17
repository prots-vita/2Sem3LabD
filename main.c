#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "toFile.h"
#include "func.h"

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. File", "4. Delete", "5. Show", "6. Task"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
int dialog(const char *msgs[], int);
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

int (*fptr[])(Table *) = {NULL, Dadd, Dfind, Dfile, Ddelete, Dshow, Dtask};

int main(){
	int SIZE;
	printf("Size: \n");
	if (scan(&SIZE)) return 0;
	int msize = 8, incor;
	Table *table;
	table = NewTable(table, SIZE);
	int input, choose, n, rc;
	while(rc = dialog(msgs, NMsgs))
		if(fptr[rc](table))
			break;
	printf("That's all. Bye!\n");	
	clearn(table);
	return 0;

/*	while (1){
		printf("\n\nPut elem - 1\nDelete elem - 2\nPrint tabl - 3\nFind an elem - 4\nPut elems from file - 5\nmyFunc - 6\n\n");
		if (scan(&choose)) break;
		switch(choose){
			case 1:
				if (Dadd(table)){
					printf("\n");
					print(table);
					clearn(table);
					return 0;
				}
				break;
			case 2:
				if (Ddelete(table)){
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
				toFile(table);
				break;
			case 6:
				myFunc(table, &tableCopy);
				print(tableCopy);
				break;
		}
	}*/
	
}

