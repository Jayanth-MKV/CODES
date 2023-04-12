%{
	#include <iostream>
        using namespace std;
        #include <map>
	#include "Register.hh"
	#include "symboltable.hh"
        #include "codegeneration.hh"
//	#include "symboltable.hh"
        #include "ast.hh"
        #include "Function.hh"
        #include "program.hh"	
        #include "y.tab.h"
        #include <string.h>

	int lineno=0;
	
/*	class toks{
        string tok_name;
        string tok;
        int lineno;
        public:
		toks(string tn,string t,int l){
			tok_name=tn;
			tok=t;
			lineno=l;
		}
		void print(ostream & o){
			o<<"Token Name: ";
			o.width(8);
			o<<tok_name<<"\t";
			o<<"Token: ";o.width(8);
			o<<"Lineno: "<<lineno<<endl;
			}
	};
*/
	list<toks*> tokenList;
	 		
%}

%%
void {tokenList.push_back(new toks("VOID","void",lineno)); return VOID;}
print {tokenList.push_back(new toks("PRINT","print",lineno)); return PRINT;}
end {tokenList.push_back(new toks("END","end",lineno));return END;}
int {cout<<"int"<<endl;tokenList.push_back(new toks("INTEGER","int",lineno));return INTEGER;}
return {tokenList.push_back(new toks("RETURN","return",lineno));return RETURN;}

[a-zA-Z][a-zA-Z0-9_]* {	cout<<yytext<<endl;tokenList.push_back(new toks("NAME",yytext,lineno));
                        yylval.cval=(char*)malloc(sizeof((char*)strlen(yytext)));
                        strcpy(yylval.cval,yytext);
                        return ID;}

[0-9]+  {tokenList.push_back(new toks("NUM",yytext,lineno)); cout<<yytext<<endl;  yylval.ival=atoi(yytext); return NUMBER;}

[(){}+=;]     {tokenList.push_back(new toks("METACHAR",yytext,lineno)); return yytext[0];}

[ \t]+	{}

\n      { lineno++;}

.	{cout<<"Not defined in Lex"<<endl;}

%%
