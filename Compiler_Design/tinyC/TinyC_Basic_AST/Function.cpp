#include <iostream>
using namespace std;
#include "symboltable.hh"
#include "ast.hh"
#include "Function.hh"

Function :: Function(DataType d, string s, int a){
	returnType=d;
	name=s;
	lineno=a;
}

Function::Function(){
	returnType=INT;
	name="";
	lineno=0;
}


Function :: ~Function(){
	
}

string Function :: getFunctionName(){
	return name;
}

void Function :: setfunctionname(string s){
	name=s;
}

void Function :: setdatatype(DataType d){
        returnType=d;
}

void Function :: setLocalList(SymbolTable & s){
	localSymbolTable=s;
}

SymbolTable Function :: getLocalList(){
	return localSymbolTable;
}
	
void Function :: setAstList(list<Ast *> & l){
	statementList=l;
}

DataType Function :: getReturnType(){
	return returnType;
}
	
void Function :: setReturnType(DataType d){
	returnType=d;
}

SymbolTableEntry & Function :: getSymbolTableEntry(string s){
	return localSymbolTable.getSymbolTableEntry(s);

/*	list<SymbolTableEntry*> varTable=localSymbolTable.varTable;
	list<SymbolTableEntry*>::iterator it;
        for(it=varTable.begin();it!=varTable.end();it++){
                if((*it)->getVariableName()== s)
                        return *it;
        }
*/
}
	

void Function :: print(ostream & f){
	f<<"DATATYPE:"<<((returnType)==INT?"INT ":" ")<<" NAME: "<<name;
	f<<"LINENO: "<<lineno<<endl;
	f<<"Local Declarations"<<endl;
	printSymbolTable(f);
/*
	f<<"AST"<<endl;
	for(Ast* i:statementList){
		(i)->print(f);
	}
*/	
}


void Function :: printSymbolTable(ostream & f){
	
	localSymbolTable.print(f);
}

list<Ast*> Function :: getAstlist(){
return statementList;
}

//../tinyCC -symtab test.tc
//-tokens next cat filename
