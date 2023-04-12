#ifndef MachineDescriptor_HH
#define MachineDescriptor_HH

class MachineDescriptor
{
public:
        map<Opcode, InstructionDescriptor *> spimInstTable;
        map<SpimRegister, RegisterDescriptor *> spimRegTable;

        void initInstTable();
        void initRegTable();

        RegisterDescriptor *getNewRegister();
};

extern MachineDescriptor machineDes;

#endif
