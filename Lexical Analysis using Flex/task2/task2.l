/*
Name:	Abdul Ghaffar Kalhoro
	Ahmad Amjad Mughal
Class:	BSCS-6C
Compiller Construction Lab-5.
*/


/********************************
Task: 2 ~~ Code for PostFix with
input string::  44 33 22 * + 1 -
********************************/

%{ 
// #define stack_size 5
 static int indexStack, stackValue [5];
int counter1 = 0;
//function for pushing values.
 static void func_pushValues (int func_arg) {
//condition for checking stack size to be less than 5
   if (++indexStack<5) {
//insert into stack
stackValue[indexStack]= func_arg;
}
 }
//printing function.
static void print() {

//loop until less than value.
for(counter1 = 0;counter1<5;counter1++){
printf("%d ",stackValue[counter1]);
}
printf("\n");


}
//pop all the values of the stack function
 static int stackPOP (void) {
   if (indexStack>=0) {
indexStack = indexStack;
int temp = stackValue[indexStack];
stackValue[indexStack] = 0;
indexStack = indexStack -1;
return temp;

}

 }
%}
%%

[0-9]+                   {func_pushValues (atoi(yytext));print();}
"+"                      {func_pushValues (stackPOP() + stackPOP());print();}
"-"                        {int right= stackPOP(); func_pushValues (stackPOP() - right);print();}
"*"                      {int first = stackPOP();int second = stackPOP(); int product = first*second; func_pushValues(product);print();}
"/"                      {int right= stackPOP(); func_pushValues (stackPOP() / right);print();}
"\n"                       {printf ("Result = %d\n", stackPOP());}
[ \t\n]                  ;
%%                        
//drive function
 int main (void) {
indexStack= -1; 

yyin = stdin;
printf("Input Value:: \t");

yylex(); 
}


