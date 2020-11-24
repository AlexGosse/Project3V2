//
// Created by Alex on 11/9/2020.
//

#ifndef PROJECT3_HEAP_H
#define PROJECT3_HEAP_H
#include "graph.h"
#include "util.h"

#define PREDV_SIZE 20000
#define BEST_PRED_START -1
#define BEST_PRED_NOT_REACHED -2

class MinHeap{
public:
    struct element{
        element(){}
        element(int vertex, int minDist) : vertex{vertex},  minDist{minDist} { //Insertion of a regular element
            //Initialize predV to -1 to indicate emptiness
            for(int i = 0; i < PREDV_SIZE; i++){
                predV[i] = BEST_PRED_START;
            }
            predVSize = 0;
        }
        int vertex; //The current vertex
        int predV[PREDV_SIZE]; //The predecessors of the current vertex
        int predVSize = 0;
        int minDist; //Current known minimum distance to V, the head
        int bestPred = BEST_PRED_START; //Used in relax, the correct predecessor for the optimal path
    };

    //Remove and return the min
    element extractMin();

    //Prints the heap
    void printHeap();


    //Create the heap from the adjacency list
    void makeHeap(graph *g, int startVertex);

    //Number of elements in the heap
    int numElements() {return n;}

    //Check for a new min distance
    void relax(element u, int vVertex, int vWeight);

private:
    int n = 0; //Size of the heap
    element *heap = new element[1000];

    //Heapify using a bottom up approach for an insertion at a leaf
    void heapifyInsertion(int index);

    //Heapify top down after the head was changed for a leaf
    void heapifyDeletion(int index);

    //Insert an element into the heap
    void insert(element elm);

    //Add another predecessor to an element
    void addPredecessor(int predecessor, int vertex);

    //Reduce the distance
    void decreaseKey(int index, int newMinDist);
};

#endif //PROJECT3_HEAP_H
