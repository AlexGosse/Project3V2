//
// Created by Alex on 11/9/2020.
//
#include <iostream>

#ifndef PROJECT3_UTIL_H
#define PROJECT3_UTIL_H
#include "graph.h"
#include "heap.h"

//Dijkstra algorithm
MinHeap::element* Dijkstra(graph adjacencyList, int numOfVertices, int s);

//Split a string by spaces into 3 parts
int* split(std::string str);

bool compare(MinHeap::element i, MinHeap::element j);

#endif //PROJECT3_UTIL_H
