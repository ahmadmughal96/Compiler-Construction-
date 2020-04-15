%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	extern FILE* yyin;
	extern char *yytext;
	int yylex(void);
	

%}

ws	[" "\t]+
digit	[0-9]
alpha	[a-zA-Z]
alnum	[a-zA-Z0-9]
sign 	[+-]
int	{sign}?{digit}+
exp	[Ee]{int}
real	{sign}?(({digit}+[.]{digit}*)|([.]{digit}+))
sci	({int}|{real}){exp}
id	({alpha}|[_])({alnum}|[_])*
literal	\"(\\.|[^"])*\"



macro	[\#]{id}[" "]*{id}[" "]*{real}
directive	[\#]{id}[" "]*[\<][" "]*{id}[.]{id}[" "]*[\>]
directiveS	[\#]{id}[" "]*[\"]{id}[.]{id}[" "]*[\"]

%x CMNT
%x SCMNT

%%

{ws}
{macro}		ECHO;
{directive}	ECHO;
{directiveS}	ECHO;
{literal}	{return LITERAL;}
void|float|int|for|if|return {return KEYWORD;}
{id}	{return ID;}
{int}	{return INT;}
{real}	{return REAL;}
{sci}	{return SCI;}
"++"|"--"	{return INCOP;}
"+="|"-="|"*="|"/="|"="	{return ARASOP;}
"+"|"-"|"*"|"/"	{return ARITOP;}
">"|"<"|"<="|">="|"=="|"!="	{return RELOP;}
"&&"|"||"	{return LOGICOP;}
"&"|"^"|"|"	{return BOOLOP;}
"("|")"|"{"|"}"|"["|"]"|","|";"|"."|""""|"''"	{return MRK;}
"?"|":"	{return CONDOP;}

"/*"	{BEGIN CMNT;}
"//"	{BEGIN SCMNT;}

<CMNT>.
<CMNT>\n
<CMNT>"*/"	{BEGIN INITIAL;}

<SCMNT>.
<SCMNT>\n	{BEGIN INITIAL;}


	
.	ECHO;

%% 

int yywrap(){
	return 1; 
}


int main(int argc,char* argv[]){
	int token;	
	++argv;
	--argc;
	if(0<argc)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
	while(token = yylex()){
	
		switch(token){
			case INT:
				printf("<INT, %d>",atoi(yytext));	
			break;
			
			case REAL:
				printf("<REAL, %f>",atof(yytext));	
			break;

			case SCI:
				printf("<SCI, %f>",atof(yytext));	
			break;
			
			case ID:
				printf("<ID, %s>",yytext);
			break;
			
			case MRK:
				printf("<MRK, %s>",yytext);
			break;

			case ARASOP:
				printf("<ARASOP, %s>",yytext);
			break;
			
			case ARITOP:
				printf("<ARITOP, %s>",yytext);
			break;
			
			
			case RELOP:
				printf("<RELOP, %s>",yytext);
			break;

			case INCOP:
				printf("<INCOP, %s>",yytext);
			break;
			
			case BOOLOP:
				printf("<BOOLOP, %s>",yytext);
			break;
			
			case CONDOP:
				printf("<CONDOP, %s>",yytext);
			break;
			
			case LOGICOP:
				printf("<LOGICOP, %s>",yytext);
			break;
			
			case KEYWORD:
				printf("<%s>",yytext);
			break;
					
			case LITERAL:
				printf("<LITERAL, %s>",yytext);
			break;
	}
	

	}
	return 0;
}





