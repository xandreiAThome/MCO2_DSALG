#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "GraphFunc.c"

int main()
{
    int nodeAmount;
    struct nodeTag *graph = getInput("text/input.txt", &nodeAmount);

    printf("%s\n", graph[0].connectedNode->name);

    printf("%d\n", getIndexGivenNodeToken(graph, "HAL", nodeAmount));

    printf("%s\n", toLower("HELLOW WORLD"));
    BFS(graph, nodeAmount, "hal");
}
