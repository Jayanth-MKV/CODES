%{
#include "ExprValue.hh"
#include "Date.hh"
#include<iostream>
using namespace std;
extern int yylex();
extern void yyerror(char const*);
%}
%union{
      int number;
      Date *date;
      ExprValue *ev;
}
%start line
%token <number> NUMBER
%token <date> DATE_TOKEN
%type <ev> DE
%%
line:  DE '\n'            {
                              if($1->vt==INT_VALUE)
                                cout<<$1->v.number;
                              else
                                 $1->v.date->print();
                          }
     ;
DE:   DE '+' NUMBER       {       
				$$ = new ExprValue();
                                    $$->v.date= new Date(*($1->v.date)+($3));
                                    $$->vt=DATE_VALUE;
                                  
                          }
    
    | DE '-' DE      {	if($3->vt==INT_VALUE){
				    $$ = new ExprValue();
                                   
                                    $$->v.date= new Date(*($1->v.date)-($3->v.number));
                                    $$->vt=DATE_VALUE;

				}
				else{

                                           $$ = new ExprValue();
                                            $$->v.number=*($1->v.date)-*($3->v.date);
                                            $$->vt=INT_VALUE;
			             }
				}

    | NUMBER              {
                                $$ = new ExprValue();
                                $$->v.number=$1;
                                $$->vt=INT_VALUE;
			
                          }
    |  DATE_TOKEN         {
                             $$ = new ExprValue();
                             $$->v.date=new Date(*$1);
                             $$->vt=DATE_VALUE;
			
                           }
    ;
        
%%
int main(){
 yyparse();
}

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }
