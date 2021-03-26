#ifndef MACHINE_MODEL_H
#define MACHINE_MODEL_H

#define TAPE_SIZE 30000

typedef struct machine_model 
{
    unsigned char  tape[TAPE_SIZE];
    unsigned char* data_pointer;
    bool           jmp_fwd; 
    bool           jmp_bwd; 
} machine_model;

machine_model* new_MM(void);

#endif