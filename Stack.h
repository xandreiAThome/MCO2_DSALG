#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef char Str2[3];

typedef struct stackTag
{
    Str20 cToken;
    struct stackTag *nextNode;
} Stack;

/*
typedef struct qNodeTag
{
    Str20 cToken;
    struct qNodeTag *nextNode;
} qNode;
*/

int StackFull();
int StackEmpty(struct stackTag *stack);
void Top(struct stackTag *stack, char *dest);
void Pop(struct stackTag **stack, char *dest);
int Push(struct stackTag **stack, char *c);

// void initStr20(Str20 s);
// void initStr2(Str2 s);

#endif