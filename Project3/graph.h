//
// Created by Alex on 11/9/2020.
//

#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H

class graph {
private:
    int numVert, numEdge;
    struct node{
        int vertex;
        int weight;
        node* next;
    };

    //Each element in the linked list are the outgoing neighbors of the vertex equal to the index
    node** adjacencyList;

public:
    graph(int n, int m);
    int getNumVertices(){return numVert;}
    int getNumEdges(){return numEdge;}

    //Iterate through adjacency List
    node* getIter(int i){return adjacencyList[i];}
    node* newNode(); //Make a new node, should maybe be private
    void printGraph();
    void insertElement(int* edgeInfo); //Insert element into the graphs
};


#endif //PROJECT3_GRAPH_H
