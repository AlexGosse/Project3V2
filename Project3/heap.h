//
// Created by Alex on 11/9/2020.
//

#ifndef PROJECT3_HEAP_H
#define PROJECT3_HEAP_H
#include "graph.h"
#include "util.h"

class MinHeap{
public:
    struct element{
        element(){}
        element(int vertex, int minDist) : vertex{vertex},  minDist{minDist} {} //Insertion of a regular element
        //element(int vertex, int predV, int weight, int minDist) : vertex{vertex}, predV{predV}, weight{weight}, minDist{minDist} {} //Insertion of the start element
        int vertex; //The current vertex
        int predV; //The predecessor of the current vertex
        int minDist; //Current known minimum distance to V, the head
    };

    //Returns the min - There must be at least 1 element in the heap to use
    int minimum();

    //Remove and return the min
    int extractMin();

    //Reduce the distance
    void decreaseKey(int index, int newMinDist);

    //Prints the heap
    void printHeap();

    //Create the heap from the adjacency list
    void makeHeap(graph *g, int startVertex);

    //Return the number of elements in the queue
    int numElements();

private:
    int n = 0; //Size of the heap
    element *heap = new element[1000];

    //Heapify using a bottom up approach for an insertion at a leaf
    void heapifyInsertion(int index);
    //Heapify top down after the head was changed for a leaf
    void heapifyDeletion(int index);
    //Calculate the total distance from node 1
    void setMinDist(int index);
    //Insert an element into the heap
    void insert(element elm);

};

#endif //PROJECT3_HEAP_H
