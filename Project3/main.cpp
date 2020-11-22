#include <iostream>
#include "heap.h"
#include "graph.h"
#include "util.h"

void Dijkstra(graph adjacencyList, int numOfVertices, int s);

int main() {
    int n;
    std::string temp = "";

    std::getline(std::cin, temp);
    n = std::stoi(temp); //Number of vertices in the graph

    std::getline(std::cin, temp);
    int m = std::stoi(temp); //Number of edges in the graph

    //Array of linked lists to store data
    graph adjacencyList(n, m);

    //m lines of code corresponding to the number of edges
    for(int i = 0; i < m; i++){
        std::getline(std::cin, temp);
        int* items = split(temp);
        adjacencyList.insertElement(items);
    }

    adjacencyList.printGraph();

    //Priority queue
    MinHeap h;

    int startVertex = 0; //Sample
    int endVertex = 3;

    Dijkstra(adjacencyList, n, startVertex);

//    h.makeHeap(&adjacencyList, startVertex);
//
//    std::cout << "Printing Heap" << std::endl;
//    h.printHeap();
//    //std::cout << "MIN: " << h.extractMin() << std::endl;
//    std::cout << "\nBefore heapify: " << std::endl;
//    h.extractMin();
//    h.decreaseKey(9, 9);
//    std::cout << "\nAfter heapify: " << std::endl;
//    h.printHeap();

   return 0;
}

void Dijkstra(graph adjacencyList, int numOfVertices, int s){ // s - Starting vertex
    int* shortestPath = new int[numOfVertices]; //Shortest path
    int shortestPathSize = 0;

    for(int i = 0; i < numOfVertices; i++)
        shortestPath[i] = -1; //Initialize vertices to -1 to indicate the path is empty

    MinHeap q; //Priority queue q
    q.makeHeap(&adjacencyList, s); //Make the priority queue from the adjacency list, uses insert

    std::cout << "Printing Heap" << std::endl;
    q.printHeap();

    while(q.numElements() != 0){
        int u = q.extractMin(); //Min distance, U NEEDS TO BE A VERTEX / element
        shortestPath[shortestPathSize] = u;
        shortestPathSize++;

        //Find


    }
}

