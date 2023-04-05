#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(){
	char *s;
	s = readline("");
	int u = 95, in, index, size;
	printf("SIZE: ");
	scanf("%d", &size);
	index = (s[0]-' ')%size;
	printf("%d  %d  %d", s[0]-' ', in, index);
	return 0;
}
