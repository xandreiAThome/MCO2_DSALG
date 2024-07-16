#ifndef MCO2_H_
#define MCO2_H_

typedef char Str20[21];

typedef struct qNodeTag
{
    Str20 cToken;
    struct qNodeTag *nextNode;
} qNode;

typedef struct queueTag
{
    struct qNodeTag *head;
    struct qNodeTag *tail;
} Queue;

struct qNodeTag *newNode(char *s);
struct queueTag *CreateQueue();
void Enqueue(struct queueTag *q, char *in);
void Dequeue(struct queueTag *q, char *dest);
void QueueHead(struct queueTag *q, char *dest);
void QueueTail(struct queueTag *q, char *dest);
int QueueEmpty(struct queueTag *q);
int QueueFull(struct queueTag *q);
void initStr20(Str20 str)

#endif