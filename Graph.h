#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>

typedef char Str16[17];
typedef char Str20[21];

typedef struct nodeTag
{
    Str16 name;
    struct nodeTag *connectedNode;
} Node;

void initStr16(Str16 s);
void initGraph(struct nodeTag *graph, int size);
struct nodeTag *getInput(char *fileName, int *nodeQuanti);
void BFS(struct nodeTag *graph, int nodeQuanti, char *startNode, FILE *outputFile);
int getIndexGivenNodeToken(struct nodeTag *graph, char *nodeTokenm, int nodeQuanti);
char *toLower(char *str);
void displayEdgeCount(struct nodeTag *graph, int nodeAmount, FILE *outputFile);
void DFS(struct nodeTag *graph, int nodeQuanti, char *startNode, FILE *outputFile);
#endif