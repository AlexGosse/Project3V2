//
// Created by Alex on 11/9/2020.
// MinHeap implementation
//

#include "heap.h"
#include "util.h"
#include <iostream>

//Returns the min - There must be at least 1 element in the heap to use
int MinHeap::minimum(){
    //No elements in the heap
    if(n == 0){
        std::cout << "Index out of bounds!!!!!!" << std::endl;
        return INT32_MAX;
    }
    return heap[0].minDist;
}

int MinHeap::numElements() {
    return n;
}

//Remove and return the min
int MinHeap::extractMin(){
    if(n == 0) return -1; //No elements

    int min = minimum();
    heap[0] = heap[n-1]; //Replace head
    n--; //Decrement num of elements in the heap

    heapifyDeletion(0);
    return min;
}

//Make the heap
void MinHeap::makeHeap(graph *g, int startVertex) {
    int numVert = g->getNumVertices();

//    for(int i = 0; i < numVert; i++){ //Loop through every vertex
//        auto iter = g->getIter(i); //Iterate through the linked list
//        while(iter != nullptr && iter->vertex != -1){
//            if(i == startVertex) //If inserting a connection from start of the search algo, it's min dist is its weight
//                insert(element(iter->vertex, i, iter->weight, iter->weight)); //Assign the min dist to elements immediately connected to the start vertex
//            else
//                insert(element(iter->vertex, i, iter->vertex)); //Default min dist is large integer
//            iter = iter->next;
//        }
//    }

    for(int i = 0; i < numVert; i++){ //Loop through every vertex
        if(i == startVertex) //If inserting a connection from start of the search algo, it's min dist is its weight
            insert(element(i, 0)); //Assign the min dist to elements immediately connected to the start vertex
        else
            insert(element(i, MAX_HEAP)); //Default min dist is large integer
    }
}

void MinHeap::insert(element elm){
    heap[n] = elm;
    n++; //Increase the size of the heap
    heapifyInsertion(n-1); //Place element in the correct position
}

//Reduce the min distance of a connection
void MinHeap::decreaseKey(int index, int newMinDist){
    for(int i = 0; i < n; i++){
        if(heap[i].vertex == index) {
            heap[i].minDist = newMinDist;
            heapifyInsertion(i); //Maintain heap property
        }
    }
}

//Prints the heap
void MinHeap::printHeap(){
    std::cout << "Min Dist: " <<std::endl;
    for(int i = 0; i < n; i++)
        std::cout << heap[i].minDist << std::endl;
    std::cout << "\nVertex: " << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << heap[i].vertex << std::endl;
}

//Heapify using a bottom up approach for an insertion at a leaf
void MinHeap::heapifyInsertion(int index) {
    //Find parent index
    int parent = (index - 1) / 2;
    //If child is less than the parent, swap
    while(heap[index].minDist < heap[parent].minDist) {
        std::swap(heap[index], heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

//Find the minDist by looking at predecessors
void MinHeap::setMinDist(int index){
    heap[index].minDist += heap[heap[index].predV].minDist;
}

//Heapify top down after the head was changed for a leaf
void MinHeap::heapifyDeletion(int index){
    //Indexes of left and right children
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallestChild = 500; //The index smaller of the left and right children

    //Bounds checks
    if(left > n && right > n){} //Both out of bounds
    else if (left > n && right < n) //Right is in bounds but not left
        smallestChild = right;
    else if (right > n && left < n) //Left is in bounds but not right
        smallestChild = left;

    //Both in bounds
    else if(heap[left].minDist <= heap[right].minDist) //Left is smaller than right
        smallestChild = left;
    else if (heap[right].minDist < heap[left].minDist) //Right is smaller than left
        smallestChild = right;

    //If there needs to be a swap
    if(smallestChild != 500 && heap[smallestChild].minDist < heap[index].minDist ) {
        std::swap(heap[index], heap[smallestChild]);
        heapifyDeletion(smallestChild);
    }
}
