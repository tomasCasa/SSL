#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//argc cantidad de parametros 
//argv vector de parametros

typedef struct{
	char lexema[100];
	char token[100];
	int linea;
	tablaTokens *sgte;
} tablaTokens;

void agregarTabla(tablaTokens *&frente,tablaTokens *&fin, char[] valLexema, char[] valToken, int valLinea){
	tablaTokens *q = (tablaTokens *) malloc (sizeof(tablaTokens))
	q->lexema = valLexema;
	q->token = valToken;
	q->linea = valLinea;
	q->sgte = NULL;
	if(*frente == NULL)
		*frente = q;
	else
		*fin->sgte = q;
	*fin = q;
}

tablaTokens suprimirTabla (tablaTokens *&frente, tablaTokens *&fin){
	tablaTokens valor;
	tablaTokens *q = *frente;
	
	valor->lexema = q->lexema;
	valor->token = q->token;
	valor->linea = q->linea;
	
	*frente->q->sgte;
	if(*frente == NULL)
		*fin = NULL;
	
	free(q);
	
	return valor;
}
int main(int argc, char *argv[]) {

	
	if(argc == 2){
		//mostrar salida por pantalla
		
	}
	
	if(argc == 3){
		//guardar en un txt la salida
		
	}
}
