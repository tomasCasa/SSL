#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

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

void agregarTablaChar(struct tablaTokens **frente, struct tablaTokens **fin, char valLexema, char valToken[], int valLinea){
	struct tablaTokens *q =  malloc (sizeof(struct tablaTokens));
	char lex[100] = " ";
	lex[0]=valLexema;
	strcpy(q->lexema, lex);
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

int esPalabraReservada(char palabra[],char palReser[][30]){
	int i;
	for(i=0;i<20;i++){
		if(!strcmp(palabra,palReser[i])){
			return 1;
		}
	}
	return 0;
}

//funciones de validacion
int esOperador(char operador[],char operadores[][20]){
	int i;
	for(i=0;i<20;i++){
		if(!strcmp(operador,operadores[i])){
			return 1;
		}
	}
	return 0;
}

int esCaracterPuntuacion(char caracter, char carPun[]){
	int i;
	for(i=0;i<9;++i){
		if(caracter==carPun[i]){
			return 1;
		}
	}
	return 0;
}

int constanteDecimal(char constante[]){
	if(constante[0]=='0')
		return 0;

	int i;
	for(i=0;constante[i]!='\0';i++){
		if(constante[i]<'0'||constante[i]>'9')
			return 0;
	}
	
	return 1;
}

int constanteOctal(char constante[]){
	int i;
	if(constante[0]=='0'){
		if(constante[1]!='x'&&constante[1]!='X'){
			for(i=1;constante[i]!='\0';i++){
				if(constante[i]<'0'||constante[i]>'7'){
					return 0;
				}
			}
			return 1;
		}
	}
	return 0;
}

int constanteHexa(char constante[]){
	int i;
	if(constante[2]=='\0'){
		return 0;
	}
	if(constante[0]=='0'){
		if(constante[1]=='x'||constante[1]=='X'){
			for(i=2;constante[i]!='\0';i++){
				if((constante[i]<'0'||constante[i]>'9')&&(constante[i]<'a'||constante[i]>'f')&&(constante[i]<'A'||constante[i]>'F')){
					return 0;
				}
			}
			return 1;
		}
		else{
			
		}
	}
	return 0;
}

int esNumOLet(char ch){
	return ( ('0' <= ch && ch <= '9')||('A'<= ch && ch <='Z')||('a'<=ch && ch<='z')||ch=='_'||ch=='ñ'||ch=='Ñ');
}

int esPrimerOper(char ch){
	return (ch=='='||ch=='<'||ch=='>'||ch=='!'||ch=='+'||ch=='-'||ch=='&'||ch=='|'||ch=='*'||ch=='/'||ch=='%');
}

int errorIdentificador(char identificador[]){
	if('0' <= identificador[0] && identificador[0] <= '9' )
		return 1;
	
	//ver si una cadena tiene ñ
	int i;
	for(i=0;identificador[i]!='\0';i++){
		if(identificador[i]=='Ñ' || identificador[i]=='ñ')
			return 1;
	}
	
	if(identificador[0]==';')
		return 1;
			
	return 0;
}


//funciones para los vectores de funcion y variables
void agregarIdentificador(char nuevo[],char identificadores[][100]){
	int i;
	for(i=0;i<20;i++){
		if(identificadores[i][0]==' ')
			strcpy(identificadores[i],nuevo);
	}
}

int esViejoIden(char viejo[],char identificadores[][100]){
	int i;
	for(i=0;i<20;i++){
		if(!strcmp(viejo,identificadores[i]))
			return 1;
	}
	return 0;
}

int inicializar(char identificadores[][100]){
	int i;
	for(i=0;i<20;i++){
		identificadores[i][0]=' ';
	}
}

//leer txt
void leerTxt(char archivo[],struct tablaTokens **frente,struct tablaTokens **fin){

	char variables[20][100];
	char funciones[20][100];
	inicializar(variables);
	inicializar(funciones);
	
	FILE *fnuevo=fopen(archivo,"rt");
	int flag=0;
	
	char carPun[9]={"{};(),"};
	
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
	strcpy(palReser[15],"include");
	
	
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
	strcpy(operadores[17],"[");
	strcpy(operadores[18],"]");
	strcpy(operadores[19],".");
	
	
	char ch, buffer[100],bufferOper[2];
    FILE *fp;
    int i=0,j=0;
    int linea=1;
    fp = fopen(archivo,"rt");
    
    if(fp == NULL){
        printf("error al abrir el archivo\n");
    }
    
    while((ch = fgetc(fp)) != EOF){
    		if(ch=='\n')
    			linea++;
           
           //es un numero o una letra
           if(esNumOLet(ch)){
               buffer[j] = ch;
               j++;
           }
           else if((!esNumOLet(ch)) && (j != 0)){
                   buffer[j] = '\0';
                   j = 0;         
                   if(esPalabraReservada(buffer,palReser)){
                       agregarTabla(frente,fin,buffer,"palabraReservada",linea);
				   }
                   else{
                   		if(constanteHexa(buffer)){
                   			agregarTabla(frente,fin,buffer,"constanteHexadecimal",linea);
						}
						else if(constanteOctal(buffer)){
							agregarTabla(frente,fin,buffer,"constanteOctal",linea);
						}
						else if(constanteDecimal(buffer)){
							agregarTabla(frente,fin,buffer,"constanteDecimal",linea);
						}
						else{
							if(errorIdentificador(buffer)){
	                   			agregarTabla(frente,fin,buffer,"errorIdentificador",linea);
							}
							else{
								if(esViejoIden(buffer,variables)){
									agregarTabla(frente,fin,buffer,"identificador	",linea);
								}
								else if(esViejoIden(buffer,funciones)){
									agregarTabla(frente,fin,buffer,"identificadorFuncion",linea);
								}
								else{
									flag=0;
		                       		fseek(fnuevo,ftell(fp)-sizeof(ch),SEEK_SET);
		                       		while((ch = fgetc(fnuevo)) != EOF&&(flag==0)){
		                       				if(esPrimerOper(ch)||ch==','||ch==';'||ch==')') {
		                       					agregarTabla(frente,fin,buffer,"identificador	",linea);
		                       					agregarIdentificador(buffer,variables);
		                       					flag=1;
											}
		                       					
		                       				if(ch=='('){
		                       					agregarTabla(frente,fin,buffer,"identificadorFuncion",linea);
		                       					agregarIdentificador(buffer,funciones);
		                       					flag =1;
											}
										
									}
									if(ch==EOF)
		                       			agregarTabla(frente,fin,buffer,"errorIdentificador",linea);
		                       					
										
									fseek(fp,ftell(fp)-sizeof(ch),SEEK_SET);
								}
								
							}
						}
				   }
				   strcpy(buffer," ");
           }
           
           if(esPrimerOper(ch)){
           		bufferOper[i]=ch;
           		i++;
		   }
           else if((!esPrimerOper(ch) )&& (i != 0)){
           		bufferOper[i] = '\0';
                i = 0;
                
                if(esOperador(bufferOper,operadores)){
                	
                	agregarTabla(frente,fin,bufferOper,"Operador	",linea);
				}
				strcpy(bufferOper," ");
		   }	
           	
           if(esCaracterPuntuacion(ch,carPun)){
		   		agregarTablaChar(frente,fin,ch,"caracterPuntuacion",linea);
		   }
		   
    }
    //es un numero o una letra
           if(esNumOLet(ch)){
               buffer[j] = ch;
               j++;
           }
           else if((!esNumOLet(ch)) && (j != 0)){
                   buffer[j] = '\0';
                   j = 0;         
                   if(esPalabraReservada(buffer,palReser)){
                       agregarTabla(frente,fin,buffer,"palabraReservada",linea);
				   }
                   else{
                   		if(constanteHexa(buffer)){
                   			agregarTabla(frente,fin,buffer,"constanteHexadecimal",linea);
						}
						else if(constanteOctal(buffer)){
							agregarTabla(frente,fin,buffer,"constanteOctal",linea);
						}
						else if(constanteDecimal(buffer)){
							agregarTabla(frente,fin,buffer,"constanteDecimal",linea);
						}
						else{
							if(errorIdentificador(buffer)){
	                   			agregarTabla(frente,fin,buffer,"errorIdentificador",linea);
							}
							else{
								if(esViejoIden(buffer,variables)){
									agregarTabla(frente,fin,buffer,"identificador	",linea);
								}
								else if(esViejoIden(buffer,funciones)){
									agregarTabla(frente,fin,buffer,"identificadorFuncion",linea);
								}
								else{
									flag=0;
		                       		fseek(fnuevo,ftell(fp)-sizeof(ch),SEEK_SET);
		                       		while((ch = fgetc(fnuevo)) != EOF&&(flag==0)){
		                       				if(esPrimerOper(ch)||ch==','||ch==';'||ch==')') {
		                       					agregarTabla(frente,fin,buffer,"identificador	",linea);
		                       					agregarIdentificador(buffer,variables);
		                       					flag=1;
											}
		                       					
		                       				if(ch=='('){
		                       					agregarTabla(frente,fin,buffer,"identificadorFuncion",linea);
		                       					agregarIdentificador(buffer,funciones);
		                       					flag =1;
											}
										
									}
									if(ch==EOF)
		                       			agregarTabla(frente,fin,buffer,"errorIdentificador",linea);
		                       					
										
									fseek(fp,ftell(fp)-sizeof(ch),SEEK_SET);
								}
								
							}
						}
				   }
				   strcpy(buffer," ");
           }
           
           if(esPrimerOper(ch)){
           		bufferOper[i]=ch;
           		i++;
		   }
           else if((!esPrimerOper(ch) )&& (i != 0)){
           		bufferOper[i] = '\0';
                i = 0;
                
                if(esOperador(bufferOper,operadores)){
                	
                	agregarTabla(frente,fin,bufferOper,"Operador	",linea);
				}
				strcpy(bufferOper," ");
		   }
    fclose(fp);
    

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
	
	struct tablaTokens *frente = NULL;
	struct tablaTokens *fin = NULL;
	
	
	///////////////leer txt///////////////////////////////
	
	
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
	
	return 0;
}
