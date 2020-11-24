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
    int u = EdgeInfo[0] -1, v = EdgeInfo[1] -1, w = EdgeInfo[2]; //Adjust for 1 indexed elements
    node* headNode = new node(); //Head insertion
    headNode->vertex = v;
    headNode->weight = w;
    headNode->next = adjacencyList[u];
    adjacencyList[u] = headNode;
}

//Print entire graph
void graph::printGraph() {
    for(int i = 0; i < numVert; i++){
        std::cout << i + 1 << ": "; //Add 1 to adjust for 1 indexed nodes
        node* iter = adjacencyList[i];
        while (iter->next != nullptr){
            if(iter->next->next != nullptr)
                std::cout << "(" << iter->vertex + 1 << ", " <<  iter->weight << "); ";
            else
                std::cout << "(" << iter->vertex + 1 << ", " <<  iter->weight << ")";

            iter = iter->next;
        }
        std::cout << std::endl;
    }
}

