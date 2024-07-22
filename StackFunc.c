#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TO Make a new Stack just declare a Stack pointer variable and init it to NULL

/*
void initStr20(Str20 s)
{
    for (int i = 0; i < 21; i++)
    {
        s[i] = '\0';
    }
}
*/
/*
void initStr2(Str2 s)
{
    for (int i = 0; i < 3; i++)
    {
        s[i] = '\0';
    }
}
*/

/*
    @param **stack: The pointer to the pointer of the stack that the data will be inserted into
    @param *c: the data that will be inserted into the stack: MUST BE a String
    @returns 0 if failed to push, 1 if pushed succesfully
*/
int Push(struct stackTag **stack, char *c)
{

    struct stackTag *newNode = malloc(sizeof(Stack)); // create new node
    initStr20(newNode->cToken);
    if (newNode == NULL)
    {
        return 0;
    }
    strcpy(newNode->cToken, c);

    newNode->nextNode = *stack; // store the previous head to the next of the new node
    *stack = newNode;           // store the newNode as the new head

    return 1;
}

/*
    @param *stack: The pointer to the pointer of the stack where the data will be extracted from
    @param *dest: The pointer to the destination string
    if stack is null, dest is empty string
*/
void Pop(struct stackTag **stack, char *dest)
{
    if (*stack == NULL)
    {
        strcpy(dest, "");
    }
    // get the char * from the head node
    if (*stack != NULL)
    {
        strcpy(dest, (*stack)->cToken);
        struct stackTag *tempNode = (*stack)->nextNode; // store the next node to a temp ptr
        free(*stack);                                   // free the current node
        *stack = tempNode;                              // store the temp node as the new current node
    }
}

/*
    @param *stack: The pointer to the stack where the data will be extracted from
    @param *dest: the pointer to the destination for where the top will be copied to
*/
void Top(struct stackTag *stack, char *dest)
{
    if (stack == NULL)
    {
        strcpy(dest, "");
    }
    else
    {
        strcpy(dest, stack->cToken);
    }
}

/*
    @param *stack: The pointer to the stack where the data will be extracted from
    @returns 1 when the stack is empty, 0 otherwise
*/
int StackEmpty(struct stackTag *stack)
{
    if (stack == NULL)
    {
        return 1;
    }

    return 0;
}

/*
    @param *stack: The pointer to the stack where the data will be extracted from
    @returns 1 when the stack is full, 0 otherwise
*/
int StackFull()
{
    if (malloc(sizeof(Stack)) == NULL)
    {
        return 1;
    }

    return 0;
}