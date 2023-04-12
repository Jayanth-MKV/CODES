#ifndef AST_HH
#define AST_HH

//extern enum INT;
namespace ast{
typedef enum  
{
	INT,
	DOUBLE
}DataType;
}

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
        //virtual TargetCodeForAst & generateTargetCode();
	virtual IntermediateCodeForAst & generateIntermediateCode();
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
       //TargetCodeForAst & generateTargetCode();

	/* 
		The Target code for an assignment x = y  
		is a combination of load and store statements:
		(load) R <- y 
		(store) x <- R
          
          The Target code for an assignment x = 10  
		is a combination of immediate load and store statements:
		(immediateload) R <- 10 
		(store) x <- R

     */

     //function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();

};

class PrintAst:public Ast
{
     Ast *var;
public:
	PrintAst(Ast *, int);
	~PrintAst();
	void print(ostream & file_buffer);
        //functions added for code generation
        //TargetCodeForAst & generateTargetCode();

	//function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
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
    //TargetCodeForAst & generateTargetCode();
	//function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
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
        //TargetCodeForAst & generateTargetCode();

	//function added for intermediate code generation

    IntermediateCodeForAst & generateIntermediateCode();

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

template <class T> IntermediateCodeForAst& NumberAst<T> :: generateIntermediateCode(){
//	cout<<"Number ic"<<endl;
	list<Quadruple *> iCode;
	Quadruple * q = new Quadruple();
	q->setOpd1(new Constant<T>(constant));
	iCode.push_back(q);
	IntermediateCodeForAst * icfa = new IntermediateCodeForAst(iCode);
	return *icfa;
}

/*template <class T> TargetCodeForAst & NumberAst<T>:: generateTargetCode(){
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
*/


class ReturnAst:public Ast
{

public:
	ReturnAst(int line);
	~ReturnAst();

	void print(ostream & filebuffer);
        //functions added for code generation
        //TargetCodeForAst & generateTargetCode();
		//function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
};


//Added for intermediate code generation

class ExprAst:public Ast
{
protected:
	DataType nodeDataType;
	int lineNumber;
 public:
	ExprAst();
	~ExprAst();
    bool typeCheckAst();

	void print(ostream & filebuffer);

	//functions added for code generation
	//virtual TargetCodeForAst & generateTargetCode();
	//function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode(){}

};

typedef enum{
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	MOD,
	UNARYPLUS,
	UNARYMINUS
} ArithmeticOp;
class ArithmeticExprAst:public ExprAst
{
    Ast *l;
    Ast *r;
    ArithmeticOp aOp;
 public:
    ArithmeticExprAst(Ast *, Ast *,ArithmeticOp);

     bool typeCheckAst();
	void print(ostream & filebuffer);
	//functions added for code generation
	//virtual TargetCodeForAst & generateTargetCode();

	//function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
 
};

typedef enum{
	LESSTHAN,
	GREATERTHAN,
	EQUALTO,
	NOTEQUALTO,
	LESSTHANOREQUALTO,
	GREATERTHANOREQUALTO
}RelationalOp;

class RelationalExprAst:public ExprAst
{
    Ast *l;
    Ast *r;
    RelationalOp rOp;
 public:
     RelationalExprAst(Ast *, Ast *,RelationalOp);
     bool typeCheckAst();
	void print(ostream & filebuffer);
	//functions added for code generation
	//virtual TargetCodeForAst & generateTargetCode();
     //function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
};

typedef enum{
       AND,
       OR,
       NOT
}LogicalOp;

class LogicalExprAst:public ExprAst
{
    Ast *l;
    Ast *r;
    LogicalOp lOp;

 public:

    LogicalExprAst(Ast *, Ast *,LogicalOp);
    bool typeCheckAst();
    void print(ostream & filebuffer);

	//functions added for code generation
    //virtual TargetCodeForAst & generateTargetCode();

    //function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
 
};

class IfElseStmtAst:public Ast{
         Ast *cond;
         Ast  *ifPart;
         Ast   *elsePart;
   public:
    IfElseStmtAst(Ast *, Ast *,Ast *);
    bool typeCheckAst();
    void print(ostream & filebuffer);
	//functions added for code generation
    //virtual TargetCodeForAst & generateTargetCode();

    //function added for intermediate code generation

    virtual IntermediateCodeForAst & generateIntermediateCode();
   	
};

#endif
