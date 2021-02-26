#ifndef MACHINE_MODEL_H
#define MACHINE_MODEL_H

#define TAPE_SIZE 30000

typedef struct MachineModelTag
{
    unsigned char  tape[TAPE_SIZE];
    unsigned char* data_pointer;
    bool           jmp_fwd; 
    bool           jmp_bwd; 
} MachineModel;

MachineModel* new_MM(void);

#endif