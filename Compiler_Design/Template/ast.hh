#ifndef AST_HH
#define AST_HH

//extern enum INT;

class Ast
{
protected:
	DataType nodeDataType;
	int lineNumber;

public:
	Ast();
	~Ast();

	virtual DataType getDataType();
	virtual bool typeCheckAst();
	virtual void print(ostream &) = 0;
        //functions added for code generation
        virtual TargetCodeForAst & generateTargetCode();
	virtual SymbolTableEntry & getSymbolEntry(){}
};

class AssignmentAst:public Ast
{
	Ast * lhs;
	Ast * rhs;

public:
	AssignmentAst(Ast *, Ast *, int);
	~AssignmentAst();
	bool typeCheckAst();
	void print(ostream & filebuffer);
        //functions added for code generation
        TargetCodeForAst & generateTargetCode();
};

class PrintAst:public Ast
{
     Ast *var;
public:
	PrintAst(Ast *, int);
	~PrintAst();
	void print(ostream & file_buffer);
        //functions added for code generation
        TargetCodeForAst & generateTargetCode();

};


class NameAst:public Ast
{
	SymbolTableEntry * variablesymbolentry;

public:
	NameAst(SymbolTableEntry &, int );
	~NameAst();
	DataType getDataType();
	SymbolTableEntry & getSymbolEntry();
	void print(ostream & filebuffer);
        //functions added for code generation
        TargetCodeForAst & generateTargetCode();

};

template <class T>
class NumberAst:public Ast
{
	T constant;

public:
	NumberAst(T, DataType, int);
	~NumberAst();

	DataType getDataType();

	void print(ostream &);
        //functions added for code generation
        TargetCodeForAst & generateTargetCode();

};

//template class NumberAst<int>;
//DataType NumberAst<int> :: getDatatype();

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
cout<<"begin tg_Number Ast.cpp"<<endl;
TargetCodeForAst *t=new TargetCodeForAst();
OpCode o=OpCode::immloadw;
InstructionFormat insf=op_r_o1;
InstructionDescriptor id(o,"li",insf);
Instruction * ins=new Instruction(id);
ins->setResult(new RegOpd(new RegisterDescriptor(v0, "v0", RegisterValType:: INT, int_reg)));
ins->setOpd1(new ConstOpd<int>(constant));
t->appendToInstList(ins);
t->setReg(new RegisterDescriptor(v0, "v0",RegisterValType::  INT, int_reg));
cout<<"end tg_Number Ast.cpp"<<endl; 
return *t;
}


class ReturnAst:public Ast
{

public:
	ReturnAst(int line);
	~ReturnAst();

	void print(ostream & filebuffer);
        //functions added for code generation
        TargetCodeForAst & generateTargetCode();
};

#endif
