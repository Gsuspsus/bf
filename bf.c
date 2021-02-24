#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>


#define DATA_SIZE 30000

typedef struct 
{
    unsigned char  data[DATA_SIZE];
    unsigned char* data_pointer;
    bool           jmp_fwd; 
    bool           jmp_bwd; 
} MachineModel;

MachineModel* new_MM()
{
    MachineModel* mm = (MachineModel*)malloc(sizeof(MachineModel));
    for(int i = 0; i < DATA_SIZE;i++){
        mm->data[i] = 0;
    }
    mm->data_pointer = &(mm->data[0]);
    mm->jmp_fwd = 0;
    mm->jmp_bwd = 0;
    return mm;
}

void run_instruction(MachineModel* mm, char* code)
{
    switch(*code){
        case '>':
            ++mm->data_pointer;
            break;
        case '<':
            --mm->data_pointer;
            break;
        case '+':
            ++*mm->data_pointer;
            break;
        case '-':                    
            --*mm->data_pointer;
            break;
        case '.':
            printf("%c",*mm->data_pointer);
            break;
        case ',':
            *mm->data_pointer=getchar();
            break;
        case '[':
            if(*mm->data_pointer == 0){
                mm->jmp_fwd = true;
            }
            break;
        case ']':
            if(*mm->data_pointer != 0){
                mm->jmp_bwd = true;
            }
            break;
      default:
            break;
    }
}


int main(int argc, char* argv[])
{
    MachineModel* mm = new_MM();
    unsigned char* code;
    if(argc > 1){
        code = argv[1]; 
    }else{
        code = ",.[,.]";
    }
    while(*code){
       run_instruction(mm,code);
        if(mm->jmp_fwd){
            while(*code && *code != ']'){
                code++;
            }

            mm->jmp_fwd = false;
            continue;
        }

         if(mm->jmp_bwd){
            while(*code && *code != '['){
                code--;
            }

            mm->jmp_bwd = false;
            continue;
        }

        code++;
    }
    return 0;
}