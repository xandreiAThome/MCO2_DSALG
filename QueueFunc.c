#include <stdio.h>
#include <string.h>
#include "Queue.h"

void initStr20(Str20 str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = '\0';
    }
}

/*
@param *s: the data that will be inserted into the queue: MUST BE a String
@returns the new created node n
*/
struct qNodeTag *newNode(char *s)
{
    struct qNodeTag *n = malloc(sizeof(qNode)); // create new node
    initStr20(n->cToken);
    strcpy(n->cToken, s); // stores s to the new node
    n->nextNode = NULL;   // initializes the next node to NULL
    return n;
}

/*
@returns the created queue q
*/
struct queueTag *CreateQueue()
{
    struct queueTag *q = malloc(sizeof(Queue)); // create new queue
    q->head = NULL;                             // initialize to NULL
    q->tail = NULL;
    return q;
}

/*
@param *q the pointer to the queue thay the data will be inserted to
@param *in: the data that will be inserted into the queue: MUST BE a String
*/
void Enqueue(struct queueTag *q, char *in)
{
    struct qNodeTag *new = newNode(in);

    if (q->tail == NULL) // if empty
    {
        q->head = new; // assign the new node as head and tail
        q->tail = new;
    }
    new->nextNode = q->tail; // assign the tail as the nextNode of the new node
    q->tail->nextNode = new; // assign the new node as the tail's nextNode
    q->tail = new;           // assign the new node as the new tail
}

/*
@param *q the pointer to the queue thay the data will be inserted to
@param *dest: The pointer to the destination string
if head is null, dest is empty string
*/
void Dequeue(struct queueTag *q, char *dest)
{
    if (q->head == NULL) // if empty
    {
        strcpy(dest, "");
    }

    if (q->head == q->tail)
    {
        strcpy(dest, q->head->cToken); // store the token to a temporary variable
        free(q->head);                 // frees the memory in the head
        q->head = NULL;                // changes the head and tail to NULL
        q->tail = NULL;
    }

    struct qNodeTag *temp = q->head; // stores the head to a temporary node
    if (temp != NULL)
    {

        strcpy(dest, temp->cToken);  // accesses the token in temp (head) and stores it to tempChar
        q->head = q->head->nextNode; // assigns the nextNode as the new head
    }

    if (q->head == NULL)
    {
        q->tail = NULL; // if there is no head/element, tail becomes NULL
    }

    free(temp); // frees the memory in temp
}

/*
@param *q the pointer to the queue thay the data will be inserted to
@param *dest: The pointer to the destination string
if head is null, dest is empty string
*/
void QueueHead(struct queueTag *q, char *dest)
{
    if (q->head == NULL)
    {
        strcpy(dest, "");
    }
    else
    {
        strcpy(dest, q->head->cToken);
    }
}

/*
@param *q the pointer to the queue thay the data will be inserted to
@param *dest: The pointer to the destination string
if tail is null, dest is empty string
*/
void QueueTail(struct queueTag *q, char *dest)
{
    if (q->tail == NULL)
    {
        strcpy(dest, "");
    }
    else
    {
        strcpy(dest, q->tail->cToken);
    }
}

/*
@param *q the pointer to the queue thay the data will be inserted to
@returns 1 if the queue is empty, 0 if it is not
*/
int QueueEmpty(struct queueTag *q)
{
    if (q->head == NULL || q->tail == NULL) // if empty
    {
        return 1;
    }

    return 0;
}

/*
@param *q the pointer to the queue thay the data will be inserted to
@returns 1 if the queue is full, 0 if it is not
*/
int QueueFull(struct queueTag *q)
{
    if (malloc(sizeof(qNode)) == NULL) // if full
    {
        return 1;
    }

    return 0;
}
