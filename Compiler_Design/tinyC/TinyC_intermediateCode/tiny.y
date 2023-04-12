%{
	#include <iostream>
        #include <fstream>
	#include <cstring>
	#include <filesystem>
	using namespace std;
        #include <map>   
	#include "Register.hh"
        #include "symboltable.hh"
        #include "codegeneration.hh"
		#include "IntermediateCode.hh"
//      #include "symboltable.hh"
        #include "ast.hh"
        #include "Function.hh"
        #include "program.hh" 
		#include "machinedescription.hh"

    void yyerror(const char *s);
    int yylex();
    extern FILE* yyin;
    SymbolTable* gst=new SymbolTable();
    Program * pr;
	MachineDescriptor machineDes;
    extern int lineno;
    extern list<toks*> tokenList;
%}

%union{
	Program* pro;
	char ch;
        SymbolTable* sym;
	SymbolTableEntry * ste;
	Function* func;
        char* cval;
	int ival;
	double dval;
	Ast* a;
	list<Ast*> *la;
	DataType dt;
	ExprAst *ea;
};

%start lines
%token <ival> NUMBER
%token <cval> ID
%token END
%token RETURN
%token VOID
%token IF
%token ELSE
%token UNARY
%token <cval> LE
%token <cval> GE
%token <cval> EQ
%token <cval> NE
%token <cval> GT
%token <cval> LT
%token <cval> AAND
%token <cval> OOR
%token <cval> NNOT

%token <ch> SUBTRACT
%token <ch> MUL
%token <ch> DIVISION
%token <ch> MODULUS
%token <ch> ADDITION
%token <dval> DOUB

%token PRINT
%token INTEGER
%token PRINTALL

%left MUL DIVISION
%left ADDITION SUBTRACT

%type <ival> digit digits int_const
%type <pro> program
%type <func> body
%type <a> assign_stmt return_main
%type <la> assign_stmt_list print_stmt_list if_else_stmt_list stmt_list local_decl_optional
%type <ste> vardecl
%type <cval> id relop
%type <dt> int void returnty double
%type <a> constant
%type <a> expr relexpr logical_expr
%type <dval> double_const 
%type <ch> arithop
%%

int: INTEGER	{
		DataType dt=INT;
		$$=dt;
		}
;

double: DOUB	{
		DataType dt=DOUBLE;
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
	| double{$$=$1;}
;

program: returnty ID '('')' '{' body return_main '}'	{
							//cout<<"program"<<endl;
							pr=new Program();
							$$=pr;
							string s=$2;
							SymbolTableEntry *ste=new SymbolTableEntry(s,$1,lineno);
							gst->pushSymbol(ste);
							$$->setGlobalTable(*gst);
							$6->setfunctionname($2);
							$6->setdatatype($1);
							list<Ast* > l=($6->getAstlist());
							l.push_back($7);
							$6->setAstList(l);
							$$->addFunctionDetails($2,$6);
						}
;


body: local_decl_optional stmt_list { list<Ast*>::iterator i =$2->begin();	
				for(auto i=($2)->begin();i!=($2)->end();i++){($1)->push_back(*i);}	
						$$=new Function();
						$$->setAstList(*$2);
						$$->setLocalList(*gst);					
}
;

stmt_list:	assign_stmt_list {$$=$1;}
|		print_stmt_list	{$$=$1;}
|		if_else_stmt_list	{$$=$1;}
|		assign_stmt_list stmt_list	{
				list<Ast*>::iterator i =$2->begin();	
				for(auto i=($2)->begin();i!=($2)->end();i++){($1)->push_back(*i);}	
}
|		print_stmt_list stmt_list	{
				list<Ast*>::iterator i =$2->begin();	
				for(auto i=($2)->begin();i!=($2)->end();i++){($1)->push_back(*i);}	
}
;

print_stmt_list:  PRINT id ';'	{
					if(gst->variableInSymbolListCheck($2)){
                                        Ast* a=new PrintAst(new NameAst(gst->getSymbolTableEntry($2),lineno),lineno);
                                        $$=new list<Ast*>();
                                        $$->push_back(a);
					}
                                         else{   cout<<$2<<" Not declared"<<endl;
                                        }
				}
;


if_else_stmt_list: IF '(' logical_expr ')' '{' stmt_list '}' ELSE '{' assign_stmt '}' {	
	//cout<<"in ifelse"<<endl;
	$$=new list<Ast*>();
    Ast * n = new IfElseStmtAst($3,$6->front(),$10);
	$$->push_back(n);
}
| IF '(' logical_expr ')' '{' stmt_list '}' {
	//cout<<"in if"<<endl;
	$$=new list<Ast*>();
    Ast * n = new IfElseStmtAst($3,$6->front(),NULL);
	$$->push_back(n);
}
;

logical_expr : logical_expr AAND logical_expr {
	$$ = new LogicalExprAst($1,$3,AND);
    //$$->push_back(n);
}
| logical_expr OOR logical_expr {	
	$$ = new LogicalExprAst($1,$3,OR);

}
| NNOT logical_expr {
	$$ = new LogicalExprAst($2,NULL,NOT);

}
| relexpr	{
	$$=$1;
}
;

relexpr : expr relop expr {
	
	if(strcmp($2,"<=")==0)
			$$= new RelationalExprAst($1,$3,LESSTHANOREQUALTO);
	else if(strcmp($2,">=")==0)
			$$= new RelationalExprAst($1,$3,GREATERTHANOREQUALTO);
	else if(strcmp($2,"==")==0)
			$$= new RelationalExprAst($1,$3,EQUALTO);
	else if(strcmp($2,"!=")==0)
			$$= new RelationalExprAst($1,$3,NOTEQUALTO);
	else if(strcmp($2,">")==0)
			$$= new RelationalExprAst($1,$3,GREATERTHAN);
	else if(strcmp($2,"<")==0)
			$$= new RelationalExprAst($1,$3,LESSTHAN);
	else{
			cout<<$2<<endl;
			cout<<"default"<<endl;
			break;
		}

}
;

/* 
case "&&":
			$$= new LogicalExprAst($1,$3,AND);
			break;
			case "||":
			$$= new LogicalExprAst($1,$3,OR);
			break;
			case "!":
			$$= new LogicalExprAst($1,$3,NOT);
			break;
*/

relop:  LT {$$=$1;}
| GT {$$=$1;}
| LE {$$=$1;}
| GE {$$=$1;}
| NE {$$=$1;}
| EQ {$$=$1;}

;



return_main: 
		RETURN NUMBER ';'	{$$=new ReturnAst(lineno);}
	;

assign_stmt_list: assign_stmt {			
				
                    $$=new list<Ast*>();
                    $$->push_back($1);
                                                
				}
	| assign_stmt_list assign_stmt {	
						($1)->push_back($2);
						$$=$1;
					}
;

/* 
| assign_stmt_list assign_stmt {	
						($1)->push_back($2);
						$$=$1;
					}
*/

assign_stmt:	
		id '=' id ';'{  
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

		| id '=' constant ';'	{
						
					if(gst->variableInSymbolListCheck($1)){
						Ast* a=new AssignmentAst(new NameAst(gst->getSymbolTableEntry($1),lineno),$3,lineno);
                                	$$=a;
					}
                	               	 else{   cout<<$1<<" Not declared"<<endl;
        	                       	}
	
					}
		| id '=' expr ';'{

					if(gst->variableInSymbolListCheck($1)){
						Ast* a=new AssignmentAst(new NameAst(gst->getSymbolTableEntry($1),lineno),$3,lineno);
                                	$$=a;
					}
                	               	 else{   cout<<$1<<" Not declared"<<endl;
        	                       	}
		}
;



expr : expr arithop expr {
		switch($2){
			case '+':
			$$= new ArithmeticExprAst($1,$3,PLUS);
			break;
			case '-':
			$$= new ArithmeticExprAst($1,$3,MINUS);
			break;
			case '*':
			$$= new ArithmeticExprAst($1,$3,MULTIPLY);
			break;
			case '/':
			$$= new ArithmeticExprAst($1,$3,DIVIDE);
			break;
			case '%':
			$$= new ArithmeticExprAst($1,$3,MOD);
			break;
			default:	
			cout<<$2<<endl;
			cout<<"default"<<endl;
			break;
		}

}
|		id			{$$=new NameAst(gst->getSymbolTableEntry($1),lineno) ;}
|		constant	{$$=$1;}
;



arithop : ADDITION {$$=$1;}
 | SUBTRACT {$$=$1;}
 | MUL 		{$$=$1;}
 | DIVISION {$$=$1;}
 | MODULUS  {$$=$1;}
 ;




local_decl_optional:	vardecl local_decl_optional{	
							Ast * nast=new NameAst(*$1,lineno);
							$2->push_back(nast);
							gst->pushSymbol($1);
							$$=$2;
						}

			| vardecl	{
						$$=new list<Ast*>();
						Ast * nast=new NameAst(*$1,lineno);
						gst->pushSymbol($1);
						$$->push_back(nast);
						}
;
vardecl:	returnty ID ';' {
			string s=$2;
			SymbolTableEntry* ste=new SymbolTableEntry(s,$1,lineno); 
			$$=ste;
			 }
;






constant : int_const{
	DataType dt=INT;
	$$=new NumberAst<int>($1,dt,lineno);
	}
	| double_const{
		DataType dt=DOUBLE;
	$$=new NumberAst<double>($1,dt,lineno);	
	}

id:	ID	{$$=$1;	}
;

double_const : '+' DOUB	{$$=$2;}
	|'-'DOUB	{$$=($2)*-1;}
	|DOUB	{$$=$1;}
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

int main(int argc,char* argv[])
{
if(argc==3){
//cout<<"Inside"<<endl;
yyin=fopen(argv[2],"r");
yyparse();

string s=argv[2];
string t=".tokens";
string a=".AST";
string sym=".symtable";
string ic=".ic";
string sp=".spim";

remove((s+t).c_str());
remove((s+a).c_str());
remove((s+sym).c_str());
//remove((s+ic).c_str());
remove((s+sp).c_str());

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
else if(strcmp(argv[1],"-compile")==0){
ofstream outfile(strcat(argv[2],".spim"));
if(!outfile)
cout<<"Error in creating file"<<endl;

//pr->printTargetCode(outfile);
outfile.close();
}
else if(strcmp(argv[1],"-ic")==0){
ofstream outfile(strcat(argv[2],".ic"));
if(!outfile)
cout<<"Error in creating file"<<endl;

pr->printIntermediateCode(outfile);
outfile.close();
}
}
else if(argc==2){
yyin=fopen(argv[1],"r");
yyparse();
}
else{
cout<<"\tUsage: tinyCC [options] [file]"<<endl;
cout<<"\t\t\tOptions:"<<endl;
cout<<"\t\t\t-help/any     Show this help"<<endl;
cout<<"\t\t\t-parse	  Stop processing with parsing"<<endl; 
cout<<"\t\t\t-toks   Show the tokens in file.toks (or out.toks)"<<endl;
cout<<"\t\t\t-ast      Show abstract syntax trees in file.ast (or out.ast)"<<endl;
cout<<"\t\t\t-ic      Show intermediate code in file.ic "<<endl;
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
