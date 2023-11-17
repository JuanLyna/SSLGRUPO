%{
#include <stdlib.h>
#include "y.tab.h"
int errorlexico = 0 ;
%}
id [a-z][a-z0-9]*
asignacion ":="
numero  [0-9]([0-9])*
inicio	("inicio")
fin ("fin")
leer ("leer")
escribir ("escribir")
parentesisabre ("(")
parentesiscierra (")")
coma (",")
puntocoma (";")
operadoraditivo ("+"|"-")
%%
{puntocoma} {return PUNTOCOMA;}
{coma} {return COMA;}
{parentesisabre} {return PARENTESISABRE;}
{parentesiscierra} {return PARENTESISCIERRA;}
{operadoraditivo} {return OPERADORADITIVO;}
{inicio} {return INICIO;}
{fin} {return FIN;}
{leer} {return LEER;}
{escribir} {return ESCRIBIR;}
{numero} {return NUMERO;}
{asignacion} {return ASIGNACION;}
{id}    {return ID;}
.   {printf("Error Léxico: '%s' NO RECONOCIDO \n",yytext);
     errorlexico = 1;}


%%

