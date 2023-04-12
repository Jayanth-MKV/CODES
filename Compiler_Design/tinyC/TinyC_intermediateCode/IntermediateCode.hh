#ifndef INTERMEDIATE_CODE_HH
#define INTERMEDIATE_CODE_HH

namespace ic
{

typedef enum{
   ASSIGN,
   PLUS,
   MINUS,
   MULTIPLY,
   DIVIDE,
   MOD,
   UNARYPLUS,
   UNARYMINUS,
   LESSTHAN,
   LESSTHANOREQUALTO,
   GREATERTHAN,
   GREATERTHANOREQUALTO,
   EQUALTO,
   NOTEQUALTO,
   AND,
   OR,
   NOT,
   IF,
   ELSE,
   GOTO,
   PRINT
}OpCode;
}

class Operand
{	
public:
	virtual void print(ostream & file_buffer) = 0;
};

class Variable:public Operand
{
	SymbolTableEntry *symbolEntry;

public:
	Variable(SymbolTableEntry * );
	~Variable();
	void print(ostream &);
	Variable & operator= (const Variable);
};

template <class T>
class Constant: public Operand
{
	T num;

public:
	Constant (T);
	~Constant();

	void print(ostream & fileBuffer);
	Constant & operator=(const Constant);
};

template <class T> Constant<T> :: Constant(T n){
    num=n;
}

template <class T> Constant<T> :: ~Constant(){}

template <class T> void Constant<T> :: print(ostream &o){
o<<num;
}

class Quadruple;
class Quadruple
{
	Operand *opd1;   
	Operand *opd2;   
	Variable *result;

//used in case conditinal or unconditional goto
	Quadruple *nextInstAddr;

public:
	ic::OpCode  opCode;  
	Quadruple();
	Quadruple(Operand*,Operand*,Variable*,ic::OpCode);
	~Quadruple();  

	InstructionDescriptor & getInstDesc();
	Operand * getOpd1();
	Operand * getOpd2();
	Variable * getResult();
	//ic::OpCode getOpCode();
	void setOpd1(Operand *);
	void setOpd2(Operand *);
	void setResult(Variable *);

	void setNextInstAddr(Quadruple*);
	Quadruple* getNextInstAddr();
	void print(ostream & );
};

class IntermediateCodeForAst
{
   list<Quadruple *> iCode;

   // symbol entry of result variable
   SymbolTableEntry *symbolEntry;

public:

	IntermediateCodeForAst();
	IntermediateCodeForAst(list<Quadruple *> &);
	~IntermediateCodeForAst();

	void appendToICode(Quadruple*);
	list<Quadruple *> & getICode();
	void setICode(list<Quadruple *>);
	void setSTE(SymbolTableEntry *);
	SymbolTableEntry* getSTE();
	IntermediateCodeForAst & operator=(const IntermediateCodeForAst &);
};

#endif