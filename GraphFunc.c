#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

void initStr16(Str16 s)
{
    for (int i = 0; i < 17; i++)
    {
        s[i] = '\0';
    }
}

void initGraph(struct nodeTag *graph, int size)
{
    for (int i = 0; i < size; i++)
    {
        initStr16(graph[i].name);
        graph[i].connectedNode = NULL;
    }
}

struct nodeTag *getInput(char *fileName, int *nodeQuanti)
{
    FILE *inPtr;
    if ((inPtr = fopen(fileName, "r")) == NULL)
    {
        printf("File doesn't exist\n");
    }

    int nodeAmount;
    fscanf(inPtr, "%d\n", &nodeAmount);
    *nodeQuanti = nodeAmount;

    struct nodeTag *graph = malloc(sizeof(struct nodeTag) * nodeAmount);
    initGraph(graph, nodeAmount);

    char tempC = ' ';
    Str16 tempS = "";
    int index = 0;

    while (tempC != EOF)
    {
        tempC = fgetc(inPtr);
        if (tempC == ' ' || tempC == '\n')
        {
            if (strcmp(tempS, "-1") == 0)
            {
                index++;
            }
            else
            {
                if (strlen(graph[index].name) == 0)
                {
                    strcpy(graph[index].name, tempS);
                }
                else
                {
                    struct nodeTag *tempNode = &graph[index];
                    while (tempNode->connectedNode != NULL)
                    {
                        tempNode = tempNode->connectedNode;
                    }
                    struct nodeTag *newNode = malloc(sizeof(struct nodeTag));
                    strcpy(newNode->name, tempS);
                    newNode->connectedNode = NULL;
                    tempNode->connectedNode = newNode;
                }
            }

            initStr16(tempS);
        }
        else
        {
            tempS[strlen(tempS)] = tempC;
        }
    }

    return graph;
}

void BFS(struct nodeTag *graph)
{
}