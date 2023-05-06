#include <stdio.h>
#include <stdlib.h>
#include "toFile.h"
#include "func.h"
#include "dialogue.h"

int main(){
	int cho, SIZE;
	FILE *fp;
	Table *table;
	printf("new or return(1/2): ");
	scanf("%d", &cho);
	if (cho==1){
		printf("Size: \n");
		if (scan(&SIZE)) return 0;
		table = NewTable(table, SIZE);
		table->iofile = fopen("info.bin", "w+b");
	} else {
		fp = fopen("key.bin", "r+b");
		fread(&SIZE, sizeof(int), 1, fp);
//		printf("%d", SIZE);
		table = NewTable(table, SIZE);
		if (-1 == rename ("info.bin","info2.bin")){
			printf ("Error rename\n");
		}
		table->iofile = fopen(table->file, "w+b");
		returnTable(table, fp, "info2.bin");
		fclose(fp);
	}
	const char *msgs[] = {"0. Return", "1. Add", "2. Find", "3. Find release", "4. File", "5. Delete", "6. Delete release", "7. Show"};
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int (*fptr[])(Table *) = {NULL, Dadd, Dfind1, DfindRes, Dfile, Ddelete, DdeleteRes, Dshow};
	int msize = 8, incor;
	int input, choose, n, rc;
	while(rc = dialog(msgs, NMsgs))
		if(fptr[rc](table))
			break;
	printf("That's all. Bye!\n");
	fclose(table->iofile);
	clearn(table);
	return 0;
}
