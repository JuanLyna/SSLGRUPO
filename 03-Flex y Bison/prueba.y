%{ 			
 #include <stdio.h>  
 int yylex() ;
 void yyerror(char *s);
 extern int errorlexico; 
%}
%union{

int entero ;

}

%token PUNTOCOMA COMA PARENTESISABRE PARENTESISCIERRA OPERADORADITIVO INICIO FIN LEER ESCRIBIR ASIGNACION DESCONOCIDO ID
%type <entero> expresion termino
%token <entero>  NUMERO 


%%
programa : INICIO listasentencias  FIN 
	 ;	 
listasentencias: sentencia listasentencias
		| /*vacio*/
		;


sentencia : ID ASIGNACION expresion PUNTOCOMA
	   | LEER PARENTESISABRE listaidentificadores PARENTESISCIERRA PUNTOCOMA
	   | ESCRIBIR PARENTESISABRE listaexpresiones PARENTESISCIERRA PUNTOCOMA 
	   ;

listaidentificadores: ID 
 		      | listaidentificadores COMA ID
		      ;
listaexpresiones: expresion 
		 | listaexpresiones COMA expresion
		 ;

expresion : termino  
	  | expresion OPERADORADITIVO termino
 	  {
 	  int res=$$;
 	  if(OPERADORADITIVO == '+')
 	  {
 	  res=$1+$3 ;
 	  }else {  res=$1-$3 ;}

 	  int primernum = $1 ; 
 	  int segundonum = $3 ;
 	  
 	  if(primernum!=segundonum)
 	  {
 	  printf("Los nùmeros son iguales");
 	  }}
 	  ;
termino : ID
 	| NUMERO
	| PARENTESISABRE expresion PARENTESISCIERRA
 	;

%%


int main()
{
int codigo = yyparse() ;
if(codigo==0){
printf("El código no presenta errores sintacticos \n"); 
}else printf("El codigo presenta errores sintacticos\n") ;
if(errorlexico==0){
printf("El código no presenta errores Lèxico\n"); 
}else printf("El codigo presenta errores Lèxicos\n") ;
return 0 ; 
}
void yyerror (char *s)
{
 printf ( "%s\n", s); 
}
 int yywrap(void)
{
return 1 ; 
}
 
