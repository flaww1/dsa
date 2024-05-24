#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Name: Flávio Pereira
Number: 21110
Date: 24/05/2024
*/

/**
 * @file graph.h
 * Header file for graph-related functions and structures.
 */

/**
 * Structure to represent a path in the graph.
 * Each path consists of an array of vertex indices and a length.
 */
typedef struct {
    int* vertices; // Array to store vertex indices
    int length;    // Length of the path
} Path;

/**
 * Structure representing a vertex in the graph.
 * Each vertex contains a value and a pointer to the next vertex in the adjacency list.
 */
typedef struct Vertex {
    int value;      // Value associated with the vertex
    struct Vertex* next; // Pointer to the next vertex in the adjacency list
} Vertex;

/**
 * Structure representing an edge in the graph.
 * Each edge connects two vertices and contains a pointer to the destination vertex.
 */
typedef struct Edge {
    struct Vertex* destination; // Pointer to the destination vertex
    struct Edge* next;           // Pointer to the next edge in the adjacency list
} Edge;

/**
 * Structure representing the graph itself.
 * It includes the number of vertices, an array of pointers to vertices, and an array of arrays of pointers to edges.
 */
typedef struct Graph {
    int numVertices; // Number of vertices in the graph
    struct Vertex** vertices; // Array of pointers to vertices
    struct Edge*** edges;     // Array of arrays of pointers to edges
} Graph;

/**
 * @brief Creates a new graph with a specified number of vertices.
 * @param numVertices The number of vertices in the graph.
 * @return A pointer to the newly created graph.
 */
Graph* createGraph(int numVertices);

/**
 * @brief Copies a path.
 * @param path The original path to copy.
 * @return A new path that is a copy of the original.
 */
Path* copyPath(Path* path);

/**
 * @brief Adds a vertex to the graph with a specified value.
 * @param graph The graph to modify.
 * @param vertexIndex The index where the vertex should be added.
 * @param value The value of the vertex.
 * @return A pointer to the newly added vertex.
 */
Vertex* addVertex(Graph* graph, int vertexIndex, int value);

/**
 * @brief Adds an edge between two vertices in the graph.
 * @param graph The graph to modify.
 * @param startVertex The starting vertex of the edge.
 * @param endVertex The ending vertex of the edge.
 * @return A pointer to the newly added edge, or NULL if the operation fails.
 */
Edge* addEdge(Graph* graph, int startVertex, int endVertex);

/**
 * @brief Removes a vertex from the graph.
 * @param graph The graph to modify.
 * @param vertexIndex The index of the vertex to remove.
 * @return True if the vertex was successfully removed, false otherwise.
 */
bool removeVertex(Graph* graph, int vertexIndex);

/**
 * @brief Removes an edge from the graph.
 * @param graph The graph to modify.
 * @param startVertex The starting vertex of the edge.
 * @param endVertex The ending vertex of the edge.
 * @return True if the edge was successfully removed, false otherwise.
 */
bool removeEdge(Graph* graph, int startVertex, int endVertex);

/**
 * @brief Loads a graph from a text file.
 * @param graph The graph to populate.
 * @param filename The name of the file to load from.
 * @return True if the operation was successful, false otherwise.
 */
bool loadMatrix(Graph* graph, const char* filename);

/**
 * @brief Performs a depth-first search on the graph.
 * @param graph The graph to search.
 * @param startVertex The starting vertex of the search.
 * @param endVertex The ending vertex of the search.
 * @param visited An array indicating whether a vertex has been visited.
 * @param currentSum The current sum of the path.
 * @param maxSum Pointer to the maximum sum found so far.
 */
void depthFirstSearch(Graph* graph, int startVertex, int endVertex, int* visited, int currentSum, int* maxSum);

/**
 * @brief Performs a breadth-first search on the graph.
 * @param graph The graph to search.
 * @param startVertex The starting vertex of the search.
 * @param endVertex The ending vertex of the search.
 * @param currentSum Pointer to store the current sum of the path.
 */
void breadthFirstSearch(Graph* graph, int startVertex, int endVertex, int* currentSum);

/**
 * @brief Finds the maximum sum path in a graph.
 * @param graph The graph to search.
 * @param maxSum Pointer to store the maximum sum found.
 * @param maxPath Pointer to store the path with the maximum sum.
 */
void findMaxSumPath(Graph* graph, int* maxSum, Path** maxPath);

/**
 * @brief Frees the memory allocated for a graph.
 * @param graph The graph to free.
 */
void freeGraph(Graph* graph);

/**
 * @brief Saves the graph to a file in DOT format.
 * @param filename The name of the file to save to.
 * @param graph The graph to save.
 */
void saveGraphToFile(const char* filename, Graph* graph);

/**
 * @brief Sets connection rules for a grid graph.
 * @param graph The graph to configure.
 * @param numVertices The total number of vertices in the graph.
 */
void setConnectionRules(Graph* graph, int numVertices);

/**
 * @brief Checks if a path already exists in a list of paths.
 * @param paths The list of paths to check against.
 * @param count The number of paths in the list.
 * @param newPath The path to check for existence.
 * @return True if the path exists, false otherwise.
 */
bool pathExists(Path** paths, int count, Path* newPath);

/**
 * @brief Loads a graph from a text file and sets connection rules.
 * @param graph The graph to populate.
 * @param numberOfVertices The total number of vertices in the graph.
 * @param filename The name of the file to load from.
 * @return True if the operation was successful, false otherwise.
 */
bool loadAndSetConnectionRules(Graph* graph, int numberOfVertices, const char* filename);

/**
 * @brief Calculates the sum of a path.
 * @param path The path to calculate the sum of.
 * @param graph The graph containing the path.
 * @return The sum of the path.
 */
int calculatePathSum(Path* path, Graph* graph);

/**
 * @brief Finds the maximum sum path between two vertices in a graph using recursion.
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
Path*** findMaxSumPathRecursive(Graph* graph, int startVertex, int endVertex, int* visited, int currentSum, int* maxSum, Path* currentPath, Path*** allPathsPtr, int* allPathsCountPtr);

/**
 * @brief Adds a vertex to a path.
 * @param path The path to which the vertex should be added.
 * @param vertex The vertex to add.
 * @return The modified path.
 */
Path* addToPath(Path* path, int vertex);

#endif // GRAPH_H
