#include <iostream>
using namespace std;
#include "Register.hh"
//#include "codegeneration.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
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

TargetCodeForAst & AssignmentAst::generateTargetCode(){
list<Instruction *> pil;
TargetCodeForAst t = rhs->generateTargetCode();
OpCode o=OpCode::storew;
InstructionFormat insf=op_o1_r;
InstructionDescriptor id(o,"sw",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(new RegisterDescriptor(v0, "v0",RegisterValType:: INT, int_reg)));
SymbolTableEntry ste=lhs->getSymbolEntry();
ins->setOpd1(new MemAddrOpd(ste));
pil.push_back(ins);
for(auto i = t.getInstlist().begin();i!=t.getInstlist().end();i++){
//i->setResult(new RegOpd(new RegisterDescriptor(a0, "a0", INT, intreg));
pil.push_back(*i);
}
TargetCodeForAst at(pil,new RegisterDescriptor(v0, "v0",RegisterValType:: INT, int_reg));
return at;
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

TargetCodeForAst & PrintAst::generateTargetCode(){
list<Instruction *> pil;
TargetCodeForAst t = var->generateTargetCode();
OpCode o=OpCode :: immloadw;
InstructionFormat insf=op_r_o1;
InstructionDescriptor id(o,"li",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(new RegisterDescriptor(v0, "v0",RegisterValType::  INT, int_reg)));
ins->setOpd1(new ConstOpd<int>(1));
pil.push_back(ins);
for(auto i = t.getInstlist().begin();i!=t.getInstlist().end();i++){
(*i)->setResult(new RegOpd(new RegisterDescriptor(a0, "a0",RegisterValType::  INT, int_reg)));
pil.push_back(*i);
}
OpCode o1=OpCode :: syscall;
InstructionFormat insf1=op;
InstructionDescriptor id1(o1,"syscall",insf1);
Instruction * ins1=new Instruction(id1);
pil.push_back(ins1);
TargetCodeForAst at(pil,new RegisterDescriptor(v0, "v0",RegisterValType:: INT, int_reg));
return at;
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

TargetCodeForAst & NameAst:: generateTargetCode(){
TargetCodeForAst t;
OpCode o=OpCode :: loadw;
InstructionFormat insf=op_r_o1;
InstructionDescriptor id(o,"lw",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(new RegisterDescriptor(v0, "v0",RegisterValType::  INT, int_reg)));
ins->setOpd1(new MemAddrOpd(getSymbolEntry()));
t.appendToInstList(ins);
t.setReg(new RegisterDescriptor(v0, "v0", RegisterValType:: INT, int_reg));
return t;
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

template <class T> TargetCodeForAst & NumberAst<T>:: generateTargetCode(){
TargetCodeForAst t;
OpCode o=OpCode::immloadw;
InstructionFormat insf=op_r_o1;
InstructionDescriptor id(o,"li",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(new RegisterDescriptor(v0, "v0", RegisterValType:: INT, int_reg)));
ins->setOpd1(new ConstOpd<T>(constant));
t.appendToInstList(ins);
t.setReg(new RegisterDescriptor(v0, "v0",RegisterValType::  INT, int_reg));
return t;
}

ReturnAst::ReturnAst(int line){
	lineNumber=line;
}

ReturnAst::~ReturnAst(){
}

void ReturnAst:: print(ostream& o){
	o<<"LINENUMBER: "<<"0"<<endl;
}

TargetCodeForAst & ReturnAst:: generateTargetCode(){

}
