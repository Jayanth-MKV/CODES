#include <iostream>
#include <map>
using namespace std;
#include "Register.hh"
//#include "codegeneration.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
#include "IntermediateCode.hh"
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

IntermediateCodeForAst & Ast :: generateIntermediateCode(){
}

//TargetCodeForAst & Ast::generateTargetCode(){}

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

IntermediateCodeForAst & AssignmentAst :: generateIntermediateCode(){
//	cout<<"Ass ic"<<endl;
	static int t_num=0;
		string t0="a"+to_string(t_num);
		t_num++;
	SymbolTableEntry * se = new SymbolTableEntry(t0,nodeDataType,lineNumber);
	list<Quadruple *> iCode;
	IntermediateCodeForAst ls=lhs->generateIntermediateCode();
	Quadruple * q = new Quadruple();
	q->setResult(new Variable(ls.getSTE()));
	//cout<<"--"<<ls.getSTE()->getVariableName()<<endl;
	
	IntermediateCodeForAst rs=rhs->generateIntermediateCode();
	if(rs.getSTE()){
	q->setOpd1(new Variable(rs.getSTE()));
	list<Quadruple *> ll=rs.getICode();
	for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    iCode.push_back(*i);
	}
	else
	q->setOpd1(rs.getICode().front()->getOpd1());
	q->setOpd2(new Variable(se));
	q->opCode=ic::ASSIGN;
	iCode.push_back(q);
//	cout<<"-- ";
//	q->getResult()->print(cout);
//	cout<<endl;
//	q->getOpd1()->print(cout);
//	cout<<" --"<<endl;

	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	icfa->setSTE(se);
	return *icfa;
}

	//for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    //iCode.push_back(*i);  
	//for (list<Quadruple *>::iterator i=rs.getICode().begin(); i!=rs.getICode().end(); i++)
    //iCode.push_back(*i); 
	//iCode.insert(iCode.begin(),rs.getICode().begin(),rs.getICode().end());
	//q->setResult(new Variable(variablesymbolentry));
	//icfa->setSTE(variablesymbolentry);

/*
TargetCodeForAst & AssignmentAst::generateTargetCode(){
cout<<"begin tg_Ass Ast.cpp"<<endl;
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
cout<<ste.getStartOffset()<<endl;
ins->setOpd1(new MemAddrOpd(ste));
pil.push_back(ins);
//cout<<"begin tg_Ass Ast.cpp"<<endl;
for(auto i = t.getInstlist().begin();i!=t.getInstlist().end();i++){
//i->setResult(new RegOpd(new RegisterDescriptor(a0, "a0", INT, intreg));
pil.push_back(*i);
}

TargetCodeForAst *at=new TargetCodeForAst(pil,machineDes.spimRegTable[v0]);
cout<<"end tg_Ass Ast.cpp"<<endl;

return *at;
}

*/

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

IntermediateCodeForAst & PrintAst :: generateIntermediateCode(){
//	cout<<"print ic"<<endl;
	//IntermediateCodeForAst * icfa = new IntermediateCodeForAst();
	//icfa->setSTE(&(var->getSymbolEntry()));
	list<Quadruple *> iCode;
	Quadruple * q = new Quadruple();
	q->setOpd1(new Variable(&var->getSymbolEntry()));
	q->opCode=ic::PRINT;
	iCode.push_back(q);
	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	return *icfa;	
}

/*

TargetCodeForAst & PrintAst::generateTargetCode(){
cout<<"begin tg_print Ast.cpp"<<endl;
list<Instruction *> pil;
TargetCodeForAst t=(var->generateTargetCode());
OpCode o=OpCode :: immloadw;
InstructionFormat insf=op_r_o1;
cout<<"insf: "<<insf<<endl;
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
cout<<"end tg_print Ast.cpp"<<endl;
return *at;
}
*/


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

IntermediateCodeForAst & NameAst :: generateIntermediateCode(){
	/*list<Quadruple *> iCode;
	Quadruple * q = new Quadruple();
	q->setResult(new Variable(variablesymbolentry));
	iCode.push_back(q);
	*/
//	cout<<"Name ic"<<endl;
	IntermediateCodeForAst * icfa = new IntermediateCodeForAst();
	icfa->setSTE(variablesymbolentry);
	//cout<<variablesymbolentry->getVariableName()<<endl;
	return *icfa;	
}

/*

TargetCodeForAst & NameAst:: generateTargetCode(){
cout<<"begin tg_Name Ast.cpp"<<endl;
TargetCodeForAst *t=new TargetCodeForAst();
OpCode o=OpCode :: loadw;
InstructionFormat insf=op_r_o1;
InstructionDescriptor id(o,"lw",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(machineDes.spimRegTable[v0]));
ins->setOpd1(new MemAddrOpd(getSymbolEntry()));
cout<<getSymbolEntry().getStartOffset()<<endl;
t->appendToInstList(ins);
t->setReg(machineDes.spimRegTable[v0]);
cout<<"end tg_Name Ast.cpp"<<endl;
return *t;
}
*/
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

IntermediateCodeForAst & ReturnAst :: generateIntermediateCode(){
//	cout<<"Return ic"<<endl;
	list<Quadruple *> iCode;
	Quadruple * q = new Quadruple();
	q->setOpd1(new Constant<int>(0));
	q->opCode=ic::GOTO;
	iCode.push_back(q);
	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	return *icfa;	
}

/*
TargetCodeForAst & ReturnAst:: generateTargetCode(){
cout<<"begin tg_Return Ast.cpp"<<endl;
cout<<"return"<<endl;
list<Instruction *> pil;

OpCode o=OpCode :: immloadw;
InstructionFormat insf=op_r_o1;
cout<<"insf: "<<insf<<endl;
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
cout<<"end tg_Return Ast.cpp"<<endl;
return *at;
}
*/

ExprAst :: ExprAst(){}
ExprAst :: ~ExprAst(){}

void ExprAst :: print(ostream & o){}


bool ExprAst :: typeCheckAst(){}

ArithmeticExprAst :: ArithmeticExprAst(Ast *a, Ast *b,ArithmeticOp c){
	l=a;
	r=b;
	aOp=c;
}

IntermediateCodeForAst & ArithmeticExprAst :: generateIntermediateCode(){
//	cout<<"ArithmeticExprAst ic"<<endl;
	static int t_num=0;
		string t0="t"+to_string(t_num);
		t_num++;
	list<Quadruple *> iCode;
		SymbolTableEntry * se = new SymbolTableEntry(t0,nodeDataType,lineNumber);
	Quadruple * q = new Quadruple();
		//q->setResult(new Variable(ls.getSTE()));
		IntermediateCodeForAst ls=l->generateIntermediateCode();
		if(ls.getSTE()){
		q->setOpd1(new Variable(ls.getSTE()));
		list<Quadruple *> ll=ls.getICode();
		for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    	iCode.push_back(*i);
		}
		else{
		q->setOpd1(ls.getICode().front()->getOpd1());
		}

	IntermediateCodeForAst rs=r->generateIntermediateCode();
	if(rs.getSTE()){
	q->setOpd2(new Variable(rs.getSTE()));
	list<Quadruple *> ll=rs.getICode();
	for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    iCode.push_back(*i);
	}
	else{
	q->setOpd2(rs.getICode().front()->getOpd1());
	}

	switch (aOp)
	{
	case 0:	q->opCode=ic::PLUS;
		break;
	case 1:	q->opCode=ic::MINUS;
		break;
	case 2: q->opCode=ic::MULTIPLY;
		break;
	case 3:	q->opCode=ic::DIVIDE;
		break;
	case 4:	q->opCode=ic::MOD;
		break;
	case 5:	q->opCode=ic::UNARYPLUS;
		break;
	case 6:	q->opCode=ic::UNARYMINUS;
		break;
	default:
		break;
	}

	q->setResult(new Variable(se));

	iCode.push_back(q);

	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	icfa->setSTE(se);
	return *icfa;

}
 
void ArithmeticExprAst :: print(ostream & o){
	o<<"Arith:"<<endl;
	o<<"\t\tLHS "<<"( ";
	l->print(o);
	o<<" )"<<endl;
	o<<"\t\t"<<aOp<<endl;
	o<<"\t\tRHS "<<"( ";
	r->print(o);
	o<<")"<<endl;
}

bool ArithmeticExprAst :: typeCheckAst(){

}

RelationalExprAst :: RelationalExprAst(Ast *a, Ast *b,RelationalOp c){
	l=a;
	r=b;
	rOp=c;
}

IntermediateCodeForAst & RelationalExprAst :: generateIntermediateCode(){
//	cout<<"RelationalExprAst ic"<<endl;
	static int t_num=0;
		string t0="t"+to_string(t_num);
		t_num++;
	list<Quadruple *> iCode;
		SymbolTableEntry * se = new SymbolTableEntry(t0,nodeDataType,lineNumber);
	Quadruple * q = new Quadruple();
		//q->setResult(new Variable(ls.getSTE()));
		IntermediateCodeForAst ls=l->generateIntermediateCode();
		if(ls.getSTE()){
		q->setOpd1(new Variable(ls.getSTE()));
		list<Quadruple *> ll=ls.getICode();
		for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    	iCode.push_back(*i);
		}
		else{
		q->setOpd1(ls.getICode().front()->getOpd1());
		}

	IntermediateCodeForAst rs=r->generateIntermediateCode();
	if(rs.getSTE()){
	q->setOpd2(new Variable(rs.getSTE()));
	list<Quadruple *> ll=rs.getICode();
	for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    iCode.push_back(*i);
	}
	else{
	q->setOpd2(rs.getICode().front()->getOpd1());
	}

	switch (rOp)
	{
	case 0:	q->opCode=ic::LESSTHAN;
		break;
	case 5:	q->opCode=ic::LESSTHANOREQUALTO;
		break;
	case 1: q->opCode=ic::GREATERTHAN;
		break;
	case 4:	q->opCode=ic::GREATERTHANOREQUALTO;
		break;
	case 2:	q->opCode=ic::EQUALTO;
		break;
	case 3:	q->opCode=ic::NOTEQUALTO;
		break;

	default:
		break;
	}

	q->setResult(new Variable(se));

	iCode.push_back(q);

	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	icfa->setSTE(se);
	return *icfa;

}
 
void RelationalExprAst :: print(ostream & o){
	o<<"RELATIONAL"<<endl;
	l->print(o);
	o<<"\t\t"<<rOp<<endl;
	r->print(o);
	o<<endl;
}

bool RelationalExprAst :: typeCheckAst(){

}

LogicalExprAst :: LogicalExprAst(Ast *a, Ast *b,LogicalOp c){
	l=a;
	r=b;
	lOp=c;
}

IntermediateCodeForAst & LogicalExprAst :: generateIntermediateCode(){
//	cout<<"LogicalExprAst ic"<<endl;
	static int t_num=0;
		string t0="t"+to_string(t_num);
		t_num++;
	list<Quadruple *> iCode;
		SymbolTableEntry * se = new SymbolTableEntry(t0,nodeDataType,lineNumber);
	Quadruple * q = new Quadruple();
		//q->setResult(new Variable(ls.getSTE()));
		IntermediateCodeForAst ls=l->generateIntermediateCode();
		if(ls.getSTE()){
		q->setOpd1(new Variable(ls.getSTE()));
		list<Quadruple *> ll=ls.getICode();
		for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    	iCode.push_back(*i);
		}
		else{
		q->setOpd1(ls.getICode().front()->getOpd1());
		}

	IntermediateCodeForAst rs=r->generateIntermediateCode();
	if(rs.getSTE()){
	q->setOpd2(new Variable(rs.getSTE()));
	list<Quadruple *> ll=rs.getICode();
	for (list<Quadruple *>::iterator i=ll.begin(); i!=ll.end(); i++)
    iCode.push_back(*i);
	}
	else{
	q->setOpd2(rs.getICode().front()->getOpd1());
	}

	switch (lOp)
	{
	case 0:	q->opCode=ic::AND;
		break;
	case 1:	q->opCode=ic::OR;
		break;
	case 2: q->opCode=ic::NOT;
		break;
	
	default:
		break;
	}

	q->setResult(new Variable(se));

	iCode.push_back(q);

	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	icfa->setSTE(se);
	return *icfa;
}
 
void LogicalExprAst :: print(ostream & o){
//	o<<"LOGICAL"<<endl;
	if(l)
	l->print(o);
	o<<"\t\t"<<lOp<<endl;
	r->print(o);
	o<<endl;
}

bool LogicalExprAst :: typeCheckAst(){

}

IfElseStmtAst :: IfElseStmtAst(Ast *a, Ast *b, Ast* c){
	cond=a;
	ifPart=b;
	elsePart=c;
}

IntermediateCodeForAst & IfElseStmtAst :: generateIntermediateCode(){
//	cout<<"IfElseStmt ic"<<endl;
	static int t_num=0;
		string t0="b"+to_string(t_num);
		t_num++;
		list<Quadruple *> iCode;
		SymbolTableEntry * se = new SymbolTableEntry(t0,nodeDataType,lineNumber);
		Quadruple * q1 = new Quadruple();

		IntermediateCodeForAst cs=cond->generateIntermediateCode();
		if(cs.getSTE()){
		q1->setOpd1(new Variable(cs.getSTE()));
		list<Quadruple *> ll=cs.getICode();
		for (list<Quadruple *>::reverse_iterator i=ll.rbegin(); i!=ll.rend(); i++)
    	iCode.push_back(*i);
		}
		else{
		q1->setOpd1(cs.getICode().front()->getOpd1());
		}

		q1->opCode=ic::IF;
		q1->setOpd2(new Variable(se));
		//q->setResult(new Variable(ls.getSTE()));

		IntermediateCodeForAst ls=ifPart->generateIntermediateCode();
		if(ls.getSTE()){
		//cout<<"down if"<<endl;
		q1->setResult(new Variable(ls.getSTE()));
		
		}
		else{
		q1->setOpd1(ls.getICode().front()->getOpd1());
		}

		iCode.push_back(q1);
		list<Quadruple *> ll=ls.getICode();
		for (list<Quadruple *>::reverse_iterator i=ll.rbegin(); i!=ll.rend(); i++)
    	iCode.push_back(*i);

	if(elsePart){
//		cout<<"in else part"<<endl;
		Quadruple *q=new Quadruple();
	IntermediateCodeForAst rs=elsePart->generateIntermediateCode();
	if(rs.getSTE()){
	q->setOpd1(new Variable(rs.getSTE()));
	
	}
	else{
	q->setOpd1(rs.getICode().front()->getOpd1());
	}

	q->opCode=ic::ELSE;

	iCode.push_back(q);
	list<Quadruple *> ll=rs.getICode();
	for (list<Quadruple *>::reverse_iterator i=ll.rbegin(); i!=ll.rend(); i++)
    iCode.push_back(*i);
	}
	iCode.reverse();
	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	icfa->setSTE(se);
//	cout<<"end ifelse stmt ic "<<endl;
	return *icfa;
}
 
void IfElseStmtAst :: print(ostream & o){
	o<<"IF"<<endl;
	cond->print(o);
	ifPart->print(o);
	if(elsePart){
	o<<"ELSE"<<endl;
	elsePart->print(o);
	}
	else
	o<<"NO ELSE";
	o<<endl;
}

bool IfElseStmtAst :: typeCheckAst(){

}
