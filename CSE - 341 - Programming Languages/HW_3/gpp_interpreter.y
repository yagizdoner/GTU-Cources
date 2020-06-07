/*
	YAGIZ DONER
	141044062
	CSE - 341 HW3 PART1
*/

%token IntegerValue Id Comment
%token KW_TRUE KW_FALSE
%left OP_PLUS OP_MINUS 
%left OP_MULT OP_DIV
%left KW_AND KW_OR KW_NOT KW_EQUAL KW_APPEND KW_CONCAT
%left KW_SET KW_DEFFUN KW_IF KW_DEFVAR
%left OP_OP OP_APOS
%right OP_CP

%{ 
    #include <stdio.h>
    #include <string.h>
    void yyerror(char *); 
    int yylex(void); 
    int sym[26]; 
    char arr[100];
    char arr1[100];
    char arr2[200];
    char buf[201];

%} 
%% 
START:
	START INPUT
 	|
	;

INPUT: 
	Comment { printf("Syntax OK.\nResult: Comment\n");}        
	|EXPI   { printf("Syntax OK.\nResult: %d\n", $1); }   
	|EXPB  { printf("Syntax OK.\nResult: %d\n", $1); } 
	|EXPLISTI  { printf("Syntax OK.\nResult: '(%s)\n", arr2); sprintf(arr2,"%s",""); }        
	; 

EXPI:   
	OP_OP KW_SET Id EXPI OP_CP            { sym[$3] = $4; $$=$4;} 
	| OP_OP KW_DEFVAR Id EXPI OP_CP       { sym[$3] = $4; $$=$4;}
	| OP_OP KW_DEFFUN Id IDLIST EXPLISTI OP_CP  {$$ = 0;}  
	| OP_OP KW_IF EXPB EXPLISTI OP_CP     { if($3 == 0){$$=0;}else{printf("%s",arr2);}}
	| OP_OP KW_IF EXPB EXPLISTI EXPLISTI OP_CP  {if($3 == 1){$$=$4;}else{$$=$5;}}
	| OP_OP OP_PLUS EXPI EXPI OP_CP      { $$ = $3 + $4; } 
    | OP_OP OP_MINUS EXPI EXPI OP_CP      { $$ = $3 - $4; } 
    | OP_OP OP_MULT EXPI EXPI OP_CP       { $$ = $3 * $4; } 
    | OP_OP OP_DIV EXPI EXPI OP_CP        { $$ = $3 / $4; }
	| Id                                  { $$ = sym[$1]; } 
	| IntegerValue    
	| OP_OP Id EXPLISTI OP_CP    
        ; 

EXPB:
	OP_OP KW_AND EXPB EXPB OP_CP          {$$ = $3 && $4;}
	|OP_OP KW_OR EXPB EXPB OP_CP	      {$$ = $3 || $4;}
	|OP_OP KW_NOT EXPB OP_CP	      {$$ = !$3;}
	|OP_OP KW_EQUAL EXPB EXPB OP_CP       {if($3 == $4){$$=1;}else{$$=0;}}
	| OP_OP KW_EQUAL EXPI EXPI OP_CP      {if($3 == $4){$$=1;}else{$$=0;}}
	| BinaryValue
	;

EXPLISTI:
	OP_OP KW_CONCAT EXPLISTI EXPLISTI OP_CP 
	|OP_OP KW_APPEND EXPI EXPLISTI OP_CP	{sprintf(buf,"%d ",$3);strcat(buf,arr2);sprintf(arr2,"%s",buf);}
	|LISTVALUE
	|
	;

LISTVALUE:
	OP_APOS OP_OP VALUES OP_CP {strcat(arr2,arr);}     
	|OP_APOS OP_OP OP_CP	 
	;

VALUES:
	VALUES IntegerValue {sprintf(arr1,"%d ",$2);strcat(arr,arr1);}
	|IntegerValue {sprintf(arr,"%d ",$1);}
	;

IDLIST:
	IDLIST Id
	| Id
	;

BinaryValue:
	KW_TRUE {$$ = 1;}
	|KW_FALSE {$$ = 0;}
	;


%% 
void yyerror(char *s) { 
	printf("%s",s);
} 
int main(void) { 
    yyparse(); 
    return 0; 
} 
