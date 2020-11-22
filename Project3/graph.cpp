//
// Created by Alex on 11/9/2020.
//

#include "graph.h"

//Constructor given number of vertices
graph::graph(int n, int m) {
    numVert = n;
    numEdge = m;
    adjacencyList = new node*[n];
    //Initialize adjacency list
    for (int i = 0; i < n; i++) {
        adjacencyList[i] = newNode();
    }
}

//Default values for a node
graph::node* graph::newNode(){
    node *newNode = new node;
    newNode->weight = -1;
    newNode->vertex = -1;
    newNode->next = nullptr;
    return newNode;
}

//Insert a new element into the graph
void graph::insertElement(int* EdgeInfo){
    int u = EdgeInfo[0], v = EdgeInfo[1], w = EdgeInfo[2];
    node* headNode = new node(); //Head insertion
    headNode->vertex = v;
    headNode->weight = w;
    headNode->next = adjacencyList[u];
    adjacencyList[u] = headNode;
}

//Print entire graph
void graph::printGraph() {
    for(int i = 0; i < numVert; i++){
        std::cout << i << " ";
        node* iter = adjacencyList[i];
        while (iter->next != nullptr){
            std::cout << "(" << iter->vertex << ", " <<  iter->weight << ") ";
            iter = iter->next;
        }
        std::cout << std::endl;
    }
}

