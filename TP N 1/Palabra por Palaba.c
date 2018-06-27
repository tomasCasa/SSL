#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv []){
	
	FILE *fpuntero;
	char c;
	fpuntero = fopen("prueba.txt", "rt+");
	
	if(fpuntero == NULL) {
			perror("Error al intentar abrir el archivo");
			return 1;
	}

	do{
		c=getc(fpuntero);
		if(c!=' ' && c!='\n')
		 printf( "%c\n",c);
		 
	}while(c != EOF);
	
	fclose(fpuntero);

	return 0;
}
