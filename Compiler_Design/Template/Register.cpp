#include <iostream>
using namespace std;
#include "Register.hh"

RegisterDescriptor::RegisterDescriptor (SpimRegister sr, string s, RegisterValType rvt, RegisterUseCategory rc){
reg=sr;
name=s;
valueType=rvt;
regUse=rc;
}


string RegisterDescriptor::getName(){return name;}

RegisterDescriptor::RegisterDescriptor(){}
