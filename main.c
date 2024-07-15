#include "MCO2.h"
#include <stdio.h>
#include <stdlib.h>
#include "graph.c"

int main()
{
    struct nodeTag *graph = getInput("text/input.txt");

    printf("%s", graph[0].connectedNode->connectedNode->name);
}
