#include "Graph.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "QueueFunc.c"

/**
 * @brief Displays how many edges are connected to each node
 *
 * @param graph
 * @param nodeAmount
 * @param outputFile
 */
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

int getEdgeCount(struct nodeTag *graph, int nodeAmount, char *nodeName)
{
    for (int i = 0; i < nodeAmount; i++)
    {
        if (strcmp(graph[i].name, nodeName) == 0)
        {
            int k = 0;
            struct nodeTag *tempNode = graph[i].connectedNode;
            while (tempNode != NULL)
            {
                k++;
                tempNode = tempNode->connectedNode;
            }
            return k;
        }
    }

    return -1;
}

void initStr16(Str16 s)
{
    for (int i = 0; i < 17; i++)
    {
        s[i] = '\0';
    }
}

/**
 * @brief Initializes the graph data struct to empty
 *
 * @param graph
 * @param size
 */
void initGraph(struct nodeTag *graph, int size)
{
    for (int i = 0; i < size; i++)
    {
        initStr16(graph[i].name);
        graph[i].connectedNode = NULL;
    }
}

/**
 * @brief Get the Input graph from a given text file
 *
 * @param fileName
 * @param nodeQuanti pointer to an int, which will be assigned the number of nodes in the graph
 * @return struct nodeTag*
 */
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

/**
 * @brief Gives the order of visit for the breath first search
 *
 * @param graph
 * @param nodeQuanti
 * @param startNode
 * @param outputFile
 */
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

/**
 * @brief Get the Index Given Node Token object
 *
 * @param graph
 * @param nodeToken
 * @param nodeQuanti
 * @return  the index of the given node
 */
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

/**
 * @brief Converts string to lowercase
 *
 * @param str
 * @return new string
 */
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
*/

/**
 * @brief gives the order of visits for the depth first search
 *
 * @param graph
 * @param nodeQuanti
 * @param startNode
 * @param outputFile
 */

void DFS(struct nodeTag *graph, int nodeQuanti, char *startNode, FILE *outputFile, int visited[])
{

    int startIndex = getIndexGivenNodeToken(graph, startNode, nodeQuanti);
    visited[startIndex] = 1;
    printf("%s ", graph[startIndex].name);
    fprintf(outputFile, "%s ", graph[startIndex].name);

    struct nodeTag *nextNode = graph[startIndex].connectedNode;

    while (nextNode != NULL)
    {
        int neighborIndex = getIndexGivenNodeToken(graph, nextNode->name, nodeQuanti);
        if (!visited[neighborIndex])
        {
            DFS(graph, nodeQuanti, graph[neighborIndex].name, outputFile, visited);
        }
        nextNode = nextNode->connectedNode;
    }
}
