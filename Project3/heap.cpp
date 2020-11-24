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

//Number of elements in the heap
int MinHeap::numElements() {
    return n;
}

//Remove and return the min
MinHeap::element MinHeap::extractMin(){
    if(n == 0) {
        std::cout << "ERROR EXTRACTING MIN: N == 0 " << std::endl;
        return element(); //No elements, should never happen
    }
    element min = heap[0];
    heap[0] = heap[n-1]; //Replace head
    n--; //Decrement num of elements in the heap

    heapifyDeletion(0);

    return min;
}

////Remove and return the min
//int MinHeap::extractMin(){
//    if(n == 0) return -1; //No elements
//
//    int min = minimum();
//    heap[0] = heap[n-1]; //Replace head
//    n--; //Decrement num of elements in the heap
//
//    heapifyDeletion(0);
//    return min;
//}

//Return the vertex of the min node
int MinHeap::minVertex() {
    return heap[0].vertex;
}

//Make the heap using insert
void MinHeap::makeHeap(graph *g, int startVertex) {
    int numVert = g->getNumVertices();

    //First add all the vertices without pred vertex
    for(int i = 0; i < numVert; i++){ //Loop through every vertex
        if(i == startVertex) //If inserting a connection from start of the search algo, it's min dist is its weight
            insert(element(i, 0)); //Assign the min dist to start
        else
            insert(element(i, MAX_HEAP)); //Default min dist is large integer
    }

    //Add all the predecessor vertices
    for(int i = 0; i < numVert; i++){ //Loop through every vertex, i = predIndex
        auto iter = g->getIter(i); //Iterate through the linked list
        while(iter != nullptr && iter->vertex != -1){ //Loop through linked list
            addPredecessor(i, iter->vertex); //Add the predecessor if necessary
            iter = iter->next;
        }
    }
}

//Add a predecessor to an index of the
void MinHeap::addPredecessor(int predecessor, int vertex){
    //Check if the predecessor already exists
    for(int i = 0; i < heap[vertex].predVSize; i++){ //Loop through predecessors
        if(heap[vertex].predV[i] == predecessor){
            return;
        }
    }
    //Add predecessor
    heap[vertex].predV[heap[vertex].predVSize] = predecessor;
    heap[vertex].predVSize ++;
}

//Insert an element into the minHeap
void MinHeap::insert(element elm){
    heap[n] = elm;
    n++; //Increase the size of the heap
    heapifyInsertion(n-1); //Place element in the correct position
}

//Reduce the min distance of a connection
void MinHeap::decreaseKey(int index, int newMinDist){
//    for(int i = 0; i < n; i++){ //Find index in heap
//        if(heap[i].vertex == index) {
//            heap[i].minDist = newMinDist;
//            heapifyInsertion(i); //Maintain heap property
//        }
//    }
    heap[index].minDist = newMinDist;
    heapifyInsertion(index);
}

//Check for a new min distance
void MinHeap::relax(element u, int vVertex, int vWeight){
    //Find vVertex in heap
    int vIndex = -1;
    for(int i = 0; i < n; i++){
        if(heap[i].vertex == vVertex)
            vIndex = i;
    }

    if(u.minDist + vWeight < heap[vIndex].minDist) {
        decreaseKey(vIndex, u.minDist + vWeight); //Update the minDist
        std::cout << "u.vertex: " << u.vertex << std::endl;
        std::cout << "heap[vVertex]: " << heap[vVertex].vertex << std::endl;
        std::cout << "vVertex: " << vVertex << std::endl;
        heap[vIndex].bestPred = u.vertex;
    }
}

//Prints the heap
void MinHeap::printHeap(){
    std::cout << "Min Dist: " <<std::endl;
    for(int i = 0; i < n; i++)
        std::cout << heap[i].minDist << std::endl;
    std::cout << "PredVertex: " << std::endl;
    for(int i = 0; i < n; i++) {
        std::cout << "Vertex: ";
        std::cout << heap[i].vertex << ": ";
        for (int j = 0; j < heap[i].predVSize; j++)
            std::cout << heap[i].predV[j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
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

//Heapify top down after the head was changed for a leaf
void MinHeap::heapifyDeletion(int index){
    if(n == 1)
        return;

    //Indexes of left and right children
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallestChild = MAX_HEAP; //The index smaller of the left and right children

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
    if(smallestChild != MAX_HEAP && heap[smallestChild].minDist < heap[index].minDist ) {
        std::swap(heap[index], heap[smallestChild]);
        heapifyDeletion(smallestChild);
    }
}
