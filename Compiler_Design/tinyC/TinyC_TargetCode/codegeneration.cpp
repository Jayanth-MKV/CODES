#include <iostream>
using namespace std;
#include "Register.hh"
#include "symboltable.hh"
#include "codegeneration.hh"

InstructionDescriptor :: InstructionDescriptor (OpCode o,string s,InstructionFormat ifo){
op=o;
mnemonic =s ;
InsFormat=ifo;
}
InstructionDescriptor :: InstructionDescriptor(){}
InstructionDescriptor :: ~InstructionDescriptor(){}
OpCode InstructionDescriptor :: getOpCode(){ return op;}
string InstructionDescriptor :: getMnemonic(){return mnemonic;}
InstructionFormat InstructionDescriptor :: getInstFormat(){return InsFormat;}

void InstructionDescriptor :: print(ostream & o){
o<<mnemonic<<" ";
}

//RegisterDescriptor * Opd :: getReg(){}

MemAddrOpd :: MemAddrOpd(SymbolTableEntry & se){string s=se.getVariableName();
symbolEntry=new SymbolTableEntry(s,se.getDataType(),se.getLineNumber());
symbolEntry->setStartOffset(se.getStartOffset());
symbolEntry->setEndOffset(se.getEndOffset());
}
MemAddrOpd :: ~MemAddrOpd(){}
void MemAddrOpd :: print(ostream & o ){
o<<(symbolEntry->getStartOffset())<<"($fp)";
}

SymbolTableEntry * MemAddrOpd :: getsymbolEntry(){
return symbolEntry;
}


MemAddrOpd & MemAddrOpd ::  operator = ( MemAddrOpd& mao){
	symbolEntry=mao.getsymbolEntry();
	return *this;
}


RegOpd :: RegOpd(RegisterDescriptor *rd){
	regDesc=rd;
}
RegisterDescriptor * RegOpd :: getReg(){
return regDesc;
}
void RegOpd :: print(ostream & o){
o<<"$"<<regDesc->getName();
}
RegOpd & RegOpd ::  operator=(RegOpd & ro){
regDesc=ro.getReg();
return *this;
}

/*
template <class T > ConstOpd<T> :: ConstOpd(T a){
	num=a;
}

template <class T > ConstOpd<T> :: ~ConstOpd(){ }

template <class T > void  ConstOpd<T> :: print(ostream & o){ 
o<<num<<" ";
}
*/


Instruction :: Instruction(InstructionDescriptor id){
	instDesc=id;
}

Instruction :: ~Instruction(){}



Opd* Instruction ::getOpd1(){return opd1;}

Opd * Instruction ::getOpd2(){return opd2;}

Opd * Instruction ::getResult(){return result;}

void Instruction ::setOpd1(Opd * io){opd1=io;}

void Instruction ::setOpd2(Opd * io){opd2=io;}

void Instruction ::setResult(Opd * io){result=io;}

string Instruction ::getLabel(){return label;}

void Instruction ::setLabel(string s){label=s;}

void Instruction ::print(ostream & o){
o<<"\t";
//cout<<"Instruction"<<endl;
instDesc.print(o);
InstructionFormat i = instDesc.getInstFormat();
//cout<<i<<endl;
switch(i){
case 1:		result->print(o);o<<", ";
		opd1->print(o);
		break;
case 2:		//opd1->print(o);
		result->print(o);o<<", ";
		opd1->print(o);
		break;
case 4:		o<<"epilogue_main";
case 5: 	//opd1->print(o);
		//o<<"syscall";
		break;
default:	cout<<"Invalid InsFormat"<<endl;
		break;
}
o<<endl;
}

TargetCodeForAst ::TargetCodeForAst(){}
TargetCodeForAst ::~TargetCodeForAst(){}

TargetCodeForAst ::TargetCodeForAst(list<Instruction *>& li, RegisterDescriptor *rd){
	instList=li;
	result_Reg=rd;
}

void TargetCodeForAst ::appendToInstList(Instruction* i){
	instList.push_back(i);
}

list<Instruction *> & TargetCodeForAst ::getInstlist(){
//cout<<"get"<<endl;
return instList;
}

void TargetCodeForAst ::setInstList(list<Instruction *> l){
//instList=l;
for(auto i=l.begin();i!=l.end();i++){
//cout<<"i"<<endl;
instList.push_back(*i);
}
//cout<<"end sl"<<endl;
}

RegisterDescriptor * TargetCodeForAst :: getReg(){return result_Reg;}
void TargetCodeForAst :: setReg(RegisterDescriptor* rd){
result_Reg=rd;
}
TargetCodeForAst & TargetCodeForAst :: operator=(TargetCodeForAst & t){
//list<Instruction *> l(t.getInstlist());
//cout<<"in"<<endl;
/*for(auto i=t.getInstlist().begin();i!=t.getInstlist().end();i++){
cout<<"i"<<endl;
//instList.push_back(*i);
}
*/
//cout<<"after"<<endl;
//cout<<"before"<<endl;
//this->instList=t.instList;
for(auto i=t.instList.begin();i!=t.instList.end();i++){
//cout<<"i"<<endl;
this->instList.push_back(*i);
}

//cout<<"In op="<<endl;
this->result_Reg=t.result_Reg;
//cout<<"end op"<<endl;
return *this;
}
