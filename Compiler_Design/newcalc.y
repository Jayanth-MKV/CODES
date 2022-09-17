%{
#include<stdio.h>
extern int yylex();
extern void yyerror(char*);
%}
%start stat
%token NUMBER
%%                   /* beginning of rules section */
stat:    expr '\n'        {
                           printf("%d\n",$1);
                          }
         ;

expr:   expr '+' term    {
                                    $$ = $1 + $3;
                          }
        | expr '-' term   {
                                  $$= $1-$3;
                          }
        | term            {
                                    $$ = $1;
                           }
         ;
term:   term '*' factor  {
                            $$ = $1 * $3;
                          }
        | term '/' factor   {
                                $$ = $1/$3;
                             }
        | factor           {
                              $$ = $1;
                            }
         ;

factor: NUMBER            {
                                $$ = $1;
                          }

%%
int main()
{
 yyparse();
}

