#include <iostream>
using namespace std;
#include <map>
#include "Register.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
#include "ast.hh"
#include "Function.hh"
#include "program.hh"
#include "machinedescription.hh"

Program::Program(){
		//cout<<"Machine Desc initialized"<<endl;
		machineDes.initInstTable();
		machineDes.initRegTable();
	}

Program::~Program(){}

 Function * Program:: getFunctionDetails(string s){
 	if(FunctionMap.find(s)!=FunctionMap.end()){
		return FunctionMap[s];
	}
	return NULL;
 }
void Program:: addFunctionDetails(string s , Function * f){
	FunctionMap[s]=f;
}
void Program:: setFunctionMap(map<string, Function *> & m){
	FunctionMap=m;
}
void Program:: setGlobalTable(SymbolTable & st){
	globalSymbolTable=st;
}
SymbolTableEntry & Program:: getSymbolTableEntry(string s){
	return globalSymbolTable.getSymbolTableEntry(s);
}
void Program:: printSymbolTable(ostream & o){
	return globalSymbolTable.print(o);
}

void Program:: print(ostream &o){
	o<<"Global Declarations : "<<endl;
	printSymbolTable(o);
	o<<"Program"<<endl;
	for(auto i=FunctionMap.begin();i!=FunctionMap.end();i++){
		(i->second)->print(o);
	}
}

void Program::printAst(ostream &f){
	f<<"AST"<<endl;
	for(auto i=FunctionMap.begin();i!=FunctionMap.end();i++){
         list<Ast*> statementList=(i->second)->getAstlist();

        for(Ast* i:statementList){
                (i)->print(f);
        }
	}
}

Function * Program:: getMainFunction(){
	return  getFunctionDetails("main");
}

bool Program:: variableFunctionNameCheck(string s){
	if(FunctionMap.find(s)!=FunctionMap.end()){
                return true;
        }
	else{
		return false;
	}
}

bool Program:: variableInSymbolTableCheck(string s){
	return globalSymbolTable.variableInSymbolListCheck(s);
}


void Program :: generateTargetCode(){
	//cout<<"begin tg_program.cpp"<<endl;
	for(auto i=FunctionMap.begin();i!=FunctionMap.end();i++){
		(i->second)->generateTargetCode();
	}
	//cout<<"exit tg_program.cpp"<<endl;

}

void Program :: printTargetCode(ostream &o){
	generateTargetCode();
//	cout<<"TargetcodeGen completed"<<endl;
	for(auto i=FunctionMap.begin();i!=FunctionMap.end();i++){
//		cout<<"--- Function ---"<<endl;
                (i->second)->printTargetCode(o);
        }
}
