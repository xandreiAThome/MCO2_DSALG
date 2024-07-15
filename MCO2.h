#ifndef MCO2_H_
#define MCO2_H_

typedef char Str16[17];

typedef struct nodeTag
{
    Str16 name;
    struct nodeTag *connectedNode;
} Node;

#endif