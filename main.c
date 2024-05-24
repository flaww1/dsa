#include "graph.h"
#include <stdio.h>

int main() {
    int numberOfVertices = 5;  // Number of vertices in the graph
    Graph* graph = createGraph(numberOfVertices * numberOfVertices);

    // Load the matrix from the file and set connection rules
    const char* inputFilename = "matrix.txt";
    loadAndSetConnectionRules(graph, numberOfVertices, inputFilename);

    // Save the graph to a DOT file
    saveGraphToFile("graph.dot", graph);

    // Find the maximum sum path and print it
    int maxSum;
    Path* maxPath;
    findMaxSumPath(graph, &maxSum, &maxPath);
    printf("Max Path Sum: %d\n", maxSum);
    printf("Max Path: ");
    for (int i = 0; i < maxPath->length; i++) {
        printf("%d ", maxPath->vertices[i]);
    }
    printf("\n");

    // Free the allocated memory for the graph
    freeGraph(graph);

    return 0;
}
// New function combining loading the matrix and setting connection rules
void loadAndSetConnectionRules(Graph* graph, int numberOfVertices, const char* filename) {
    loadMatrix(graph, filename);
    setConnectionRules(graph, numberOfVertices);
}
