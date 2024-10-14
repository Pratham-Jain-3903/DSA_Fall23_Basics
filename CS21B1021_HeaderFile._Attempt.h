#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// typedef enum {false,true} bool;  error
#define false 0
#define true 1

bool Select = false; // Declaration and initialization of boolean variables.
bool Insert_Node_status = false;
bool Insert_Edge_status = false;
bool Delete_Node_status = false;
bool Delete_Edge_status = false;
bool Search_status = false;

// store adjacency list nodes
struct Node
{
    int vertex;
    struct Node *next;
};

struct Node *createNode(int n);

struct graph
{
    int countVertex;
    struct Node **adjLists;
};

struct Node *createNode(int val)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->vertex = val;
    newNode->next = NULL;
    return newNode;
}

struct graph *Returner = malloc(sizeof(struct graph));

// create adjacency list from specified edges if Select is true (1)
void CreateGraph(bool Select)
{

    if (Select == true)
    {
        int vertices;
        scanf("%d", &vertices);

        struct graph *Graph = malloc(sizeof(struct graph));
        graph->countVertex = vertices;

        graph->adjLists = malloc(vertices * sizeof(struct node *));

        int i;
        for (i = 0; i < vertices; i++)
            graph->adjLists[i] = NULL;
    }

    else
    {
        int N, M; // no. of vertices and edges
        printf("enter no. of vertices, edges\n");
        scanf("%d %d", &N, &M);

        int arr[M][2];

        for (int j = 0; j < M; j++)
        {
            scanf("%d %d", &arr[j][0], &arr[j][1]);
        }

        // declaring and Adjacency Matrix by setting it to 0
        int Adj[N + 1][N + 1];

        for (int i = 0; i < N + 1; i++)
        {

            for (int j = 0; j < N + 1; j++)
            {
                Adj[i][j] = 0;
            }
        }

        for (int i = 0; i < M; i++)
        {

            // Finding X and Y of Edges
            int x = arr[i][0];
            int y = arr[i][1];

            // Updating value to 1
            Adj[x][y] = 1;
            Adj[y][x] = 1;
        }
    }
}

/*struct graph *CreateGraph(int vertices) //
{
    struct graph *Graph = malloc(sizeof(struct graph));
    graph->countVertex = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node *));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}*/
