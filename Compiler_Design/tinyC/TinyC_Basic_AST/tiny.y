%{
	#include <iostream>
        #include <fstream>
	#include <cstring>
	#include <filesystem>
	using namespace std;
        #include <map>
        #include "symboltable.hh"
        #include "ast.hh"
        #include "Function.hh"
        #include "program.hh"    

    void yyerror(const char *s);
    int yylex();
    extern FILE* yyin;
    SymbolTable* gst=new SymbolTable();
    Program * pr;
    extern int lineno;
    extern list<toks*> tokenList;
%}

%union{
	Program* pro;
        SymbolTable* sym;
	SymbolTableEntry * ste;
	Function* func;
        char* cval;
	int ival;
	Ast* a;
	list<Ast*> *la;
	DataType dt;
};

%start lines
%token <ival> NUMBER
%token <cval> ID
%token END
%token RETURN
%token VOID
%token PRINT
%token INTEGER
%token PRINTALL

%left '+' '-'
%left '*' '/'
%type <ival> digit digits int_const
%type <pro> program
%type <func> body
%type <a> assign_stmt
%type <la> assign_stmt_list local_decl_optional
%type <ste> vardecl
%type <cval> id
%type <dt> int void returnty
%%

int: INTEGER	{
		DataType dt=INT;
		$$=dt;
		}
;

void: VOID {DataType dt=INT;
		$$=dt;
		}		
;

lines: program	{
				//$1->print(cout);
			}
	|END
;

returnty:int{$$=$1;}
	|void{$$=$1;}
;

program: returnty ID '('')' '{' body return_main '}'	{
							pr=new Program();
							$$=pr;
							string s=$2;
							SymbolTableEntry *ste=new SymbolTableEntry(s,$1,lineno);
							gst->pushSymbol(ste);
							$$->setGlobalTable(*gst);
							$6->setfunctionname($2);
							$6->setdatatype($1);
							$$->addFunctionDetails($2,$6);
						}
;


body: local_decl_optional assign_stmt_list { list<Ast*>::iterator i =$2->begin();	
				for(auto i=($2)->begin();i!=($2)->end();i++){($1)->push_back(*i);}	
						$$=new Function();
						$$->setAstList(*$2);
						$$->setLocalList(*gst);					
}
	| assign_stmt_list	{
						$$=new Function();
                                                $$->setAstList(*$1);
                                                $$->setLocalList(*gst);
				}
;

return_main: 
		RETURN NUMBER ';'	{}
	;

assign_stmt_list: assign_stmt {			
				
                                                $$=new list<Ast*>();
                                                $$->push_back($1);
                                                
				}
	|assign_stmt_list assign_stmt {	
						($1)->push_back($2);
						$$=$1;
					}
;

assign_stmt:	id '=' id ';'{  
				if(gst->variableInSymbolListCheck($1)){
				if(gst->variableInSymbolListCheck($3)){ 
				Ast* a=new AssignmentAst(new NameAst(gst->getSymbolTableEntry($1),lineno),new NameAst(gst->getSymbolTableEntry($3),lineno),lineno);
                                $$=a;
				}
                                else{   
				cout<<$3<<" Not declared"<<endl;
                                }
				}
				else{	cout<<$1<<" Not declared"<<endl;
				}
				}

		| id '=' int_const ';'	{
						
					if(gst->variableInSymbolListCheck($1)){
					DataType dt=INT;
Ast* a=new AssignmentAst(new NameAst(gst->getSymbolTableEntry($1),lineno),new NumberAst<int>($3,dt,lineno),lineno);
                                	$$=a;
					}
                	               	 else{   cout<<$1<<" Not declared"<<endl;
        	                       	}
	
					}
		| PRINT id ';'	{
					if(gst->variableInSymbolListCheck($2)){
                                        Ast* a=new PrintAst(new NameAst(gst->getSymbolTableEntry($2),lineno),lineno);
                                        $$=a;
					}
                                         else{   cout<<$2<<" Not declared"<<endl;
                                        }
				}
;

local_decl_optional:	vardecl local_decl_optional{	Ast * nast=new NameAst(*$1,lineno);
							$2->push_back(nast);
							gst->pushSymbol($1);
							$$=$2;
							}
			| vardecl		{
						$$=new list<Ast*>();
						Ast * nast=new NameAst(*$1,lineno);
						gst->pushSymbol($1);
						$$->push_back(nast);
						}
;
vardecl:	int ID ';' {
			string s=$2;
			SymbolTableEntry* ste=new SymbolTableEntry(s,$1,lineno); 
			$$=ste;
			 }
;

id:	ID	{$$=$1;	}
;

digit:	NUMBER	{$$=$1;}
;

int_const:	'+'digits	{$$=$2;}
	|'-'digits	{$$=($2)*-1;}
	|digits	{$$=$1;}
;

digits:	digit digits	{$$=($1*10)+$2;}
	|digit	{$$=$1;}
;

%%

int main(int argc,char* argv[]){
if(argc==3){
cout<<"Inside"<<endl;
yyin=fopen(argv[2],"r");
yyparse();

string s=argv[2];
string t=".tokens";
string a=".AST";
string sym=".symtable";

remove((s+t).c_str());
remove((s+a).c_str());
remove((s+sym).c_str());

if(strcmp(argv[1],"-toks")==0){
ofstream outfile(strcat(argv[2],".tokens"));
if(!outfile)
cout<<"Error in creating file"<<endl;
for(auto i=tokenList.begin();i!=tokenList.end();i++){
(*i)->print(outfile);
}

outfile.close();
}
else if(strcmp(argv[1],"-ast")==0){
ofstream outfile(strcat(argv[2],".AST"));
if(!outfile)
cout<<"Error in creating file"<<endl;

pr->printAst(outfile);
outfile.close();
}
else if(strcmp(argv[1],"-symtab")==0){
ofstream outfile(strcat(argv[2],".symtable"));
if(!outfile)
cout<<"Error in creating file"<<endl;

pr->print(outfile);
outfile.close();
}
}
else{
cout<<"\tUsage: tinyCC [options] [file]"<<endl;
cout<<"\t\t\tOptions:"<<endl;
cout<<"\t\t\t-help/any     Show this help"<<endl;
cout<<"\t\t\t-parse	  Stop processing with parsing"<<endl; 
cout<<"\t\t\t-toks   Show the tokens in file.toks (or out.toks)"<<endl;
cout<<"\t\t\t-ast      Show abstract syntax trees in file.ast (or out.ast)"<<endl;
cout<<"\t\t\t-symtab   Show the symbol table of delcarations in file.sy, (or out.sym)"<<endl;
cout<<"\t\t\t-compile  Compile the program and generate spim code in file.spim (or out.spim)"<<endl;
}


return 0;
}

void yyerror(const char * msg){
fprintf(stderr,"%s\n",msg);

/*
tinyC: lexical.o parser.o
        g++ -o tinyC lexical.o parser.o -ll -ly
lexical.o: lex.yy.c
        g++ -c lex.yy.c -o lexical.o
lex.yy.c: tiny.l  y.tab.h
        lex tiny.l
parser.o: y.tab.c
        g++ -c y.tab.c -o parser.o
y.tab.c y.tab.h: copy_tiny.y
        yacc -d copy_tiny.y
clean: *.o
        rm *.o
*/
}
