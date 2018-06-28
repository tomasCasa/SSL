#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	if(constante[0]=='0'){
		if(constante[1]!='x'&&constante[1]!='X'){
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

int esNumOLet(char ch){
	return ( ('0' <= ch && ch <= '9')||('A'<= ch && ch <='Z')||('a'<=ch && ch<='z')||ch=='_'||ch=='�'||ch=='�');
}

int esPrimerOper(char ch){
	return (ch=='='||ch=='<'||ch=='>'||ch=='!'||ch=='+'||ch=='-'||ch=='&'||ch=='|'||ch=='*'||ch=='/'||ch=='%');
}

int errorIdentificador(char identificador[]){
	if('0' <= identificador[0] && identificador[0] <= '9' )
		return 1;
	
	//ver si una cadena tiene �
	int i;
	for(i=0;identificador[i]!='\0';i++){
		if(identificador[i]=='�' || identificador[i]=='�')
			return 1;
	}
	
	if(identificador[0]==';')
		return 1;
			
	return 0;
}

int main(){
	
	char carPun[9]={"{};(),[]"};
	
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
	
    char ch, buffer[15],bufferOper[2];
    FILE *fp;
    int i=0,j=0;
    fp = fopen("prueba.txt","r");
    
    if(fp == NULL){
        printf("error al abrir el archivo\n");
    }
    
    while((ch = fgetc(fp)) != EOF){
           
           //es un numero o una letra
           if(esNumOLet(ch)){
               buffer[j] = ch;
               j++;
           }
           else if((!esNumOLet(ch)) && (j != 0)){
                   buffer[j] = '\0';
                   j = 0;
                                      
                   if(esPalabraReservada(buffer,palReser)){
                       printf("%s es palabra reservada\n", buffer);
				   }
                   else{
                   		if(constanteHexa(buffer)){
                   			printf("%s es una constante Hexadecimal\n", buffer);
						}
						if(constanteOctal(buffer)){
							printf("%s es una constante Octal\n", buffer);
						}
						if(constanteDecimal(buffer)){
							printf("%s es una Constante Decimal\n", buffer);
						}
						if(!constanteHexa(buffer)&&!constanteOctal(buffer)&&!constanteDecimal(buffer)){
							if(errorIdentificador(buffer)){
	                   			printf("%s es un error\n", buffer);
							}
							else{
								//ver si es un identificador de funcion o variable
	                       		printf("%s es indentificador\n", buffer);
							}
						}
				   }
           }
           
           if(esPrimerOper(ch)){
           		bufferOper[i]=ch;
           		i++;
		   }
           else if((!esPrimerOper(ch) )&& (i != 0)){
           		bufferOper[i] = '\0';
                i = 0;
                
                if(esOperador(bufferOper,operadores)){
                	printf("%s es Operador\n", bufferOper);
				}
		   }	
           	
           if(esCaracterPuntuacion(ch,carPun)){
		   		printf("%c es caracter de Puntuacion\n",ch);
		   }
		   
		   
    }
    
    fclose(fp);
    
    return 0;
}
