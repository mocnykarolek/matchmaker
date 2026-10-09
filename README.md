# Hungarian Algorithm — Bipartite Graph Matching

A C++ implementation of the Hungarian algorithm for finding a maximum-weight matching in a weighted bipartite graph.

## Features

- Custom graph representation using adjacency lists
- Depth-first search (DFS) for graph traversal and partitioning
- Conversion of graph data into a dynamically allocated weight matrix
- Maximum-weight matching using the Hungarian algorithm
- Manual memory management using `malloc`, `calloc`, and `free`
- Support for multiple input instances

## Technologies

- C++
- Graph Algorithms
- Dynamic Memory Allocation
- Pointers and Linked Lists

## How It Works

The program reads a weighted graph, identifies its two vertex groups using DFS, and constructs a weight matrix. It then applies the Hungarian algorithm to calculate the maximum total matching weight.

## Compilation

```bash
g++ -std=c++11 matchmaker.cpp -o matchmaker
```

## Execution

```bash
./matchmaker < input.txt
```

The program reads the number of test cases, followed by the number of vertices, edges, and weighted edge definitions for each case.

## Purpose

This project demonstrates algorithm implementation, graph traversal, dynamic data structures, and explicit memory management in C++.
