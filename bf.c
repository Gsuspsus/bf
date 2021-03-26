#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MachineModel.h"

void run_instruction(machine_model *mm, char *code)
{
    switch (*code)
    {
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
        printf("%c", *mm->data_pointer);
        break;
    case ',':
        *mm->data_pointer = getchar();
        break;
    case '[':
        if (*mm->data_pointer == 0)
        {
            mm->jmp_fwd = true;
        }
        break;
    case ']':
        if (*mm->data_pointer != 0)
        {
            mm->jmp_bwd = true;
        }
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    machine_model *mm = new_MM();
    unsigned char *code;
    if (argc > 1)
    {
        code = argv[1];
    }
    else
    {
        code = ",.[,.]";
    }
    while (*code)
    {
        run_instruction(mm, code);
        if (mm->jmp_fwd)
        {
            while (*code && *code != ']')
            {
                code++;
            }

            mm->jmp_fwd = false;
            continue;
        }

        if (mm->jmp_bwd)
        {
            while (*code && *code != '[')
            {
                code--;
            }

            mm->jmp_bwd = false;
            continue;
        }

        code++;
    }
    return 0;
}