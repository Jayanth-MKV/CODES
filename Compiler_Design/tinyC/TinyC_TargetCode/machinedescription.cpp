#include <iostream>
#include <map>
using namespace std;
#include "Register.hh"
#include "symboltable.hh"
#include "codegeneration.hh"
#include "machinedescription.hh"

void MachineDescriptor::initRegTable()
{
        spimRegTable[zero] = new RegisterDescriptor(zero, "zero", RegisterValType::INT, RegisterUseCategory ::fixed);
        spimRegTable[v0] = new RegisterDescriptor(v0, "v0", RegisterValType::INT, int_reg);
        spimRegTable[a0] = new RegisterDescriptor(a0, "a0", RegisterValType::INT, int_reg);
        spimRegTable[v1] = new RegisterDescriptor(v1, "v1", RegisterValType::INT, fn_result);
        spimRegTable[sp] = new RegisterDescriptor(sp, "sp", RegisterValType::INT, pointer);
        spimRegTable[fp] = new RegisterDescriptor(fp, "fp", RegisterValType::INT, pointer);
        spimRegTable[ra] = new RegisterDescriptor(ra, "ra", RegisterValType::INT, ret_address);
}

void MachineDescriptor::initInstTable()
{

        spimInstTable[OpCode::loadw] = new InstructionDescriptor(OpCode::loadw, "lw", op_r_o1);
        spimInstTable[OpCode::immloadw] = new InstructionDescriptor(OpCode::immloadw, "li", op_r_o1);
    spimInstTable[OpCode::storew] = new InstructionDescriptor(OpCode::storew, "sw", op_o1_r);
    spimInstTable[OpCode::add] = new InstructionDescriptor(OpCode::add, "add", op_r_o1_o2);
        spimInstTable[OpCode::sub] = new InstructionDescriptor(OpCode::sub, "sub", op_r_o1_o2);
    spimInstTable[OpCode::move] = new InstructionDescriptor(OpCode::move, "move", op_r_o1);
    spimInstTable[OpCode::syscall] = new InstructionDescriptor(OpCode::syscall, "syscall", op);
    spimInstTable[OpCode::jump] = new InstructionDescriptor(OpCode::jump, "j", op_st);
    spimInstTable[OpCode::jumpr] = new InstructionDescriptor(OpCode::jumpr, "jr", op_o1);
}


