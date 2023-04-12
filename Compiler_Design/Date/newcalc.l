%{
	#include "ExprValue.hh"
	#include "Date.hh"
	#include "y.tab.h"
%}
%%

[0-3][0-9]\/[01][0-9]\/[0-9][0-9][0-9][1-9]   { 
	                                             int d= atoi(strtok(yytext,"/"));
	                                             int m= atoi(strtok(NULL,"/"));
	                                             int y= atoi(strtok(NULL,"/"));
						     Date *pd = new Date(d,m,y);
	                                            
							yylval.date=pd;
                                                 return DATE_TOKEN;
                                               }
[0-9]+  { yylval.number=atoi(yytext); 
           
	return NUMBER;
         }
[-+]     {
		return yytext[0];}
\n      { return yytext[0];}
%%
