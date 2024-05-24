# Assignment: Graph-Based Maximum Sum Calculation

## Objective
Apply advanced concepts of graph theory and programming in C to solve a computational problem with a higher degree of complexity. This assignment aims to relate data structures, algorithms, and optimization techniques to develop a solution capable of calculating the maximum sum possible number of integers from an array of integers of arbitrary dimensions, considering specific rules of connection between integers.

## Features to Implement
1. Define a `GR` data structure to represent a graph. This structure must:
   - Support directed graphs.
   - Support a variable number of vertices.
   - Include functions for creating the graph, adding and removing vertices and edges.

2. Model the problem using graphs:
   - Each element of the array of integers will be represented by a vertex in the graph.
   - Edges between vertices represent a possibility of adding two elements adjacent to the matrix under specific connection rules defined by the user (e.g., elements in the same row or column, no diagonal connections).

3. Load data from a text file into the `GR` data structure:
   - The text file contains data from an array of constant integers.
   - Arrays of integers with any dimension, with values separated by commas.
   - Example format of the text file:
     ```
     7,53,183,439,863
     497,383,563,79,973
     287,63,343,169,583
     627,343,773,959,943
     767,473,103,699,303
     ```

4. Implement graph manipulation operations:
   - Including depth-first or breadth-first search to identify all possible paths meeting the defined connection rules.
   - Develop a function to calculate the sum of the vertex values on a given path.

5. Use structures and algorithms to find the path that provides the greatest sum possible of integers in the `GR` structure:
   - Obey the established connection rule.
   - Provide both the maximum sum and the path (or paths) that result in this sum.

## Documentation and Testing
- Extensively document the code, explaining the logic behind key functions and implementation decisions.
- Execute test cases with matrices of different dimensions and complexities, demonstrating the efficiency of the developed solution.

## Graph Visualization
![Graph](https://raw.githubusercontent.com/flaww1/dsa/main/graph.png)

The above image illustrates the graph representation of the problem statement. Each node represents an element of the array of integers, and edges represent connections between adjacent elements based on specific rules defined by the user.
