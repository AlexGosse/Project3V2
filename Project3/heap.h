//
// Created by Alex on 11/9/2020.
//

#ifndef PROJECT3_HEAP_H
#define PROJECT3_HEAP_H
#include "graph.h"
#include "util.h"

#define PREDV_SIZE 2000

class MinHeap{
public:
    struct element{
        element(){}
        element(int vertex, int minDist) : vertex{vertex},  minDist{minDist} { //Insertion of a regular element
            //Initialize predV to -1 to indicate emptiness
            for(int i = 0; i < PREDV_SIZE; i++){
                predV[i] = -1;
            }
            predVSize = 0;
        }
        int vertex; //The current vertex
        int predV[PREDV_SIZE]; //The predecessor of the current vertex
        int predVSize = 0;
        int minDist; //Current known minimum distance to V, the head
    };

    //Returns the min - There must be at least 1 element in the heap to use
    int minimum();

    //Remove and return the min
    int extractMin();

    //Return the vertex of the minimum node
    int minVertex();

    //Prints the heap
    void printHeap();

    //Create the heap from the adjacency list
    void makeHeap(graph *g, int startVertex);

    //Return the number of elements in the queue
    int numElements();

    //Get the size of the predV array
    int getPredVSize(int vertex){ return heap[vertex].predVSize; }

    //Check for a new min distance
    void relax(int uVertex, int uDistance, int vVertex, int vWeight);

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

    //Add another predecessor to an element
    void addPredecessor(int predecessor, int vertex);

    //Reduce the distance
    void decreaseKey(int index, int newMinDist);
};

#endif //PROJECT3_HEAP_H
