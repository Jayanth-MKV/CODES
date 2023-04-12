#ifndef Function_HH
#define Function_HH

class Function
{
	DataType returnType;
	string name;
	SymbolTable localSymbolTable;
	list<Ast *> statementList;
	int lineno;
	
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
};
#endif
