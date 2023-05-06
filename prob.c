#include <stdio.h>

int main(){
	FILE *fp = fopen("prob.bin", "w+b");
	char *c = "qwert";
	int a = 25;
	fwrite(c, sizeof(char), 5, fp);
	fseek(fp, 1, SEEK_CUR);
	fwrite(&a, 1, sizeof(int), fp);
	fclose(fp);
	return 0;
}
