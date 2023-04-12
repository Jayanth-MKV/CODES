#ifndef Function_HH
#define Function_HH

class Function
{
	DataType returnType;
	string name;
	SymbolTable localSymbolTable;
	list<Ast *> statementList;
	int lineno;

	//datamember added for code generation
        list<Instruction *> instLlist;

	//datamember added for Intermediate code geneartion
	list<Quadruple*> iCode;

public:
	Function();
	Function(DataType, string, int);
	~Function();
	void setfunctionname(string);
	void setdatatype(DataType);
	string getFunctionName();
	void setLocalList(SymbolTable &);
	SymbolTable getLocalList();
	void setAstList(list<Ast *> &);
	DataType getReturnType();
	void setReturnType(DataType);
	SymbolTableEntry & getSymbolTableEntry(string);
	void print(ostream &);
	void printSymbolTable(ostream &);
	list<Ast*> getAstlist();

    //functions added for code generation
        //void generateTargetCode();
       // void printTargetCode(ostream &);
        void printPrologue(ostream &);
        void printEpilogue(ostream &);

	//functions added for intermediate code generation

    void generateIntermediateCode();
    void printIntermediateCode(ostream &);

};
#endif
