/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
//------------------------------------------Lab-04----------------------------------//
//-------Ahmad Amjad Mughal and Abdul Ghafaar Kalhoro-------------------------------//
//---------------------------------Group-Lab-03 and 04------------------------------//
//preprocessor directories and header files
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

//defined variables and data structures 
map< string,vector<string> > symbol_table; // for toke id as string and its lexeme in vector
string num= "";
string keywordsTemp[] = {"break", "case", "char", "const", "continue", "default", "double", "else", "enum", "extern", "float", "for","goto", "if", "int", "long", "return", "short", "static", "struct", "switch", "void", "while"}; 
#define LENGTH 23
string identifier = "";
//Counters for every type of a token
int kw_count = 0;
int id_count = 0;
int relop_count = 0;
int num_count = 0;
int punc_count = 0;
int ao_count = 0;
int lindex = 0; //line index for scanning
//For token
struct Token{
  string token_id;
  string lexeme;
};

// Blacnks, Tabs and Whitespaces are skipped
bool multiline_flag = false;

string removeComments(string str){

  if(multiline_flag == false){
    int comm_index=-1;
    //single line comments
    for(int i=0;i<str.length()-1; i++){
        if(str.at(i) == '/' && str.at(i+1)=='/'){
            comm_index = i;
            break;
          }

    }

    //multiline comments
  int first = -1;
  int last = -1;

  for(int i=0;i<str.length()-1; i++){
        if(str.at(i) == '/' && str.at(i+1)=='*'){
            first = i;
            for(int j=first;j<str.length()-1; j++){
               if(str.at(j) == '*' && str.at(j+1)=='/'){
                  last = j+1;
                  break;
                }
            }
            break;
          }

    }

  if(first != -1 && last != -1){

  str.erase (first,last);

}

//When Multicomment end NOT FOUND
if(first != -1 && last == -1){

  multiline_flag = true;

}



if(comm_index !=-1){
      str.resize(comm_index);
      
        }

}else {

  int l = -1;
  for(int j=0;j<str.length()-1; j++){
               if(str.at(j) == '*' && str.at(j+1)=='/'){
                  l = j+1;
                  multiline_flag = false;
                  break;
                }
            }
        if (multiline_flag == false){
           str.erase (0,l+1);            
        }

}  

  return str;


}

//whitespace removal i.e. blanks, tabs and newlines
string whitespace_removal(string line){

      line.erase(std::remove(line.begin(), line.end(), '\t'),
              line.end());
      line.erase(std::remove(line.begin(), line.end(), '\n'),
              line.end());

      return line;
}

vector<string> empty_elements_removal(vector<string> input){

  for(int i=0;i<input.size();i++){
      if(input[i].length() == 1){
          input.erase(input.begin()+i);
      } 

  } 

for(int i=0;i<input.size();i++){
      if(input[i].length() == 1){
          input.erase(input.begin()+i);

      }
        }     

return input;  
}

void initialize_symbol_table(){

//initializing symbol table 
symbol_table["BREAK"].push_back("break");
symbol_table["CASE"].push_back("case");
symbol_table["CHAR"].push_back("char");
symbol_table["CONST"].push_back("const");
symbol_table["CONTINUE"].push_back("continue");
symbol_table["DEFAULT"].push_back("default");
symbol_table["DOUBLE"].push_back("double");
symbol_table["ELSE"].push_back("else");
symbol_table["ENUM"].push_back("enum");
symbol_table["EXTERN"].push_back("extern");
symbol_table["FLOAT"].push_back("float");
symbol_table["FOR"].push_back("for");
symbol_table["GOTO"].push_back("goto");
symbol_table["IF"].push_back("if");
symbol_table["INT"].push_back("int");
symbol_table["LONG"].push_back("long");
symbol_table["RETURN"].push_back("return");
symbol_table["SHORT"].push_back("short");
symbol_table["STATIC"].push_back("static");
symbol_table["STRUCT"].push_back("struct");
symbol_table["SWITCH"].push_back("switch");
symbol_table["VOID"].push_back("void");
symbol_table["WHILE"].push_back("while");

//CHecking for keyword
}
bool checkKeyWord(){
  for(int i=0;i<LENGTH;i++){
    if(identifier.compare(keywordsTemp[i])==0){
      return true;

    }

  }
return false;
}

//Automata implementation of Relational Operators, Punctuations, Arithematic Operators

Token isToken(string line){
    num = "";
    identifier = "";
    Token final;
    final.token_id = "";
    char state = '1';

    while(line.length() > lindex){
          char ch = line[lindex];
          lindex = lindex + 1;
            
          //dfa for this
          switch(state){
              case '1':
                    if(ch == '<')
                        state = '2';
                    else if(ch == '>')
                        state = '3';
                    else if(ch == '=')
                        state = '5';
                    else if (ch == '!')
                        state = '4';
                    else if (ch == '*')
                        state = 'a';
                    else if (ch == '/')
                        state = 'b';
                    else if (ch == '%')
                        state = 'c';
                    else if (ch == '+')
                        state = 'd';
                    else if (ch == '-')
                        state = 'f';   
                    else if (ch == '(')
                        state  = 'g';
                    else if (ch == ')')
                        state  = 'h';
                    else if (ch == '{')
                        state  = 'i';
                    else if (ch == '}')
                        state  = 'j';
                    else if (ch == '[')
                        state  = 'k';
                    else if (ch == ']')
                        state  = 'l';
                    else if (ch == ';')
                        state  = 'm';
                    else if (ch == ':')
                        state  = 'n';
                    else if (ch == ',')
                        state  = 'o';
                    else if (ch == '.')
                        state  = 'p';
                    else if(isdigit(ch)){ //checking for number
                          state = 'q';
                          num += ch;
                        }
                    else if( (isalpha(ch)) || ch == '_'){
                          state = 'w';
                          identifier+=ch;
                        }
                    else {
                        //lindex-=1;
                        return final;
                      }
                break;
              
              case '2':
                        if (ch == '=')
                          {
                              final.token_id = "LE";
                              final.lexeme = "<=";
                              relop_count +=1;
                              return final;

                          }
                        else
                        {
                          final.token_id = "LT";
                          final.lexeme = "<";
                           relop_count +=1;
                           lindex-=1;
                          return final;
                        }
                    break;

              case '3':
                    
                    if(ch == '=')
                        {
                          final.token_id = "GE";
                          final.lexeme = ">=";
                          relop_count +=1;
                          return final;

                        }
                    else{

                      final.token_id = "GT";
                       final.lexeme = ">";
                        relop_count +=1;
                        lindex-=1;
                        return final;

                    }
                break;


              case '4':
                    if(ch == '=')
                      {
                        final.token_id = "NE";
                          final.lexeme = "!=";
                           relop_count +=1;
                          return final;

                      }
                      else{
                        lindex-=1;
                        return final;
                      } 
                break;

              case '5':
                  if(ch == '=')
                     {
                        final.token_id = "EQ";
                        final.lexeme = "==";
                         relop_count +=1;
                        return final;
                     }
                   else
                   {
                        final.token_id = "OP";
                        final.lexeme = "=";
                         punc_count  +=1;
                         lindex-=1;
                        return final;

                   }  
                break;

                case 'a':
                    final.token_id = "MULT";
                    final.lexeme = "*";
                    ao_count += 1;
                    lindex-=1;
                    return final;
                break;

                case 'b':
                    final.token_id = "DIV";
                    final.lexeme = "/";
                    ao_count += 1;
                    lindex-=1;
                    return final;
                break;

                case 'c':
                    final.token_id = "MOD";
                    final.lexeme = "%";
                    ao_count += 1;
                    lindex-=1;
                    return final;
                break;
               
               case 'd':
                  if (ch == '+')
                          {
                              final.token_id = "INC";
                              final.lexeme = "++";
                              ao_count +=1;
                              return final;

                          }
                        else
                        {
                          final.token_id = "PL";
                          final.lexeme = "+";
                           ao_count +=1;
                           lindex-=1;
                          return final;
                        }

               break;

                 case 'f':
                  if (ch == '-')
                          {
                              final.token_id = "DEC";
                              final.lexeme = "--";
                              ao_count +=1;
                              return final;

                          }
                        else
                        {
                          final.token_id = "MINUS";
                          final.lexeme = "-";
                           ao_count +=1;
                           lindex-=1;
                          return final;
                        }

               break;
                    
                      case 'g':
                    final.token_id = "LPAREN";
                    final.lexeme = "(";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'h':
                    final.token_id = "RPAREN";
                    final.lexeme = ")";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'i':
                    final.token_id = "MLPAREN";
                    final.lexeme = "{";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'j':
                    final.token_id = "MRPAREN";
                    final.lexeme = "}";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'k':
                    final.token_id = "SQLPAREN";
                    final.lexeme = "[";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'l':
                    final.token_id = "SQRPAREN";
                    final.lexeme = "]";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'm':
                    final.token_id = "SCOLON";
                    final.lexeme = ";";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'n':
                    final.token_id = "COLON";
                    final.lexeme = ":";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'o':
                    final.token_id = "COMMA";
                    final.lexeme = ",";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                 case 'p':
                    final.token_id = "DOT";
                    final.lexeme = ".";
                    punc_count += 1;
                    lindex-=1;
                    return final;
                break;

                //for number checking


                case 'q':
                    if (isdigit(ch)){
                        state = 'q';
                        num += ch;
                      }
                    else if (ch == '.'){
                        state = 'r';
                        num += ch;
                      }

                    else if (ch == 'E'){
                        state = 't';
                        num += ch;
                      }
                   
                    else {
                    
                    final.token_id = "NUM";
                    final.lexeme = num;
                    num_count += 1;
                    lindex-=1;
                    return final;
                    }

                break;

                case 'r':

                  if (isdigit(ch)){
                        state = 's';
                        num += ch;
                      }
                  else{
                    lindex-=1;
                    return final;
                  }

                break;

                case 's':

                  if (isdigit(ch)){
                        state = 's';
                        num += ch;
                      }
                  else if (ch == 'E'){
                        state = 't';
                        num += ch;
                      }

                  else {

                    final.token_id = "NUM";
                    final.lexeme = num;
                    num_count += 1;
                    lindex-=1;
                    return final;

                  }

                break;

                case 't':
                      if (ch == '+' || ch == '-')
                        state = 'u';
                      else if(isdigit(ch))
                          state = 'v';
                        else{
                            lindex-=1;
                            return final;
                          }
                break;

                case 'u':
                      if(isdigit(ch))
                          state = 'v';
                        else{
                          lindex-=1;
                          return final;
                        }
                break;

                case 'v':
                      if(isdigit(ch))
                          state = 'v';
                        else
                        {
                            final.token_id = "NUM";
                            final.lexeme = num;
                            num_count += 1;
                            lindex-=1;
                            return final;

                        }
                break;

                case 'w':
                      if(isdigit(ch) || isalpha(ch) || ch == '_'){
                        identifier +=ch;
                        state = 'w';

                      }
                      else
                      {
                          if(!checkKeyWord()){
                            final.token_id = "ID";
                            final.lexeme = identifier;
                            id_count += 1;
                            lindex-=1;
                            return final;
                          }
                          else{
                            final.token_id = "KeyWord";
                            final.lexeme = identifier;
                            kw_count+=1;
                            lindex-=1;
                            return final;

                          }

                      }
                break;
        }


    }

    return final;

}



vector<Token> getNextToken(string line){
  vector<Token> tokens;
  line = line + " ";

  while (lindex < line.length()){
    
    Token temp  = isToken(line);

    if((temp.token_id).compare("") != 0){
        tokens.push_back(temp);
    }

  }

return tokens;

}

//checking for macros and header files
void preprocessor(string line){

  if(line.at(0)=='#'){
        cout << "< ";
        cout <<  "preprocessor";
        cout << " , ";
        cout <<  "#" ;
        cout << ">"<< endl;
    }
  ifstream myfile ("input_scanner.h");

   if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
    
      line = whitespace_removal(line); 
      line.erase(std::remove(line.begin(), line.end(), ' '),
              line.end());
      string noComments = removeComments(line);
      
      if(noComments.at(0)=='#' && noComments.at(1)=='d'){

        cout << "< ";
        cout <<  "Macro";
        cout << " , ";
        cout <<  "#Define" ;
        cout << ">"<< endl;   

      }
      if(noComments.at(0)=='#' && noComments.at(1)=='i'){

        cout << "< ";
        cout <<  "Header";
        cout << " , ";
        cout <<  "#include" ;
        cout << ">"<< endl;   

      }

}
}
    myfile.close();
}
//Function to get NextToken and placed them in an order for display 
void driverGetNextToken(vector<string> input){

  vector<Token> tokens;

  for (int i=0; i<input.size();i++){ 
      lindex = 0;
      if(input[i].at(0)=='#'){
        preprocessor(input[i]);
      }
       else{ 
      tokens = getNextToken(input[i]);

      for(int j = 0;j < tokens.size(); j++){

        symbol_table[tokens[j].token_id].push_back(tokens[j].lexeme);
        cout << "< ";
        cout <<  tokens[j].token_id;
        cout << " , ";
        cout <<  tokens[j].lexeme ;
        cout << ">"<< endl;
      }
  }
}

}

int main(){

  //skip comments from code single line or multiline
  vector<string> input;
  string line;
  ifstream myfile ("input_scanner.cpp");
    
  if (myfile.is_open())
  {
    cout << "---------------------------------------Welcome to Lexical Analyzer------------------------------------!"<<endl;
    cout << "<TokenID, Lexeme> is the format of the generated Tokens\n" <<endl;
    while ( getline (myfile,line) )
    {
    
      line = whitespace_removal(line); 
      string noComments = removeComments(line);
      if(multiline_flag == false){
      input.push_back(noComments);
    } 
      
    }
    myfile.close();
  }

  else 
    cout << "Unable to open file"; 


  input = empty_elements_removal(input);

  //symbol table fill for keyworkds

  initialize_symbol_table();
  driverGetNextToken(input);

      return 0;
}
