#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "GraphFunc.c"
#include "Stack.h"

int main()
{
    int nodeAmount;
    Str16 inputFile;
    printf("Input filename: ");
    scanf("%s", inputFile);
    struct nodeTag *graph = getInput(inputFile, &nodeAmount);

    FILE *outputFile = fopen("TRAVERSAL.TXT", "w");

    if (graph != NULL)
    {

        Str16 startNode;
        printf("Input start vertex for the traversal: ");
        scanf("%s", startNode);
        if (getIndexGivenNodeToken(graph, startNode, nodeAmount) == -1)
        {
            printf("Vertex %s not found\n", startNode);
        }
        else
        {
            displayEdgeCount(graph, nodeAmount, outputFile);
            BFS(graph, nodeAmount, startNode, outputFile);
            DFS(graph, nodeAmount, startNode, outputFile);
        }
    }
    fclose(outputFile);
}
