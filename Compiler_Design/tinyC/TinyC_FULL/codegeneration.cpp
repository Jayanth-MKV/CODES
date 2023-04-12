#include <iostream>
using namespace std;
#include "Register.hh"
#include "symboltable.hh"
#include "codegeneration.hh"

InstructionDescriptor :: InstructionDescriptor (OpCode,string,InstructionFormat){}
InstructionDescriptor :: InstructionDescriptor(){}
OpCode InstructionDescriptor :: getOpCode(){ return op;}
string InstructionDescriptor :: getMnemonic(){return mnemonic;}
InstructionFormat InstructionDescriptor :: getInstFormat(){return InstructionFormat;}
void InstructionDescriptor :: print(ostream & o){
o<<mnemonic<<" ";
}


MemAddrOpd :: MemAddrOpd(SymbolTableEntry & se){symbolEntry=&se;}
MemAddrOpd :: MemAddrOpd(){}
void MemAddrOpd :: print(ostream & o ){
cout<<(symbolEntry->getStartOffset())<<"($fp)";
}
MemAddrOpd & MemAddrOpd ::  operator = (const MemAddrOpd mao){
	symbolEntry=mao.symbolEntry;
}

RegOpd :: RegOpd(RegisterDescriptor *rd){
	regDesc=rd;
}
RegisterDescriptor * RegOpd :: getReg(){
return regDesc;
}
void RegOpd :: print(ostream & o){
o<<regDesc->getName()<<", ";
}
RegOpd & RegOpd ::  operator=(const RegOpd & ro){
regDesc=ro.regDesc;
return *this;
}

template <class T > ConstOpd<T> :: ConstOpd(T a){
	num=T;
}

template <class T > ConstOpd<T> :: ~ConstOpd(){ }

template <class T > void  ConstOpd<T> :: print(ostream & o){ 
o<<num<<" ";
}



Instruction :: Instruction(InstructionDescriptor id){
	instDesc=id;
}

Instruction :: ~Instruction(){}

Opd* Instruction ::getOpd1(){return opd1;}

Opd * Instruction ::getOpd2(){return opd2;}

Opd * Instruction ::getResult(){return result;}

void Instruction ::setOpd1(opd * io){opd1=io;}

void Instruction ::setOpd2(Opd * io){opd2=io;}

void Instruction ::setResult(Opd * io){result=io;}

string Instruction ::getLabel(){return label;}

void Instruction ::setLabel(string s){label=s;}

void Instruction ::print(ostream & o){
o<<"\t"
InstructionFormat i = instDesc.getinstFormat();
switch(i){
case op_r_o1:	result->print(o);
		opd1->print(o);break;
case op_o1_r:	opd1->print(o);
		result->print(o);break;
case op:	opd1->print(o);
		break;
default:	cout<<"Invalid InsFormat"<<endl;

}
cout<<endl;
}

TargetCodeForAst ::TargetCodeForAst(){}
TargetCodeForAst ::~TargetCodeForAst(){}

TargetCodeForAst ::TargetCodeForAst(list<Instruction *> &li, RegisterDescriptor *rd){
	instList=li;
	result_Reg=rd;
}

void TargetCodeForAst ::appendToInstList(Instruction* i){
	instList.push_back(i);
}

list<Instruction *> TargetCodeForAst ::getInstlist(){
return instList;
}

void TargetCodeForAst ::setInstList(list<instList *> l){
instList=l;
}

RegisterDescriptor * TargetCodeForAst :: getReg(){return result_Reg;}
void TargetCodeForAst :: setReg(RegisterDescriptor* rd){
result_Reg=rd;
}
TargetCodeForAst & TargetCodeForAst :: operator=(const TargetCodeForAst & t){
TargetCodeForAst re;
re.instList=t.instList;
re.result_Reg=t.result_reg;
return re;
}
