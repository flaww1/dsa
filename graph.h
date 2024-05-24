#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

// Structure to represent a path in the graph
typedef struct {
    int* vertices; // Array to store vertex indices
    int length;    // Length of the path
} Path;

// Define a structure for the graph
typedef struct Vertex {
    int value;
    struct Vertex* next;
} Vertex;

typedef struct Edge {
    struct Vertex* destination;
    struct Edge* next;
} Edge;

typedef struct Graph {
    int numVertices;
    struct Vertex** vertices;
    struct Edge*** edges;
} Graph;


// Function prototypes
Graph* createGraph(int numVertices);
Path* copyPath(Path* path);
Vertex* addVertex(Graph* graph, int vertexIndex, int value);
Edge* addEdge(Graph* graph, int startVertex, int endVertex);
bool removeVertex(Graph* graph, int vertexIndex);
bool removeEdge(Graph* graph, int startVertex, int endVertex);
bool loadMatrix(Graph* graph, const char* filename);
void depthFirstSearch(Graph* graph, int startVertex, int endVertex, int* visited, int currentSum, int* maxSum);
void breadthFirstSearch(Graph* graph, int startVertex, int endVertex, int* currentSum);
void findMaxSumPath(Graph* graph, int* maxSum, Path** maxPath);
void freeGraph(Graph* graph);
void saveGraphToFile(const char* filename, Graph* graph); // Added function prototype
void setConnectionRules(Graph* graph, int numVertices);
bool pathExists(Path** paths, int count, Path* newPath);
void loadAndSetConnectionRules(Graph* graph, int numberOfVertices, const char* filename);
int calculatePathSum(Path* path, Graph* graph);
Path*** findMaxSumPathRecursive(Graph* graph, int startVertex, int endVertex, int* visited, int currentSum, int* maxSum, Path* currentPath, Path*** allPathsPtr, int* allPathsCountPtr);
Path* addToPath(Path* path, int vertex);

#endif // GRAPH_H
