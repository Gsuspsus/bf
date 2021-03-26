#include<stdlib.h>
#include<stdbool.h>

#include "MachineModel.h"

machine_model* new_MM()
{
    machine_model* mm = (machine_model*)malloc(sizeof(machine_model));
    for(int i = 0; i < TAPE_SIZE;i++){
        mm->tape[i] = 0;
    }
    mm->data_pointer = &(mm->tape[0]);
    mm->jmp_fwd = 0;
    mm->jmp_bwd = 0;
    return mm;
}