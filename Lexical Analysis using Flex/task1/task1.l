/*
Name:	Abdul Ghaffar Kalhoro
	Ahmad Amjad Mughal
Class:	BSCS-6C
Compiller Construction Lab-5.
*/


/********************************
Task: 1 ~~ Code for PostFix with
~~input string::  

procedure compute
begin
    area = 3.141 * radius * radius
end
function main
begin
    compute
end
********************************/


/*Transational rules*/

%%
(("if"|("then")|("begin")|("end")|("procedure")|("function"))) {printf("A keyword: "); ECHO; printf("\n");}

([+-/*<>=/]|[%$]) {printf("An Operator: "); ECHO; printf("\n");}

(\") {printf("A Qoutation: "); ECHO; printf("\n");}

([()]|[{}]) {printf("A Bracket: "); ECHO; printf("\n");}

("//".*) {printf("A Comment: "); ECHO; printf("\n");}

(\\n) {printf("A newline operator"); ECHO; printf("\n");}

(;) {printf("A Semicolon: "); ECHO; printf("\n");}

(!) {printf("An Exlamation Mark: "); ECHO; printf("\n");}

([\n\t" "]) {}


([+-]?([0-9]*[.])?[0-9]+) {printf("A Number : "); ECHO; printf("\n");}

([A-Z]) {printf(" Capital Alphabets "); ECHO; printf("\n");}

([a-z]+[0-9a-zA-Z]*) {printf("An identifier: "); ECHO; printf("\n");}

. {printf("Unrecognized character: "); ECHO; printf("\n");}

%%
//driver function
int main(int argc, char **argv)

{
//condition for the file input
if(argc>1)

yyin=fopen(argv[1],"r");

else

yyin=stdin;
//lexical analyser invoking function.
yylex();

}
