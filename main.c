#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "GraphFunc.c"

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

            int visited[nodeAmount];
            for (int i = 0; i < nodeAmount; i++)
            {
                visited[i] = 0;
            }
            fprintf(outputFile, "\nDFS: ");
            printf("\nDFS: ");
            DFS(graph, nodeAmount, startNode, outputFile, visited);
        }
    }
    fclose(outputFile);
}
