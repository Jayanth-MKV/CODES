#ifndef CODE_GENERATION_HH
#define CODE_GENERATION_HH

enum class OpCode
{ 
        loadw,
        immloadw,
        storew,
        add,
        sub,
        move,
        syscall,
        jump,
        jumpr
};

typedef enum 
{               /* Instruction format; r: result; o1: opd1; op: operator */
        op_o1,  /* Only one operand, no result, eg. jr $ra */ 
        op_r_o1,        /* r <- o1, load,move*/
        op_o1_r,        /* r <- o1, store */
        op_r_o1_o2,     /* r <- o1 op o2, add, sub */
        op_st,       /* j string_label */
        op          /* only operation, syscall */
} InstructionFormat;



class InstructionDescriptor
{

        OpCode op;
        string mnemonic;
        InstructionFormat InsFormat;

public:
        InstructionDescriptor (OpCode,string,InstructionFormat);
        InstructionDescriptor();
        ~InstructionDescriptor();

        OpCode getOpCode();
        string getMnemonic();

        InstructionFormat getInstFormat();
 
        void print(ostream & file_buffer);
};
class Opd
{       
public:
        virtual RegisterDescriptor * getReg(){}
        virtual void print(ostream & file_buffer) = 0;
};

class MemAddrOpd:public Opd
{
        SymbolTableEntry *symbolEntry;

public:
        MemAddrOpd(SymbolTableEntry & se);
        ~MemAddrOpd();
        void print(ostream &);
        MemAddrOpd & operator= ( MemAddrOpd &);
	SymbolTableEntry * getsymbolEntry();
};

class RegOpd: public Opd
{
        RegisterDescriptor *regDesc;

public:
        RegOpd(RegisterDescriptor *rd);
        ~RegOpd() {}

        RegisterDescriptor *getReg();
        void print(ostream &);
        RegOpd & operator=(RegOpd &);
};

template <class T>
class ConstOpd: public Opd
{
        T num;

public:
        ConstOpd (T);
        ~ConstOpd();

        void print(ostream & file_buffer);
        ConstOpd & operator=(const ConstOpd);
};

template <class T > ConstOpd<T> :: ConstOpd(T a){
        num=a;
}

template <class T > ConstOpd<T> :: ~ConstOpd(){ }

template <class T > void  ConstOpd<T> :: print(ostream & o){ 
o<<num<<" ";
}


class Instruction
{
        Opd * opd1;   
        Opd * opd2;   
        Opd * result; 
        InstructionDescriptor instDesc;
        string  label; 
public:
        Instruction(InstructionDescriptor);
        ~Instruction();

        InstructionDescriptor & getInstDesc();
        Opd * getOpd1();
        Opd * getOpd2();
        Opd * getResult();
        string getLabel();

        void setOpd1(Opd * io);
        void setOpd2(Opd * io);
        void setResult(Opd * io);
        void setLabel(string);
        void print(ostream & );

};

class TargetCodeForAst
{
public:
        list<Instruction *> instList;
        RegisterDescriptor *result_Reg;


        TargetCodeForAst();
        TargetCodeForAst(list<Instruction *> &, RegisterDescriptor *);
        ~TargetCodeForAst();

        void appendToInstList(Instruction*);
        list<Instruction *> & getInstlist();
        void setInstList(list<Instruction *>);

        RegisterDescriptor * getReg();
        void setReg(RegisterDescriptor *);

        TargetCodeForAst & operator=(TargetCodeForAst &);
};
 #endif
