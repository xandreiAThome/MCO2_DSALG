#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "Queue.h"
#include "QueueFunc.c"

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

void BFS(struct nodeTag *graph, int nodeQuanti, char *startNode)
{
    int visited[nodeQuanti];
    for (int i = 0; i < nodeQuanti; i++)
    {
        visited[i] = 0;
    }

    int startIndex = getIndexGivenNodeToken(graph, startNode, nodeQuanti);

    struct queueTag *queue = CreateQueue();
    visited[startIndex] = 1;
    Enqueue(queue, graph[startIndex].name);

    while (!QueueEmpty(queue))
    {
        Str16 currentNode = "";
        Dequeue(queue, currentNode);
        int currentIndex = getIndexGivenNodeToken(graph, currentNode, nodeQuanti);
        printf("%s, ", currentNode);

        struct nodeTag *tempNode = &graph[currentIndex];

        while (tempNode != NULL)
        {
            int neighborIndex = getIndexGivenNodeToken(graph, tempNode->name, nodeQuanti);
            if (!visited[neighborIndex])
            {
                visited[neighborIndex] = 1;
                Enqueue(queue, tempNode->name);
            }
            tempNode = tempNode->connectedNode;
        }
    }
}

int getIndexGivenNodeToken(struct nodeTag *graph, char *nodeToken, int nodeQuanti)
{
    for (int i = 0; i < nodeQuanti; i++)
    {
        if (strcmp(toLower(graph[i].name), toLower(nodeToken)) == 0)
        {
            return i;
        }
    }

    return -1;
}

char *toLower(char *str)
{
    char *lower = (char *)malloc(sizeof(char) * strlen(str));

    for (int i = 0; i < strlen(str); i++)
    {
        lower[i] = tolower(str[i]);
    }

    lower[strlen(str)] = '\0';

    return lower;
}