#ifndef PROGRAM_HH
#define PROGRAM_HH


class Program
{
	SymbolTable globalSymbolTable;
	map<string, Function *> FunctionMap;

public:
	Program();
	~Program();
	Function * getFunctionDetails(string );
	void addFunctionDetails(string , Function *);
	void setFunctionMap(map<string, Function *> &);
	void setGlobalTable(SymbolTable &);
	SymbolTableEntry & getSymbolTableEntry(string);
	void printSymbolTable(ostream &o);
	void print(ostream &o);
	void printAst(ostream &o);
	Function * getMainFunction();
	bool variableFunctionNameCheck(string);
	bool variableInSymbolTableCheck(string);

        //functions added for code generation

        //void generateTargetCode();
    	//void printTargetCode(ostream &);

	//functions added for intermediate code generation

    void generateIntermediateCode();
    void printIntermediateCode(ostream & o);


};

#endif
