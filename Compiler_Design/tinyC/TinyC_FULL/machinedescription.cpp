

void MachineDescriptor::initRegTable()
{
        spimRegTable[zero] = new RegisterDescriptor(zero, "zero", INT, fixedreg);
        spimRegTable[v0] = new RegisterDescriptor(v0, "v0", INT, intreg);
        spimRegTable[v1] = new RegisterDescriptor(v1, "v1", INT, fnresult);
        spimRegTable[sp] = new RegisterDescriptor(sp, "sp", INT, pointer);
        spimRegTable[fp] = new RegisterDescriptor(fp, "fp", INT, pointer);
        spimRegTable[ra] = new RegisterDescriptor(ra, "ra", INT, retaddress);
}

void MachineDescriptor::initializeinstructiontable()
{

        spimInstTable[loadw] = new InstructionDescriptor(loadw, "lw", op_r_o1);
        spimInstTable[immloadw] = new InstructionDescriptor(immloadw, "li", op_r_o1);
    spimInstTable[storew] = new InstructionDescriptor(storew, "sw", op_o1_r);
    spimInstTable[add] = new InstructionDescriptor(add, "add", op_r_o1_o2);
        spimInstTable[sub] = new InstructionDescriptor(sub, "sub", op_r_o1_o2);
    spimInstTable[move] = new InstructionDescriptor(move, "move", op_r_o1);
    spimInstTable[syscall] = new InstructionDescriptor(syscall, "syscall", op);
    spimInstTable[jump] = new InstructionDescriptor(jump, "j", op_st);
    spimInstTable[jumpr] = new InstructionDescriptor(jumpr, "jr", op_o1);
}


