#include <stdio.h>
#include <string.h> // de acá sacamos las funciones strtok y strlen
#include <ctype.h> // de acá sacamos la función isdigit


#define AUTOMATA_OCTAL 1
#define AUTOMATA_DECIMAL 2
#define AUTOMATA_HEXADECIMAL 3

int cantPalabrasOctales = 0  ;
int cantPalabrasHexadecimales = 0  ;
int cantPalabrasDecimales = 0  ;
int erroresLexicos=0 ;

#define ESTADO_ACEPTACION_OCTAL 2
#define ESTADO_ACEPTACION_DECIMAL 2
#define ESTADO_ACEPTACION_HEXADECIMAL 3

int verificarPalabraOctal(char *palabra);
int verificarPalabraHexadecimal(char *palabra);
int verificarPalabraDecimal(char *palabra);
int valorNumerico (char c );
int transformarACol(char c);
int verificarPalabra(char* palabra);
int revisarHexa(char *cadena);
int revisarDecimal(char *cadena);
int revisarOctal(char *cadena);
int distinguirConstante(char* palabra);
void realizarChequeoCadena();
void calcularExpresionMatematica();
