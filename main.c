#include <stdio.h>
#include <stdlib.h>
#include "toFile.h"
#include "func.h"
#include "dialogue.h"

int main(){
	int SIZE;
	printf("Size: \n");
	if (scan(&SIZE)) return 0;
	const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Find release", "4. File", "5. Delete", "6. Delete release", "7. Show"};
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Table *) = {NULL, Dadd, Dfind1, DfindRes, Dfile, Ddelete, DdeleteRes, Dshow};
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
}
