%{
	#include <stdio.h>
	extern FILE* yyin;
	extern char *yytext;
	int yylex(void);

%}

%x CMNT 
%x SCMNT

%% 

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
	++argv;
	--argc;
	if(0<argc)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
	while(yylex())
		printf("%s",yytext);
	return 0;
}
