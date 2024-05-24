#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <limits.h>

// Function to initialize a path
Path* initializePath(int length) {
    Path* path = (Path*)malloc(sizeof(Path));
    path->vertices = (int*)malloc(length * sizeof(int));
    path->length = 0;
    return path;
}

// Function to add a vertex to a path
Path* addToPath(Path* path, int vertex) {
    path->vertices[path->length++] = vertex;
    return path;
}

// Function to free memory allocated for a path
void freePath(Path* path) {
    free(path->vertices);
    free(path);
}

// Function to copy a path
Path* copyPath(Path* path) {
    Path* newPath = initializePath(path->length);
    for (int i = 0; i < path->length; i++) {
        addToPath(newPath, path->vertices[i]);
    }
    return newPath;
}

// Recursive function to find paths and maximum sum
Path*** findMaxSumPathRecursive(Graph* graph, int startVertex, int endVertex, int* visited, int currentSum, int* maxSum, Path* currentPath, Path*** allPathsPtr, int* allPathsCountPtr) {
    visited[startVertex] = 1;
    addToPath(currentPath, startVertex);
    Vertex* vertex = graph->vertices[startVertex];
    currentSum += vertex->value;

    if (startVertex == endVertex) {
        // Store the current path
        (*allPathsCountPtr)++;
        *allPathsPtr = realloc(*allPathsPtr, (*allPathsCountPtr) * sizeof(Path*));
        (*allPathsPtr)[*allPathsCountPtr - 1] = copyPath(currentPath);
        // Update maxSum if currentSum is greater
        if (currentSum > *maxSum) {
            *maxSum = currentSum;
        }
    } else {
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->edges[startVertex][i] && !visited[i]) {
                // Pass updated allPathsPtr recursively
                findMaxSumPathRecursive(graph, i, endVertex, visited, currentSum, maxSum, currentPath, allPathsPtr, allPathsCountPtr);
            }
        }
    }

    visited[startVertex] = 0;
    currentPath->length--; // Remove the last vertex from the path
    return allPathsPtr;
}


// Helper function to check if a path already exists in the list
bool pathExists(Path** paths, int count, Path* newPath) {
    for (int i = 0; i < count; i++) {
        if (paths[i]->length == newPath->length) {
            for (int j = 0; j < newPath->length; j++) {
                if (paths[i]->vertices[j] != newPath->vertices[j]) {
                    break;
                }
                if (j == newPath->length - 1) {
                    return true; // Path already exists
                }
            }
        }
    }
    return false;
}

void findMaxSumPath(Graph* graph, int* maxSum, Path** maxPath) {
    *maxSum = INT_MIN;
    *maxPath = NULL;

    Path** allPaths = NULL; // Initialize allPaths to NULL
    int allPathsCount = 0; // Initialize count to 0

    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (i != j) {
                Path* currentPath = initializePath(graph->numVertices);
                findMaxSumPathRecursive(graph, i, j, visited, 0, maxSum, currentPath, &allPaths, &allPathsCount);
                freePath(currentPath);
            }
        }
    }

    free(visited);

    printf("Maximum sum: %d\n", *maxSum);

    // Print all paths with their sums
    for (int i = 0; i < allPathsCount; i++) {
        printf("Path %d:\n", i + 1);
        for (int j = 0; j < allPaths[i]->length; j++) {
            printf("%d ", allPaths[i]->vertices[j]); // Print vertex index
            printf("(%d)\n", graph->vertices[allPaths[i]->vertices[j]]->value); // Print vertex value
        }
        printf("Sum: %d\n", calculatePathSum(allPaths[i], graph)); // Assuming `graph` is available here
    }

    // Free the allocated memory for allPaths
    for (int i = 0; i < allPathsCount; i++) {
        freePath(allPaths[i]);
    }
    free(allPaths);
}

int calculatePathSum(Path* path,
Graph* graph) {
    int sum = 0;
    for (int i = 0; i < path->length; i++) {
        sum += graph->vertices[path->vertices[i]]->value;
    }
    return sum;
}

// Adjusted createGraph to match the declaration in graph.h
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->vertices = (Vertex**)malloc(numVertices * sizeof(Vertex*));
    graph->edges = (Edge***)malloc(numVertices * sizeof(Edge**));
    for (int i = 0; i < numVertices; i++) {
    graph->vertices[i] = NULL;
    graph->edges[i] = (Edge**)malloc(numVertices * sizeof(Edge*));
    for (int j = 0; j < numVertices; j++) {
        graph->edges[i][j] = NULL; // Ensure this is initialized to NULL
    }
}

    return graph; // Return the graph pointer
}

// Add a vertex to the graph
Vertex* addVertex(Graph* graph, int vertexIndex, int value) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->value = value;
    newVertex->next = graph->vertices[vertexIndex];
    graph->vertices[vertexIndex] = newVertex;
    return newVertex;
}
// Correct addEdge to check if the destination vertex exists
Edge* addEdge(Graph* graph, int startVertex, int endVertex) {
    if (graph->vertices[endVertex]) {
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        newEdge->destination = graph->vertices[endVertex];
        newEdge->next = graph->edges[startVertex][endVertex];
        graph->edges[startVertex][endVertex] = newEdge;
        return newEdge;
    }
    return NULL;
}
// Correct removeVertex and removeEdge to check for null pointers
bool removeVertex(Graph* graph, int vertexIndex) {
    if (graph->vertices[vertexIndex]) {
        for (int i = 0; i < graph->numVertices; i++) {
            removeEdge(graph, vertexIndex, i);
        }
        free(graph->vertices[vertexIndex]);
        graph->vertices[vertexIndex] = NULL;
        return true;
    }
    return false;
}

// Function to remove an edge from the graph and return true if successful
bool removeEdge(Graph* graph, int startVertex, int endVertex) {
    if (graph->edges[startVertex][endVertex]) {
        free(graph->edges[startVertex][endVertex]);
        graph->edges[startVertex][endVertex] = NULL;
        return true;
    }
    return false;
}

// Load a matrix from a text file and populate the graph
bool loadMatrix(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return false;
    }
    
    char buffer[1024];
    int vertexIndex = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        char* token = strtok(buffer, ";");
        while (token) {
            int value = atoi(token);
            addVertex(graph, vertexIndex, value);
            token = strtok(NULL, ";");
            vertexIndex++;
        }
    }
    
    fclose(file);
    return true;
}

// Correct depthFirstSearch to explore all paths
void depthFirstSearch(Graph* graph, int startVertex, int endVertex, int* visited, int currentSum, int* maxSum) {
    visited[startVertex] = 1;
    Vertex* vertex = graph->vertices[startVertex];
    currentSum += vertex->value;
    
    if (startVertex == endVertex) {
        if (currentSum > *maxSum) {
            *maxSum = currentSum;
        }
    } else {
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->edges[startVertex][i] && !visited[i]) {
                depthFirstSearch(graph, i, endVertex, visited, currentSum, maxSum);
            }
        }
    }
    
    visited[startVertex] = 0;
}

// Implement breadthFirstSearch correctly
void breadthFirstSearch(Graph* graph, int startVertex, int endVertex, int* maxSum) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    int currentSum = 0;
    depthFirstSearch(graph, startVertex, endVertex, visited, currentSum, maxSum);
    free(visited);
}

// Free the memory allocated for the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Vertex* temp = graph->vertices[i];
        while (temp!= NULL) {
            Vertex* next = temp->next;
            free(temp);
            temp = next;
        }
        for (int j = 0; j < graph->numVertices; j++) {
            Edge* temp = graph->edges[i][j];
            while (temp!= NULL) {
                Edge* next = temp->next;
                free(temp);
                temp = next;
            }
        }
    }
    free(graph->vertices);
    free(graph->edges);
    free(graph);
}


void saveGraphToFile(const char* filename, Graph* graph) {
    FILE* dotFile = fopen(filename, "w");
    if (!dotFile) {
        perror("Failed to open DOT file");
        return;
    }

    fprintf(dotFile, "digraph G {\n");
    for (int i = 0; i < graph->numVertices; i++) {
        fprintf(dotFile, "%d [label=\"%d\"];\n", i, graph->vertices[i]->value); // Include vertex labels
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->edges[i][j]) {
                fprintf(dotFile, "%d -> %d;\n", i, j);
            }
        }
    }
    fprintf(dotFile, "}\n");
    fclose(dotFile);
}

void setConnectionRules(Graph* graph, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            int currentVertex = i * numVertices + j;

            if (j + 1 < numVertices) { // Right neighbor
                addEdge(graph, currentVertex, currentVertex + 1);
            }
            if (i + 1 < numVertices) { // Bottom neighbor
                addEdge(graph, currentVertex, currentVertex + numVertices);
            }
            // Add other connections as needed based on rules (e.g., diagonals)
        }
    }
}
