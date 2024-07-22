#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "Queue.h"
#include "QueueFunc.c"
#include "Stack.h"
#include "StackFunc.c"

void displayEdgeCount(struct nodeTag *graph, int nodeAmount, FILE *outputFile)
{
    for (int i = 0; i < nodeAmount; i++)
    {
        int k = 0;
        struct nodeTag *tempNode = graph[i].connectedNode;
        while (tempNode != NULL)
        {
            k++;
            tempNode = tempNode->connectedNode;
        }
        printf("%s \t%d\n", graph[i].name, k);
        fprintf(outputFile, "%s \t%d\n", graph[i].name, k);
    }
}

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
        return NULL;
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
    fclose(inPtr);

    return graph;
}

void BFS(struct nodeTag *graph, int nodeQuanti, char *startNode, FILE *outputFile)
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

    fprintf(outputFile, "\nBFS: ");
    printf("\nBFS: ");
    while (!QueueEmpty(queue))
    {
        Str16 currentNode = "";
        Dequeue(queue, currentNode);
        int currentIndex = getIndexGivenNodeToken(graph, currentNode, nodeQuanti);
        printf("%s ", currentNode);
        fprintf(outputFile, "%s ", currentNode);

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
    fprintf(outputFile, "\n");
    printf("\n");
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

/*
DFS = a search algorithm for traversing a tree or graph data structure
    1. Pick a route
    2. Keep going until you reach a dead end, or a perviously visited node
    3. Backtrack to last node that has unvisited adjacent neighbors

    Put the first node in the stack -> Push all the unvisited to the stack until it reaches a dead end or another visited -> Back track until it sees another node that has a unvisited adjacent -> Pop everything until the one with unvisited adjacent -> repeat
*/


void DFS(struct nodeTag *graph, int nodeQuanti, char *startNode, FILE *outputFile)
{
    Stack *s = NULL;
    
    int visited[nodeQuanti];
    for(int i = 0; i < nodeQuanti; i++){
        visited[i] = 0;
    }

    int startIndex = getIndexGivenNodeToken(graph, startNode, nodeQuanti);

    Push(&s, graph[startIndex].name);
    visited[startIndex] = 1;
    fprintf(outputFile, "\nDFS: ");
    printf("\nDFS: ");

    while (!StackEmpty(s))
    {
        Str16 currentNode = "";
        Pop(&s, currentNode);
        printf("%s ", currentNode);
        fprintf(outputFile, "%s ", currentNode);

        int currentIndex = getIndexGivenNodeToken(graph, currentNode, nodeQuanti);
        struct nodeTag *tempNode = &graph[currentIndex];

        while (tempNode->connectedNode != NULL)
        {
            int neighborIndex = getIndexGivenNodeToken(graph, tempNode->connectedNode->name, nodeQuanti);
            if (!visited[neighborIndex])
            {
                visited[neighborIndex] = 1;
                Push(&s, tempNode->connectedNode->name);
            }
            tempNode = tempNode->connectedNode;
        }
    }

    fprintf(outputFile, "\n");
    printf("\n");
}

/*
void DFS(struct nodeTag *graph, int nodeQuanti, char *startNode, FILE *outputFile)
{
    printf("%s ", graph[0].name);
    printf("%s \n", graph[0].connectedNode->name);

    printf("%s ", graph[1].name);
    printf("%s ", graph[1].connectedNode->name);
    printf("%s ", graph[1].connectedNode->connectedNode->name);

    printf("\n%s ", graph[2].name);
    printf("%s ", graph[2].connectedNode->name);

    printf("%s ", graph[3].name);
    printf("%s ", graph[2].connectedNode->name);


}
*/
