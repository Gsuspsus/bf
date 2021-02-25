#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAPE_SIZE 30000
#define PAIR_DEPTH_LIMIT 64

typedef enum
{
    LEFT,
    RIGHT
} Side;

typedef struct
{
    int pos;
    Side side;
    int depth;
} Bracket;

typedef struct
{
    unsigned char data[TAPE_SIZE];
    unsigned char *data_pointer;
    Bracket *pairs[PAIR_DEPTH_LIMIT];
    int current_pair_index;
} MachineModel;

MachineModel *new_MM()
{
    MachineModel *mm = (MachineModel *)malloc(sizeof(MachineModel));
    for (int i = 0; i < TAPE_SIZE; i++)
    {
        mm->data[i] = 0;
    }

    for (int i = 0; i < PAIR_DEPTH_LIMIT; i++)
    {
        mm->pairs[i] = NULL;
    }
    mm->data_pointer = &(mm->data[0]);
    mm->current_pair_index = 0;
    return mm;
}

void add_bracket_to_MM(MachineModel* mm, Bracket b){
    if(mm->current_pair_index >= PAIR_DEPTH_LIMIT){
        //error handling
    }

    mm->pairs[mm->current_pair_index++] = b;

}

Bracket *find_matching_bracket(MachineModel *mm, Bracket *bracket)
{
    for (int i = 0; i < PAIR_DEPTH_LIMIT; i++)
    {
        Bracket *to_be_matched = mm->pairs[i];
        if (to_be_matched->depth == bracket->depth)
        {
            return to_be_matched;
        }
    }
}

void run_instruction(MachineModel *mm, char *code, int pc)
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
            Bracket *match = find_matching_bracket(mm, mm->pairs[pc]);
            code = mm->pairs[pc]->pos;
        }
        break;
    case ']':
        if (*mm->data_pointer != 0)
        {
            Bracket *match = find_matching_bracket(mm, mm->pairs[pc]);
            code = mm->pairs[pc]->pos;
        }
        break;
    default:
        break;
    }
}

void run_program(MachineModel *mm, char *code)
{
    int pc = 0;
    while (*code)
    {
        run_instruction(mm, code, pc++);
        code++;
    }
}

void parse_program(MachineModel *mm, char *code)
{
    int depth = 0;
    int length = strlen(code);
    Bracket p;
    for (int i = 0; i < length; i++)
    {
        switch (code[i])
        {
        case '[':;
            p.pos = i;
            p.side = LEFT;
            p.depth = depth++;
            mm->pairs[i] = &p;
            break;
        case ']':;
            p.pos = i;
            p.side = RIGHT;
            p.depth = depth--;
            mm->pairs[i] = &p;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    MachineModel *mm = new_MM();
    unsigned char *code;
    if (argc > 1)
    {
        code = argv[1];
    }
    else
    {
        code = ",.[,.]";
    }

    parse_program(mm, code);

    for (int i = 0; i < PAIR_DEPTH_LIMIT; i++)
    {
        
    }

    run_program(mm, code);

    return 0;
}