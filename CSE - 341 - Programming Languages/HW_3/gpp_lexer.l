/*
	YAGIZ DONER
	141044062
	CSE - 341 HW3 PART1
*/

%{
#include <stdlib.h>
#include <stdio.h>
void yyerror(char *);
#include "y.tab.h"
%}

COMMENT ";;".*
VALUE [1-9][0-9]*
NOTVALUE [0-9][0-9]+
ID [a-zA-Z][a-zA-Z0-9]*

%%

{VALUE}	{
	yylval = atoi(yytext);
	return IntegerValue;
	}

{NOTVALUE} {printf("Error : A Value cannot start with Zero's\n");}

{COMMENT}  {return Comment;}

"0" {yylval = atoi(yytext);
     return IntegerValue;}

and {return KW_AND;}
or {return KW_OR;}
not {return KW_NOT;}
equal {return KW_EQUAL;}
append {return KW_APPEND;}
concat {return KW_CONCAT;}
set {return KW_SET;}
defvar {return KW_DEFVAR;}
deffun {return KW_DEFFUN;}
if {return KW_IF;}
true {return KW_TRUE;}
false {return KW_FALSE;}      

{ID}	{
	yylval = *yytext - 'a';
	return Id;
	}

"+" {return OP_PLUS;}
"-" {return OP_MINUS;}
"/" {return OP_DIV;}
"*" {return OP_MULT;}
"(" {return OP_OP;}
")" {return OP_CP;}
"'" {return OP_APOS;}

[\n \t]   ;

.        {yyerror("Invalid Character!\n"); return 0;}

%%
int yywrap(void) {
	return 1;
}
