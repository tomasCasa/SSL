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


//funciones de verificacion
int esPalabraReservada(char palabra[],char palReser[][30]){
	int i;
	for(i=0;i<20;i++){
		if(!strcmp(palabra,palReser[i])){
			return 1;
		}
	}
	return 0;
}

int esOperador(char operador[],char operadores[][20]){
	int i;
	for(i=0;i<20;i++){
		if(!strcmp(operador,operadores[i])){
			return 1;
		}
	}
	return 0;
}

int esCaracterPuntuacion(char caracter[], char caracteresPuntuacion[][1]){
	int i;
	for(i=0;i<20;i++){
		if(!strcmp(caracter,caracteresPuntuacion[i])){
			return 1;
		}
	}
	return 0;
}

int constanteDecimal(char constante[]){
	if(constante[0]!=48)
		return 1;
	
	return 0;
}

int constanteOctal(char constante[]){
	if(constante[0]==48){
		if(constante[1]!=120||constante[1]!=88){
			return 1;
		}
	}
	return 0;
}

int constanteHexa(char constante[]){
	if(constante[0]==48){
		if(constante[1]==120||constante[1]==88){
			return 1;
		}
	}
	return 0;
}

//es identificador de variable o funcion

//errores de identificador
int errorIdentificador(char identificador[]){
	if(identificador[0]>=48 && identificador[0]<=57)
		return 1;
	
	if(!strcmp("ñ",strstr(identificador,"ñ")));
		return 1;
		
	if(identificador[0]==59)
		return 1;
			
	return 0;
}

//leer txt
void leerTxt(char archivo[],struct tablaTokens **frente,struct tablaTokens **fin){
	FILE *fpuntero;
	char c;
	fpuntero = fopen(archivo, "rt+");
	
	if(fpuntero == NULL) {
			perror("Error al intentar abrir el archivo");
	}

	do{
		c=getc(fpuntero);
		if(c!=' ' && c!='\n')
		 printf( "%c\n",c);
		 
	}while(c != EOF);
	
	fclose(fpuntero);
}

//guardar tabla en txt
void guardarTabla(struct tablaTokens *frente,struct tablaTokens *fin,char archivo[]){
		FILE *f = fopen(archivo,"wt+");
		struct tablaTokens lexemaAGuardar;
		if(f == NULL) {
			perror("Error al intentar abrir el archivo");
			return ;
		}
		fprintf(f,"Lexema");
		fprintf(f,"	");
		fprintf(f,"|"); 
		fprintf(f,"Token");
		fprintf(f,"	");
		fprintf(f,"|");
		fprintf(f,"Linea");
		fprintf(f,"	");
		fprintf(f,"\n");
		fprintf(f,"-------------------------------------------------------\n");
		
		printf("guardando Archivo.... \n");
		
		while(frente!=NULL){
			lexemaAGuardar = suprimirTabla(&frente,&fin);
			fprintf(f,"%s",lexemaAGuardar.lexema);	
			fprintf(f,"	");
			fprintf(f,"|");
			
			fprintf(f,"%s",lexemaAGuardar.token);
			fprintf(f,"	");
			fprintf(f,"|");
			
			fprintf(f,"%d",lexemaAGuardar.linea);
			fprintf(f,"\n");
		}
		fprintf(f,"\0");
		fclose(f);
}

int main(int argc, char *argv[]) {
	/*
	struct tablaTokens *frente = NULL;
	struct tablaTokens *fin = NULL;
	
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
	
	char caracterPuntuacion[10][1];
	strcpy(caracterPuntuacion[0],"{");
	strcpy(caracterPuntuacion[1],"}");
	strcpy(caracterPuntuacion[2],";");
	strcpy(caracterPuntuacion[3],"(");
	strcpy(caracterPuntuacion[4],")");
	strcpy(caracterPuntuacion[5],",");
	strcpy(caracterPuntuacion[6],"[");
	strcpy(caracterPuntuacion[7],"]");
	
	char variables[20][100];
	char funciones[20][100];
	
	
	///////////////leer txt///////////////////////////////
	
	//strcpy(argv[1],"prueba.txt");
	
	leerTxt(argv[1],&frente,&fin);
	
	//////////////////////////////////////////////////////
	
	if(argc == 2){
		//mostrar salida por pantalla
		printf("Lexema");
		printf("	");
		printf("|"); 
		printf("Token");
		printf("	");
		printf("|");
		printf("Linea");
		printf("	");
		printf("\n");
		printf("--------------------------------------------\n");
		struct tablaTokens eliminado;
		int i;
		for(i=0;frente != NULL;i++){
			eliminado = suprimirTabla(&frente,&fin);
			printf("%s",eliminado.lexema);	
			printf("	");
			printf("|");
			
			printf("%s",eliminado.token);
			printf("	");
			printf("|");
			
			printf("%d",eliminado.linea);
			printf("\n");
	
		}
		
	}
	
	if(argc == 3){
		//guardar en un txt la salida
		guardarTabla(frente,fin,argv[2]);
	}
	
	return 0;*/
	
	printf("%s",argv[1]);
}
