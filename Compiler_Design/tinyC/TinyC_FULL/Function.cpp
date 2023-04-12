#include <iostream>
using namespace std;
#include <sstream>
#include "Register.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
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

void Function :: generateTargetCode(){
	localSymbolTable.assignOffsetsToSymbols();
	//list<Instruction *> :: iterator it;
	for(auto i = statementList.begin();i!=statementList.end();i++){
		TargetCodeForAst tcfa = (*i)->generateTargetCode();
		instLlist.insert(instLlist.begin(),tcfa.getInstlist().begin(),tcfa.getInstlist().end());
	}

}


void Function::printPrologue(ostream & file_buffer)
{
        stringstream prologue;

        prologue << "\n\
        .text \t\t\t# The .text assembler directive indicates\n\
        .globl " << name << "\t\t# The following is the code (as oppose to data)\n";

        prologue << name << ":\t\t\t\t# .globl makes main know to the \n\t\t\t\t# outside of the program\
# Prologue begins \n\
        sw $ra, 0($sp)\t\t# Save the return address\n\
        sw $fp, -4($sp)\t\t# Save the frame pointer\n\
        sub $fp, $sp, 8\t\t# Update the frame pointer\n";

        int size = localSymbolTable.size();
        size = -size;
        prologue << "\n\tsub $sp, $sp, " << (size + 8) << "\t\t# Make space for the locals\n";
        prologue << "# Prologue ends\n\n";

        file_buffer << prologue.str();
}

void Function::printEpilogue(ostream & file_buffer)
{
        stringstream epilogue;

        int size = localSymbolTable.size();
        size = -size;

        epilogue << "\n# Epilogue Begins\nepilogue_" << name << ":\n\tadd $sp, $sp, " << (size+8) <<endl;
        epilogue << "\tlw $fp, -4($sp)  \n\tlw $ra, 0($sp)   \n\t";

        epilogue << "jr  $31\t\t# Jump back to the called procedure\n# Epilogue Ends\n\n";

        file_buffer << epilogue.str();
}

void Function::printTargetCode(ostream & file_buffer)
{
        printPrologue(file_buffer);

        list<Instruction *>::iterator i;
        for (i = instLlist.begin(); i != instLlist.end(); i++)
                (*i)->print(file_buffer);

        printEpilogue(file_buffer);
}



//../tinyCC -symtab test.tc
//-tokens next cat filename
