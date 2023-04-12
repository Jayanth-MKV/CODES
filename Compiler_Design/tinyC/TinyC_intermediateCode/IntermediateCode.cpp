#include <iostream>
using namespace std;
#include "Register.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
#include "IntermediateCode.hh"


Variable :: Variable(SymbolTableEntry * se){
    symbolEntry=se;
}

Variable::~Variable(){}

void Variable::print(ostream &o){
o<<symbolEntry->getVariableName();
}

Variable & Variable :: operator= (const Variable v){
    *this=v;
    return *this;
}


Quadruple :: Quadruple(Operand* a,Operand* b,Variable* c,ic::OpCode op){
    opd1=a;
    opd2=b;
    result=c;
    op=opCode;
}
Quadruple :: Quadruple(){}
Quadruple :: ~Quadruple(){}

Operand * Quadruple :: getOpd1(){
    return opd1;
}
Operand * Quadruple :: getOpd2(){
    return opd2;
}
Variable * Quadruple :: getResult(){
    return result;
}

void Quadruple :: setOpd1(Operand * a){
    opd1=a;
}
void Quadruple :: setOpd2(Operand *b){
    opd2=b;
}
void Quadruple :: setResult(Variable * c){
    result=c;
}

/*
ic::OpCode getOpCode(){
    return this->opCode;
}
*/

/*	
void Quadruple :: setNextInstAddr(Quadruple* q){

}
Quadruple* Quadruple :: getNextInstAddr(){

}
*/

void Quadruple :: print(ostream & o ){

//   cout<<"Quad run"<<endl; 
//   cout<<opCode<<endl;
   switch(opCode){
case 0:		if(opd2)
            opd2->print(o);
            o<<" : ";
            if(result)
            getResult()->print(o);
            else
            o<<"PRINT ";
            //cout<<opCode<<endl;
            o<<"=";
            if(opd1)
		    opd1->print(o);
            else
            o<<"NULL";
            o<<endl;
		    break;
case 1: o<<"\t";
		result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"+";
        opd2->print(o);
        o<<endl;
		break;
case 2:	o<<"\t";
        result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"-";
        opd2->print(o);
        o<<endl;
        break;
case 3: o<<"\t";
        result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"*";
        opd2->print(o);
        o<<endl;
		break;
case 4: o<<"\t";
        result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"/";
        opd2->print(o);
        o<<endl;
		break;
case 5: result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"&";
        opd2->print(o);
        o<<endl;	
		break;
case 6: result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"++";
        o<<endl;	
		break;
case 7: result->print(o);
        o<<"=";
	    opd1->print(o);
        o<<"--";
        o<<endl;	
		break;

case 8: result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<"<";
        opd2->print(o);
        o<<endl;
break;

case 9:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<"<=";
        opd2->print(o);
        o<<endl;
break;

case 10:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<">";
        opd2->print(o);
        o<<endl;
break;

case 11:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<">=";
        opd2->print(o);
        o<<endl;
break;

case 12:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<"==";
        opd2->print(o);
        o<<endl;
break;

case 13:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<"!=";
        opd2->print(o);
        o<<endl;
break;

case 14:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<"&&";
        opd2->print(o);
        o<<endl;
break;

case 15:result->print(o);
        o<<" : ";
	    opd1->print(o);
        o<<"||";
        opd2->print(o);
        o<<endl;
break;

case 16:
        o<<"!";
        opd1->print(o);
        o<<endl;
break;

case 17:opd2->print(o);
        o<<" : ";
        o<<"IF ";
        opd1->print(o);
	    o<<endl<<"\t THEN ";
        result->print(o);
        o<<endl;
break;

case 18://result->print(o);
        o<<"ELSE ";
	    opd1->print(o);
        o<<endl;
break;

case 19://result->print(o);
        o<<"GOTO ";
	    opd1->print(o);
        o<<endl;
break;
case 20://result->print(o);
        o<<"PRINT ";
	    opd1->print(o);
        o<<endl;
break;

default:	
            cout<<"Invalid ic format"<<endl;
		    break;
}
//cout<<"end quad run"<<endl;
}


IntermediateCodeForAst :: IntermediateCodeForAst(){}

IntermediateCodeForAst :: IntermediateCodeForAst(list<Quadruple*> &l){
    iCode=l;
}
IntermediateCodeForAst :: ~IntermediateCodeForAst(){}


void IntermediateCodeForAst :: appendToICode(Quadruple* q){
    iCode.push_back(q);
}
list<Quadruple *> & IntermediateCodeForAst :: getICode(){
    return iCode;
}
void IntermediateCodeForAst :: setICode(list<Quadruple *> l){
    iCode=l;
}

void IntermediateCodeForAst :: setSTE(SymbolTableEntry * se){
    symbolEntry=se;
}

SymbolTableEntry* IntermediateCodeForAst :: getSTE(){
    return symbolEntry;
}

IntermediateCodeForAst & IntermediateCodeForAst :: operator=(const IntermediateCodeForAst & ic){
    *this=ic;
    return *this;
}
