//
// Created by Alex on 11/9/2020.
//
#include <algorithm>
#include "util.h"
#define MAX_HEAP 2000000000 //Large number for a default min dist

//Split a string by spaces
int* split(std::string str){
    static int split[3];
    std::string temp = "";
    for(int i = 0, splitIndex = 0; i < str.length(); i++){
        if(str[i] != ' ')
            temp += str[i];
        else{
            split[splitIndex] = std::stoi(temp);
            splitIndex++;
            temp = "";
        }
    }
    split[2] = std::stoi(temp);

    return split;
}

MinHeap::element* Dijkstra(graph adjacencyList, int numOfVertices, int s){ // s - Starting vertex, e - Ending vertex
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
            //q.printHeap(); //TEST
            q.relax(u, iter->vertex, iter->weight);
            iter = iter->next;
        }
    }

    //Sort s by vertex
    std::sort(setS, setS + numOfVertices, compare);

    return setS;
}

bool compare(MinHeap::element i, MinHeap::element j){return i.vertex < j.vertex;}