

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @file graph.c
 * @brief Functions for managing graphs and finding paths within them.
 */

/*
Name: Flávio Pereira
Number: 21110
Date: 24/05/2024
*/

/**
 * Initializes a path with a given length.
 * @param length The length of the path.
 * @return A pointer to the newly allocated Path object.
 */
Path* initializePath(int length) {
    Path* path = (Path*)malloc(sizeof(Path));
    path->vertices = (int*)malloc(length * sizeof(int));
    path->length = 0;
    return path;
}

/**
 * Adds a vertex to a path.
 * @param path The path to which the vertex should be added.
 * @param vertex The vertex to add.
 * @return The modified path.
 */
Path* addToPath(Path* path, int vertex) {
    path->vertices[path->length++] = vertex;
    return path;
}

/**
 * Frees the memory allocated for a path.
 * @param path The path to free.
 */
void freePath(Path* path) {
    free(path->vertices);
    free(path);
}

/**
 * Copies a path.
 * @param path The original path to copy.
 * @return A new path that is a copy of the original.
 */
Path* copyPath(Path* path) {
    Path* newPath = initializePath(path->length);
    for (int i = 0; i < path->length; i++) {
        addToPath(newPath, path->vertices[i]);
    }
    return newPath;
}

/**
 * Finds the maximum sum path between two vertices in a graph using recursion.
 * @param graph The graph to search.
 * @param startVertex The starting vertex of the path.
 * @param endVertex The ending vertex of the path.
 * @param visited An array indicating whether a vertex has been visited.
 * @param currentSum The current sum of the path.
 * @param maxSum Pointer to the maximum sum found so far.
 * @param currentPath The current path being explored.
 * @param allPathsPtr Pointer to a list of all paths found.
 * @param allPathsCountPtr Pointer to the count of all paths found.
 * @return A pointer to the list of all paths found.
 */
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
            if (graph->edges[startVertex][i] &&!visited[i]) {
                // Pass updated allPathsPtr recursively
                findMaxSumPathRecursive(graph, i, endVertex, visited, currentSum, maxSum, currentPath, allPathsPtr, allPathsCountPtr);
            }
        }
    }

    // Decrement the length of currentPath to backtrack
    currentPath->length--;
    visited[startVertex] = 0; // Reset visited status after backtracking

    // Return the updated allPathsPtr
    return allPathsPtr;
}


/**
 * Checks if a path already exists in a list of paths.
 * @param paths The list of paths to check against.
 * @param count The number of paths in the list.
 * @param newPath The path to check for existence.
 * @return True if the path exists, false otherwise.
 */
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


/**
 * Finds the maximum sum path in a graph.
 * @param graph The graph to search.
 * @param maxSum Pointer to store the maximum sum found.
 * @param maxPath Pointer to store the path with the maximum sum.
 */
void findMaxSumPath(Graph* graph, int* maxSum, Path** maxPath) {
    *maxSum = INT_MIN;
    *maxPath = NULL;

    Path** allPaths = NULL; // Initialize allPaths to NULL
    int allPathsCount = 0; // Initialize count to 0

    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (i!= j) {
                Path* currentPath = initializePath(graph->numVertices);
                findMaxSumPathRecursive(graph, i, j, visited, 0, maxSum, currentPath, &allPaths, &allPathsCount);
                // Removed the logic for updating *maxSum and *maxPath here
            }
        }
    }

    free(visited);

    // Print all paths with their sums
    for (int i = 0; i < allPathsCount; i++) {
        printf("\nPath %d:\n", i + 1);
        printf("Vertices (Index - Value): ");
        for (int j = 0; j < allPaths[i]->length; j++) {
            printf("%d - (%d) ", allPaths[i]->vertices[j], graph->vertices[allPaths[i]->vertices[j]]->value); // Print vertex index and value
            if (j!= allPaths[i]->length - 1) {
                printf("-> ");
            }
        }
        printf("\nSum of path %d: %d\n", i + 1, calculatePathSum(allPaths[i], graph)); // Assuming `graph` is available here
    }

    // Check if maxPath is not NULL before printing
    if (*maxPath!= NULL) {
        printf("\nPath with Maximum Sum:\n");
        printf("Vertices (Index - Value): ");
        for (int j = 0; j < (*maxPath)->length; j++) {
            printf("%d - (%d) ", (*maxPath)->vertices[j], graph->vertices[(*maxPath)->vertices[j]]->value); // Print vertex index and value
            if (j!= (*maxPath)->length - 1) {
                printf("-> ");
            }
        }
        printf("\nSum of path with maximum sum: %d\n", *maxSum);
    } else {
        printf("\nNo path found.\n");
    }

    // Free the allocated memory for allPaths
    for (int i = 0; i < allPathsCount; i++) {
        freePath(allPaths[i]);
    }
    free(allPaths);
}

/**
 * Calculates the sum of a path.
 * @param path The path to calculate the sum of.
 * @param graph The graph containing the path.
 * @return The sum of the path.
 */
int calculatePathSum(Path* path,
Graph* graph) {
    int sum = 0;
    for (int i = 0; i < path->length; i++) {
        sum += graph->vertices[path->vertices[i]]->value;
    }
    return sum;
}

/**
 * Creates a graph with a specified number of vertices.
 * @param numVertices The number of vertices in the graph.
 * @return A pointer to the newly created graph.
 */
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

/**
 * Adds a vertex to the graph with a specified value.
 * @param graph The graph to modify.
 * @param vertexIndex The index where the vertex should be added.
 * @param value The value of the vertex.
 * @return A pointer to the newly added vertex.
 */
Vertex* addVertex(Graph* graph, int vertexIndex, int value) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->value = value;
    newVertex->next = graph->vertices[vertexIndex];
    graph->vertices[vertexIndex] = newVertex;
    return newVertex;
}


/**
 * Adds an edge between two vertices in the graph.
 * @param graph The graph to modify.
 * @param startVertex The starting vertex of the edge.
 * @param endVertex The ending vertex of the edge.
 * @return A pointer to the newly added edge, or NULL if the operation fails.
 */
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

/**
 * Removes a vertex from the graph.
 * @param graph The graph to modify.
 * @param vertexIndex The index of the vertex to remove.
 * @return True if the vertex was successfully removed, false otherwise.
 */
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

/**
 * Removes an edge from the graph.
 * @param graph The graph to modify.
 * @param startVertex The starting vertex of the edge.
 * @param endVertex The ending vertex of the edge.
 * @return True if the edge was successfully removed, false otherwise.
 */
bool removeEdge(Graph* graph, int startVertex, int endVertex) {
    if (graph->edges[startVertex][endVertex]) {
        free(graph->edges[startVertex][endVertex]);
        graph->edges[startVertex][endVertex] = NULL;
        return true;
    }
    return false;
}

/**
 * Loads a graph from a text file.
 * @param graph The graph to populate.
 * @param filename The name of the file to load from.
 * @return True if the operation was successful, false otherwise.
 */
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

/**
 * Performs a depth-first search on the graph.
 * @param graph The graph to search.
 * @param startVertex The starting vertex of the search.
 * @param endVertex The ending vertex of the search.
 * @param visited An array indicating whether a vertex has been visited.
 * @param currentSum The current sum of the path.
 * @param maxSum Pointer to the maximum sum found so far.
 */
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

/**
 * Performs a breadth-first search on the graph.
 * @param graph The graph to search.
 * @param startVertex The starting vertex of the search.
 * @param endVertex The ending vertex of the search.
 * @param maxSum Pointer to store the maximum sum found.
 */
void breadthFirstSearch(Graph* graph, int startVertex, int endVertex, int* maxSum) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    int currentSum = 0;
    depthFirstSearch(graph, startVertex, endVertex, visited, currentSum, maxSum);
    free(visited);
}

/**
 * Frees the memory allocated for a graph.
 * @param graph The graph to free.
 */
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

/**
 * Saves the graph to a file in DOT format.
 * @param filename The name of the file to save to.
 * @param graph The graph to save.
 */
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

/**
 * Sets connection rules for a grid graph.
 * @param graph The graph to configure.
 * @param numVertices The total number of vertices in the graph.
 */
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
