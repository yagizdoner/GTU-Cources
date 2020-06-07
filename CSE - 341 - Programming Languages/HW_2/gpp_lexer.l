/* 
   CSE 341 - HW2 - PART 1
   Author : Yağız DÖNER 
   Number : 141044062
*/

%{

%}

COMMENT ";;".*
VALUE    [1-9][0-9]*
NOTVALUE [0-9][0-9]+
ID       [a-zA-Z][a-zA-Z0-9]*


%%

"0" {printf("VALUE\n");}
{VALUE}+ {printf("VALUE\n");}
{NOTVALUE} {printf("Error : A Value cannot start with Zero's\n");}
{COMMENT} {printf("COMMENT\n");}

and {printf("KW_AND\n");}
or {printf("KW_OR\n");}
not {printf("KW_NOT\n");}
equal {printf("KW_EQUAL\n");}
less {printf("KW_LESS\n");}
nil {printf("KW_NIL\n");}
list {printf("KW_LIST\n");}
append {printf("KW_APPEND\n");}
concat {printf("KW_CONCAT\n");}
set {printf("KW_SET\n");}
deffun {printf("KW_DEFFUN\n");}
for {printf("KW_FOR\n");}
if {printf("KW_IF\n");}
exit {printf("KW_EXIT\n");}
load {printf("KW_LOAD\n");}
disp {printf("KW_DISP\n");}
true {printf("KW_TRUE\n");}
false {printf("KW_FALSE\n");}       

{ID} {printf( "IDENTIFIER\n");}

"+" {printf("OP_PLUS\n");}
"-" {printf("OP_MINUS\n");}
"/" {printf("OP_DIV\n");}
"*" {printf("OP_MULT\n");}
"(" {printf("OP_OP\n");}
")" {printf("OP_CP\n");}
"**" {printf("OP_DBLMULT\n");}
"\"" {printf("OP_OC\n");}
"," {printf("OP_COMMA\n");}

[ \t\n]+   /* Throw Whitespaces */

. {printf( "Unrecognized character: %s\n", yytext );}

%%
int yywrap(){} 
int main( int argc, char **argv ){
	if ( argc > 1 )
		yyin = fopen( argv[1], "r" );
	else
		yyin = stdin;

	yylex();
}
