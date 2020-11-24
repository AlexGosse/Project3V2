#include <iostream>
#include <algorithm>
#include "heap.h"
#include "graph.h"
#include "util.h"

void Dijkstra(graph adjacencyList, int numOfVertices, int s, int e);
bool compare(MinHeap::element i, MinHeap::element j);

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

    Dijkstra(adjacencyList, n, startVertex, endVertex);

   return 0;
}

void Dijkstra(graph adjacencyList, int numOfVertices, int s, int e){ // s - Starting vertex, e - Ending vertex
    MinHeap::element* setS = new MinHeap::element[numOfVertices]; //Shortest path
    int setSize = 0;
    int shortestPathDistance = 0; //Distance of the shortest path through every element

    for(int i = 0; i < numOfVertices; i++) {
        setS[i] = MinHeap::element(-1, MAX_HEAP); //Default initialization
    }

    MinHeap q; //Priority queue q
    q.makeHeap(&adjacencyList, s); //Make the priority queue from the adjacency list, uses insert

    while(q.numElements() != 0){
        MinHeap::element u = q.extractMin();

        setS[setSize] = u;
        setSize++;
        shortestPathDistance += u.minDist;



        //For each successor vertex v adjacent to u do
        auto iter = adjacencyList.getIter(u.vertex);
        while(iter != nullptr && iter->vertex != -1){ //Loop through successors to uVertex
            q.relax(u, iter->vertex, iter->weight);
            iter = iter->next;
        }
        q.printHeap();
    }
    //Print set s
    for(int i = 0; i < numOfVertices; i++){
        std::cout << setS[i].vertex << ": " << setS[i].minDist << std::endl;
    }

    //std::sort(setS, setS + numOfVertices, compare);



    //Print shortest path
    //printShortestPath(s, e, setS, setSize);

}

bool compare(MinHeap::element i, MinHeap::element j){ return (i.vertex < j.vertex);}

