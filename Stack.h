//#ifndef MCO2_H_
#define MCO2_H_

typedef char Str20[21];
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

void initStr20(Str20 s);
void initStr2(Str2 s);

//#endif