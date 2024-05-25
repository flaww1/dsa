#include "graph.h"
#include <stdio.h>

/**
 * @mainpage Main Program for Graph Operations
 *
 * This program demonstrates various operations on a graph, such as creating a graph,
 * loading a matrix from a file, setting connection rules, saving the graph to a DOT file,
 * finding the maximum sum path, and freeing the allocated memory for the graph.
 */

/**
 * @brief Main function demonstrating graph operations.
 *
 * This function creates a graph, loads a matrix from a file, sets connection rules,
 * saves the graph to a DOT file, finds the maximum sum path, prints the result,
 * and frees the allocated memory for the graph.
 */
int main() {
    int numberOfVertices = 3;  // Number of vertices in the graph
    Graph* graph = createGraph(numberOfVertices * numberOfVertices);

    // Load the matrix from the file and set connection rules
    const char* inputFilename = "matrix.txt";
    loadAndSetConnectionRules(graph, numberOfVertices, inputFilename);

    // Save the graph to a DOT file
    saveGraphToFile("graph.dot", graph);

    // Find the maximum sum path
    int maxSum;
    Path* maxPath;
    findMaxSumPath(graph, &maxSum, &maxPath);

    // Free the allocated memory for the graph
    freeGraph(graph);

    return 0;
}

/**
 * @brief Combines loading a matrix from a file and setting connection rules for a graph.
 *
 * This function takes a graph, the number of vertices, and a filename as inputs.
 * It first calls loadMatrix to load the graph's matrix from the specified file.
 * Then, it calls setConnectionRules to apply the connection rules based on the number of vertices.
 * This simplifies the process of initializing a graph with a predefined matrix and connection rules.
 *
 * @param graph The graph to be loaded and configured.
 * @param numberOfVertices The total number of vertices in the graph.
 * @param filename The name of the file containing the matrix to load.
 */
bool loadAndSetConnectionRules(Graph* graph, int numberOfVertices, const char* filename) {
    loadMatrix(graph, filename);
    setConnectionRules(graph, numberOfVertices);
}
