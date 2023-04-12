#include <iostream>
#include <map>
using namespace std;
#include "Register.hh"
//#include "codegeneration.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
#include "ast.hh"
#include "machinedescription.hh"

Ast::Ast(){

}

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

TargetCodeForAst & Ast::generateTargetCode(){}

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
//cout<<"begin tg_Ass Ast.cpp"<<endl;
list<Instruction *> pil;
//cout<<"begin tg_Ass Ast.cpp"<<endl;
TargetCodeForAst t;
//cout<<"hi"<<endl;
t=rhs->generateTargetCode();
//cout<<"after"<<endl;
//cout<<"after tcg"<<endl;
OpCode o=OpCode::storew;
//cout<<"o"<<endl;
InstructionFormat insf=op_o1_r;
InstructionDescriptor id(o,"sw",insf);
Instruction * ins=new Instruction(id);
//cout<<"begin tg_Ass Ast.cpp"<<endl;
//new RegisterDescriptor(v0, "v0",RegisterValType:: INT, int_reg)
ins->setResult(new RegOpd(machineDes.spimRegTable[v0]));
//cout<<"begin tg_Ass Ast.cpp"<<endl;
SymbolTableEntry ste=lhs->getSymbolEntry();
//cout<<ste.getStartOffset()<<endl;
ins->setOpd1(new MemAddrOpd(ste));
pil.push_back(ins);
//cout<<"begin tg_Ass Ast.cpp"<<endl;
for(auto i = t.getInstlist().begin();i!=t.getInstlist().end();i++){
//i->setResult(new RegOpd(new RegisterDescriptor(a0, "a0", INT, intreg));
pil.push_back(*i);
}

TargetCodeForAst *at=new TargetCodeForAst(pil,machineDes.spimRegTable[v0]);
//cout<<"end tg_Ass Ast.cpp"<<endl;

return *at;
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
//cout<<"begin tg_print Ast.cpp"<<endl;
list<Instruction *> pil;
TargetCodeForAst t=(var->generateTargetCode());
OpCode o=OpCode :: immloadw;
InstructionFormat insf=op_r_o1;
//cout<<"insf: "<<insf<<endl;
InstructionDescriptor id(o,"li",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(machineDes.spimRegTable[v0]));
ins->setOpd1(new ConstOpd<int>(1));
pil.push_back(ins);
for(auto i = t.getInstlist().begin();i!=t.getInstlist().end();i++){
(*i)->setResult(new RegOpd(machineDes.spimRegTable[a0]));
pil.push_back(*i);
}
OpCode o1=OpCode :: syscall;
InstructionFormat insf1=op;
InstructionDescriptor id1(o1,"syscall",insf1);
Instruction * ins1=new Instruction(id1);
pil.push_back(ins1);
pil.reverse();
TargetCodeForAst *at=new TargetCodeForAst(pil,machineDes.spimRegTable[v0]);
//cout<<"end tg_print Ast.cpp"<<endl;
return *at;
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
//cout<<"begin tg_Name Ast.cpp"<<endl;
TargetCodeForAst *t=new TargetCodeForAst();
OpCode o=OpCode :: loadw;
InstructionFormat insf=op_r_o1;
InstructionDescriptor id(o,"lw",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(machineDes.spimRegTable[v0]));
ins->setOpd1(new MemAddrOpd(getSymbolEntry()));
//cout<<getSymbolEntry().getStartOffset()<<endl;
t->appendToInstList(ins);
t->setReg(machineDes.spimRegTable[v0]);
//cout<<"end tg_Name Ast.cpp"<<endl;
return *t;
}
/*
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
*/

ReturnAst::ReturnAst(int line){
	lineNumber=line;
}

ReturnAst::~ReturnAst(){
}

void ReturnAst:: print(ostream& o){
	o<<"LINENUMBER: "<<"0"<<endl;
}

TargetCodeForAst & ReturnAst:: generateTargetCode(){
//cout<<"begin tg_Return Ast.cpp"<<endl;
//cout<<"return"<<endl;
list<Instruction *> pil;

OpCode o=OpCode :: immloadw;
InstructionFormat insf=op_r_o1;
//cout<<"insf: "<<insf<<endl;
InstructionDescriptor id(o,"li",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(machineDes.spimRegTable[v0]));
ins->setOpd1(new ConstOpd<int>(0));
pil.push_back(ins);
//for(auto i = t.getInstlist().begin();i!=t.getInstlist().end();i++){
//(*i)->setResult(new RegOpd(new RegisterDescriptor(a0, "a0",RegisterValType::  INT, int_reg)));
//pil.push_back(*i);
//}
OpCode o2=OpCode :: move;
InstructionDescriptor id2(o2,"move",insf);
Instruction * ins2=new Instruction(id2);
ins2->setResult(new RegOpd(machineDes.spimRegTable[v1]));
ins2->setOpd1(new RegOpd(machineDes.spimRegTable[v0]));
pil.push_back(ins2);
OpCode o1=OpCode :: jump;
InstructionFormat insf1=op_st;
InstructionDescriptor id1(o1,"j",insf1);
Instruction * ins1=new Instruction(id1);
pil.push_back(ins1);
pil.reverse();
TargetCodeForAst *at=new TargetCodeForAst(pil,machineDes.spimRegTable[v0]);
//cout<<"end tg_Return Ast.cpp"<<endl;
return *at;
}
