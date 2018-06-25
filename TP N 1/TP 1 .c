#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//argc cantidad de parametros 
//argv vector de parametros

typedef struct tablaTokens{
	char lexema[100];
	char token[100];
	int linea;
	struct tablaTokens *sgte;
}tablaTokens;

void agregarTabla(struct tablaTokens **frente, struct tablaTokens **fin, char valLexema[], char valToken[], int valLinea){
	struct tablaTokens *q =  malloc (sizeof(struct tablaTokens));
	strcpy(q->lexema, valLexema);
	strcpy(q->token, valToken);
	q->linea = valLinea;
	q->sgte = NULL;
	if(*frente == NULL)
		*frente = q;
	else
		(*fin)->sgte = q;
	*fin = q;
}

struct tablaTokens suprimirTabla (struct tablaTokens **frente,struct tablaTokens **fin){
	struct tablaTokens valor;
	struct tablaTokens *q = *frente;
	
	
	strcpy(valor.lexema , q->lexema);
	strcpy(valor.token , q->token);
	valor.linea = q->linea;
	
	(*frente) = q->sgte;
	if(*frente == NULL)
		*fin = NULL;
	
	free(q);
	
	return valor;
}

//definir la cantidad de palabras,operadores y caracteres///////////////////////////
char palReser[20][30];
strcpy(palReser[0],"int");
strcpy(palReser[1],"char");
strcpy(palReser[2],"else");
strcpy(palReser[3],"return");
strcpy(palReser[4],"if");
strcpy(palReser[5],"while");
strcpy(palReser[6],"for");
strcpy(palReser[7],"struct");
strcpy(palReser[8],"break");
strcpy(palReser[9],"case");
strcpy(palReser[10],"do");
strcpy(palReser[11],"double");
strcpy(palReser[12],"long");
strcpy(palReser[13],"void");
strcpy(palReser[14],"unsigned");

char operadores[20][20];
strcpy(operadores[0],"=");
strcpy(operadores[1],"<");
strcpy(operadores[2],">");
strcpy(operadores[3],"<=");
strcpy(operadores[4],">=");
strcpy(operadores[5],"==");
strcpy(operadores[6],"!=");
strcpy(operadores[7],"+");
strcpy(operadores[8],"-");
strcpy(operadores[9],"*");
strcpy(operadores[10],"/");
strcpy(operadores[11],"%");
strcpy(operadores[12],"&&");
strcpy(operadores[13],"!");
strcpy(operadores[14],"||");
strcpy(operadores[15],"++");
strcpy(operadores[16],"--");

char caracterPuntuacion[10];
strcpy(caracterPuntuacion[0],"{");
strcpy(caracterPuntuacion[1],"}");
strcpy(caracterPuntuacion[2],";");
strcpy(caracterPuntuacion[3],"(");
strcpy(caracterPuntuacion[4],")");
strcpy(caracterPuntuacion[5],",");
/////////////////////////////////////////////////////////////////

//funciones de verificacion
int esPalabraReservada(char palabra[]){
	
}

int main(int argc, char *argv[]) {
	
	struct tablaTokens *frente = NULL;
	struct tablaTokens *fin = NULL;
	
	
	
	if(argc == 2){
		//mostrar salida por pantalla
		
	}
	
	if(argc == 3){
		//guardar en un txt la salida
		
	}
}

/*
// PRUEBA de la cola
	char lexema[100];
	char token[100];
	int linea =0;
	int i;
	for(i=0;i<4;i++){
		printf("ingrese Lexema, Token y Linea \n");
		scanf("%s",&lexema);
		scanf("%s",&token);
		scanf("%d",&linea);
		agregarTabla(&frente,&fin,lexema,token,linea);
	}
	
	for(i=0;i<4;i++){
		struct tablaTokens eliminado = suprimirTabla(&frente,&fin);
		printf("Nº %d \n",i);
		printf("\n ");
		
		printf("lexema: %s \n",eliminado.lexema);
		printf("token: %s \n",eliminado.token);
		printf("linea: %d \n",eliminado.linea);
		
		printf("\n ");
		
	
	}
	
*/


