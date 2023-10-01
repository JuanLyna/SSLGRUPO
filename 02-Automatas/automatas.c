#include "automatas.h"

int main()
{
   int opcion = -1;
   while(opcion !=3){
	   printf("\n\nElija una de las siguientes opciones \n");
	   printf("----------------------------------------\n");
	   printf("1) Para utilizar una cadena de caracteres para ser reconocidas por los distintos automatas numericos\n");
	   printf("2) Para escribir una expresion matematica a resolver \n");
	   printf("3) Para salir de este menu\n\n");
	   printf("Opcion: ");
	   scanf("%d", &opcion);
	   printf("\n\n");
	   if(opcion == 1){
		   realizarChequeoCadena();
	   }else if(opcion == 2){
		   calcularExpresionMatematica();
	   }
   }
    return 0;
}

void realizarChequeoCadena(){
	char cadena[100];
    printf("Ingrese una cadena: ");
	fflush(stdout);
    scanf( "%s", cadena) ;
	char *grupoPalabra =   strtok(cadena,"$") ;


	while (grupoPalabra!=NULL)
	{
			printf("La primera cadena a chquear es :%s \n" ,grupoPalabra );
		 if(distinguirConstante(grupoPalabra)==AUTOMATA_OCTAL)
		 {
			revisarOctal(grupoPalabra) ;
			printf("Los errores lexicos de la cadena octal %s han sido %d \n" , grupoPalabra, erroresLexicos) ;

		 } else if (distinguirConstante(grupoPalabra)==AUTOMATA_DECIMAL)
		 {
			revisarDecimal(grupoPalabra) ;
			printf("Los errores lexicos de la cadena decimal %s han sido %d \n" , grupoPalabra, erroresLexicos) ;
		 } else if (distinguirConstante(grupoPalabra)==AUTOMATA_HEXADECIMAL)
		 {
			 revisarHexa(grupoPalabra) ;
			printf("Los errores lexicos de la cadena hexadecimal %s  han sido %d \n" , grupoPalabra, erroresLexicos) ;
		 }

		if(erroresLexicos==0)
			{
				verificarPalabra(grupoPalabra) ;

			}  else printf("no es posible analizar la cadena porque no pertenece al alfabeto \n") ;


		grupoPalabra = strtok(NULL , "$") ;

	}

	printf("Cantidad de palabras correctas Decimales %d \n" , cantPalabrasDecimales) ;
	printf("Cantidad de palabras correctas  Octales %d \n" , cantPalabrasOctales) ;

	printf("Cantidad de palabras correctas Hexadecimales %d \n" , cantPalabrasHexadecimales) ;
}


//PUNTO 1
int revisarHexa(char *cadena)
{
      erroresLexicos  = 0 ; 
    for(int i = 0 ; cadena[i] ; i++)
    {
        if(cadena[i] != 'A' && cadena[i] != 'B'  && cadena[i] != 'C' && cadena[i] != 'D' && cadena[i] != 'E' && cadena[i] != 'F'  &&  isdigit(cadena[i])==0 && cadena[i] != 'x') // si alguno da true es que es un hexa 
    {
       erroresLexicos ++ ;  
    }
    } 
   
	
   return erroresLexicos  ; 
}

int revisarOctal(char *cadena)
{
      erroresLexicos  = 0 ; 
    
   for (int i = 0; cadena[i]; i++)
   {
     if(cadena[i] != '0'&&cadena[i] != '1'&&cadena[i] != '2'&&cadena[i] != '3'&&cadena[i] != '4'&&cadena[i] != '5'&&cadena[i] != '6'&&cadena[i] != '7') // si alguno da true es que es un hexa 
    {
       erroresLexicos ++ ;  
    } 
   }
   
   return erroresLexicos ; 
}
int revisarDecimal(char *cadena) 
{   
  erroresLexicos = 0; 
  for (int i = 0;cadena[i]; i++)
  {
	
    if(isdigit(cadena[i])==0 && cadena[i] != '-'&&cadena[i] != '+')
    {
		
      erroresLexicos  ++ ; 
    }
  }
  
 
  return erroresLexicos  ;
}
int estadoLetraAPosicion(char estado) ; 



int distinguirConstante(char* palabra){
	int tipoAutomata = -1;
	if(palabra[0] == '0'){
		if(palabra[1] == 'x'){
			tipoAutomata = AUTOMATA_HEXADECIMAL;
		}
		else{
			tipoAutomata = AUTOMATA_OCTAL;
		}
	}
	else{
		tipoAutomata = AUTOMATA_DECIMAL;
	}
	
	
	return tipoAutomata;
}


int verificarPalabra(char* palabra)
{
	int palabraCorrecta = -1;
	
	 
	switch (distinguirConstante(palabra))
	{
		case AUTOMATA_OCTAL:
			
			palabraCorrecta = verificarPalabraOctal(palabra);
			
			break;
		case AUTOMATA_DECIMAL:
			
			palabraCorrecta = verificarPalabraDecimal(palabra);
			break;
		case AUTOMATA_HEXADECIMAL:
			
			palabraCorrecta = verificarPalabraHexadecimal(palabra);
			break;
		default:
			palabraCorrecta = -1;
	}
}

int verificarPalabraOctal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizOctal[4][2] = 
	{  // 0   0-7
		{'B','D'} , //A-
		{'C','C' }, //B
		{'C','C'} , //C+
		{'D','D'}  //D
	};
	
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizOctal[estadoActual][transformarACol(caracterActual)]);
	}
	
	if(estadoActual == ESTADO_ACEPTACION_OCTAL){
		verificaPalabra = 1;
		cantPalabrasOctales++;
	}
	return verificaPalabra;
	
}

int verificarPalabraDecimal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizDecimal[4][4] = 
	{// [0] [1-9]  +   - 
		{'D','C','B','B',} , //A-
		{'C' ,'C','D','D'},  //B
		{'C','C','D','D'} ,  //C+
		{'D','D','D','D'} // D
	};

	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizDecimal[estadoActual][transformarACol(caracterActual)]);
	}
	if(estadoActual == ESTADO_ACEPTACION_DECIMAL){
		verificaPalabra = 1;
		cantPalabrasDecimales++;
	} else 
	return verificaPalabra;
}

int verificarPalabraHexadecimal(char* palabra){
	int estadoActual = 0;
	int verificaPalabra = 0;
	const int matrizHexadecimal[5][3] = 
	{//   0  1-F  X
		{'B','E','E'} , //A-
		{'E','E','C'}, //B
		{'E','D','E'} ,  //C
		{'E','D','E'} , //D+
		{'E','E','E'} //E
	};
	 
	for(int i=0; i<strlen(palabra); i++){
		char caracterActual = palabra[i];
		estadoActual = estadoLetraAPosicion(matrizHexadecimal[estadoActual][transformarACol(caracterActual)]);
	}
	if(estadoActual == ESTADO_ACEPTACION_HEXADECIMAL){
		verificaPalabra = 1;
		cantPalabrasHexadecimales++;
	}
	return verificaPalabra;
}

int estadoLetraAPosicion(char estado){
	int numCol = -1;
	switch(estado){
		case 'A':
			numCol = 0;
			break;
		case 'B':
			numCol = 1;
			break;
		case 'C':
			numCol = 2;
			break;
		case 'D':
			numCol = 3;
			break;
		case 'E':
			numCol = 4;
			break;
		case 'F':
			numCol = 5;
			break;
		default:
			numCol = -1;
			break;
	}
	return numCol;
}

int transformarACol(char c){
	int col = 0;
	int valorNum = valorNumerico(c);
	if(valorNum== 0){
		col = 0;
	}
	else if (valorNum > 0){
		col = 1;
	}
	else{
		col = 2;
	}
	return col;
}


//PUNTO 2
int valorNumerico(char caracter)
{
	 int numero = -1;
	switch (caracter)
{
		 case '0':
			numero = 0;
			 break;
		 case '1':
		 numero = 1;
		 break;
		 case '2':
		numero = 2;
		break;
		 case '3':
		 numero = 3;
		break;
		case '4':
		 numero = 4;
		break;
		case '5':
			numero = 5;
		 break;
		 case '6':
			 numero = 6;
			 break;
		 case '7':
			numero = 7;
			break;
		 case '8':
			 numero = 8;
		 break;
		 case '9':
		numero = 9;
			 break;
		 case 'A':
		numero = 10;
		 break;
		case 'B':
		numero = 11;
		 break;
	 	 case 'C':
 		 numero = 12;
		 break;
		 case 'D':
		 numero = 13;
		break;
		 case 'E':
		 numero = 14;
		break;
		 case 'F':
		numero = 15;
	 break;
		 }
	return numero;
}


//PUNTO 3
struct PilaNumerica {
    int ultPos;
    float items[100];
};

struct PilaCaracter
{
  int ultPos;
    char items[100];
};


void inicializarPila(struct PilaNumerica* pila) {
    pila->ultPos = -1;
}
void inicializarPilaCaracteres(struct PilaCaracter* pila) {
    pila->ultPos = -1;
}

int isEmpty(struct PilaNumerica* pila) {
    return pila->ultPos == -1;
}
int isEmptyCaracteres(struct PilaCaracter* pila) {
    return pila->ultPos == -1;
}

void push(struct PilaNumerica* pila, float item) {
    
   pila->ultPos=pila->ultPos+1 ;
    pila->items[pila->ultPos] = item;
}
void pushCaracteres(struct PilaCaracter* pila, float item) {
    pila->ultPos=pila->ultPos+1 ;
    pila->items[pila->ultPos] = item;
}


float pop(struct PilaNumerica* pila) {
    if (!isEmpty(pila)) {
         float num = pila->items[pila->ultPos] ;
        pila->ultPos = pila->ultPos-1 ;
        return num;
    }
    return -1;
}
char popCaracteres(struct PilaCaracter* pila) {
    if (!isEmptyCaracteres(pila)) {
        char car = pila->items[pila->ultPos] ;
        pila->ultPos = pila->ultPos-1 ;
        return car;
    }
    return -1;
}

float realizarOperacion(float num1, char operador, float num2) {
    switch (operador) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0) {
                return num1 / num2;
            }
        default:
            printf("Operador no válido: %c\n", operador);
           return -1  ;
    }
}


float evaluarExpresion(char* expresion) {
    struct PilaNumerica pilaNum;
    struct PilaCaracter pilaOp;
    inicializarPila(&pilaNum);
    inicializarPilaCaracteres(&pilaOp);

    int i = 0;
    while (expresion[i] != '\0') {
         float numero = valorNumerico(expresion[i]) ;

        if (numero>= 0 && numero <=9 ) {


            push(&pilaNum, numero);
        } else if (expresion[i] == '+' || expresion[i] == '-') {
            if(!isEmptyCaracteres(&pilaOp) &&
                   (pilaOp.items[pilaOp.ultPos] == '+' || pilaOp.items[pilaOp.ultPos] == '-' ||
                    pilaOp.items[pilaOp.ultPos] == '*' || pilaOp.items[pilaOp.ultPos] == '/'))
            {
                float num2 = pop(&pilaNum);
                float num1 = pop(&pilaNum);
                char operador = popCaracteres(&pilaOp);
                float resultado = realizarOperacion(num1, operador, num2);
                push(&pilaNum, resultado);
            }
            pushCaracteres(&pilaOp, expresion[i]);
        } else if (expresion[i] == '*' || expresion[i] == '/') {
           if(!isEmptyCaracteres(&pilaOp) &&
                   (pilaOp.items[pilaOp.ultPos] == '*' || pilaOp.items[pilaOp.ultPos] == '/')) {
                float num2 = pop(&pilaNum);
                float num1 = pop(&pilaNum);
                char operador = popCaracteres(&pilaOp);
                float resultado = realizarOperacion(num1, operador, num2);
                push(&pilaNum, resultado);
            }
            pushCaracteres(&pilaOp, expresion[i]);
        }
        i++;
    }

    //Realizar opereaciones restantes con resultados parciales que se fueron dando
    while (!isEmptyCaracteres(&pilaOp)) {
        float num2 = pop(&pilaNum);
        float num1 = pop(&pilaNum);
        char operador = popCaracteres(&pilaOp);
        float resultado = realizarOperacion(num1, operador, num2);
        push(&pilaNum, resultado);
    }

    return pilaNum.items[pilaNum.ultPos];
}

void calcularExpresionMatematica(){
    char cadena[100];
    printf("Ingrese una expresion matematica: ");
    scanf("%s", cadena);

    float resultado = evaluarExpresion(cadena);

    printf("Resultado: %.2f\n", resultado);
}


