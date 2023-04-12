#include <iostream>
using namespace std;
#include "symboltable.hh"
#include "ast.hh"

Ast::Ast(){}

Ast::~Ast(){}

DataType Ast::getDataType(){
	return nodeDataType;
}

bool Ast:: typeCheckAst(){
	if(nodeDataType!=INT)
	return true;
	else
	return false;
}

void Ast:: print(ostream &o){
	o<<"DATATYPE: "<<nodeDataType<<" LineNO: "<<lineNumber<<endl;
}

AssignmentAst::AssignmentAst(Ast * left,Ast* right,int line){
	lhs=left;
	rhs=right;
	lineNumber=line;
}

AssignmentAst::~AssignmentAst(){
}

bool AssignmentAst::typeCheckAst(){
	return lhs->typeCheckAst();
}

void AssignmentAst::print(ostream& o){
	//o<<"DATATYPE: "<<nodeDataType<<" LineNO: "<<lineNumber<<endl;
	o<<"Asgn:"<<endl;
	o<<"\tLHS "<<"( ";
	lhs->print(o);
	o<<" )"<<endl;
	o<<"\tRHS "<<"( ";
	rhs->print(o);
	o<<" )"<<endl;
}

PrintAst::PrintAst(Ast* v,int l){
	var=v;
	lineNumber=l;
}

PrintAst::~PrintAst(){}

void PrintAst::print(ostream& o){
	o<<"Print:"<<endl;
	o<<"\t";
	var->print(o);
	o<<endl;
}

NameAst::NameAst(SymbolTableEntry& ste,int l){
	lineNumber=l;
	variablesymbolentry=&ste;
}

NameAst::~NameAst(){}

DataType NameAst::getDataType(){
	return variablesymbolentry->getDataType();
}

SymbolTableEntry & NameAst:: getSymbolEntry(){
	return *variablesymbolentry;
}

void NameAst:: print(ostream& o){
	o<<"Name : "<<variablesymbolentry->getVariableName();
}

template <class T> NumberAst<T>::NumberAst(T t,DataType dt,int l){
	constant=t;
	nodeDataType=dt;
	lineNumber=l;
}

template <class T> NumberAst<T>::~NumberAst(){
}

template <class T> DataType NumberAst<T>::getDataType(){
	return nodeDataType;
}

template <class T> void NumberAst<T>:: print(ostream& o){
	o<<"NumValue: "<<constant;
}

template class NumberAst<int>;

ReturnAst::ReturnAst(int line){
	lineNumber=line;
}

ReturnAst::~ReturnAst(){
}

void ReturnAst:: print(ostream& o){
	o<<"LINENUMBER: "<<"0"<<endl;
}
