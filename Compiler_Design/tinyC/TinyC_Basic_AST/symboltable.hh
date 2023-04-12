
#ifndef SYMBOL_TABLE_HH
#define SYMBOL_TABLE_HH

#include<string>
#include<list>

using namespace std;

class SymbolTableEntry;

typedef enum
{
	INT
} DataType;

typedef enum
{
	LOCAL
} TableScope;

class SymbolTable
{
	list<SymbolTableEntry *> varTable;
	TableScope scope;
public:
	SymbolTable();
	~SymbolTable();
	TableScope getTableScope();
	void setTableScope(TableScope);
	void print(ostream &);
	void pushSymbol(SymbolTableEntry *);
	bool variableInSymbolListCheck(string);
	SymbolTableEntry & getSymbolTableEntry(string variablename);
	
};

class SymbolTableEntry
{
	string variablename;
	DataType variabledatatype;
	TableScope scope;
	int lineNumber;
public:
	SymbolTableEntry();
	SymbolTableEntry(string &, DataType , int);
	~SymbolTableEntry();
	int getLineNumber();
	void setSymbolScope(TableScope sp);
	TableScope getSymbolScope();
	DataType getDataType();
	void setDataType(DataType);
	string getVariableName();

};

class toks{
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
                        o<<"Token: "<<tok<<"\t";o.width(8);
                        o<<"Lineno: "<<lineno<<"\n";
                        }
        };


#endif
