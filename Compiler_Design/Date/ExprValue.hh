#include "Date.hh"
//Date expression value either int or date

enum ValueType { INT_VALUE, DATE_VALUE };

union Value {
    int number;
    Date *date;
};

class ExprValue {
public:
    union Value v;
    ValueType vt;

    ExprValue(){}
};

