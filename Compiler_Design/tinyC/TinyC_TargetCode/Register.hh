#ifndef Register_HH
#define Register_HH

typedef enum
{
        zero,
        v0,
        v1,
	a0,
        fp,
        sp,
        ra
} SpimRegister;

 enum class RegisterValType 
{ 
        INT
};

typedef enum 
{ 
        fixed, 
        int_reg, 
        fn_result, 
        pointer, 
        ret_address,
} RegisterUseCategory;




class RegisterDescriptor
{
    SpimRegister reg;
    string name;
    RegisterValType valueType;
    RegisterUseCategory regUse; 

    bool regOccupied;
  public:
    RegisterDescriptor (SpimRegister, string, RegisterValType, RegisterUseCategory);
    RegisterDescriptor();
    ~RegisterDescriptor() {}

    
    RegisterUseCategory getUseCategory(); 
    SpimRegister getRegister();

    string getName();

    bool isRegisterOccupied();
    void setRegisterOccupied();
    void resetRegisterOccupied();
};

#endif
