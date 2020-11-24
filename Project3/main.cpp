#include <iostream>
#include <algorithm>
#include "heap.h"
#include "graph.h"
#include "util.h"

MinHeap::element* Dijkstra(graph adjacencyList, int numOfVertices, int s);
bool compare(MinHeap::element i, MinHeap::element j);

int main() {
    std::string input = "";

    std::getline(std::cin, input);
    int* nm = split(input);
    int n = nm[0]; //Number of vertices in the graph
    int m = nm[2]; //Number of edges in the graph

    //Array of linked lists to store data
    graph adjacencyList(n, m);

    //m lines of code corresponding to the number of edges
    for(int i = 0; i < m; i++){
        std::getline(std::cin, input);
        adjacencyList.insertElement(split(input));
    }

    //Use dijkstra algorithm
    input = "";
    while(input != "stop"){
        startLoop:

        std::getline(std::cin, input); //Receive input
        std::cout << "Command: " << input << std::endl; //Repeat output

        if(input == "stop")
            return 0;

        //Print adjacency graph
        else if (input == "write") {
            std::cout << n << " " << m << std::endl;
            adjacencyList.printGraph();
        }
        //Use Dijkstra algorithm
        else if (input.substr(0, 4) == "find") {
            //Convert input
            int* path = split(input.substr(5, input.length()));
            int startVertex = path[0] - 1; //0 indexed
            int endVertex = path[1] - 1; //0 indexed
            bool isFindingLength = path[2]; //If we are finding the length, otherwise we are finding the distance

            bool error = false;
            //Bounds checking
            if (startVertex >= n || startVertex < 0 || endVertex >= n || endVertex < 0) {
                std::cout << "Error: one or more invalid nodes" << std::endl;
                error = true;
            }

            //Check for flags out of bounds
            if(path[2] != 1 && path[2] != 0) {
                std::cout << "Error: invalid flag value" << std::endl;
                error = true;
            }

            if(error)
                goto startLoop;

            //Use Dijkstra
            MinHeap::element *setS = Dijkstra(adjacencyList, n, startVertex);

            //Check if path exists
            if (setS[endVertex].minDist == MAX_HEAP) {
                std::cout << "Error: node " << endVertex + 1 << " not reachable from node " << startVertex + 1 << std::endl;
                goto startLoop;
            }
            //Path exists
            else {
                //Printing the length
                if (isFindingLength)
                    std::cout << "LENGTH: " << setS[endVertex].minDist << std::endl;

                //Printing the path
                else {
                    int index = endVertex;
                    int pathIndex = 0;

                    int path[n];//Create the path to loop through backwards
                    for (int i = 0; i < n; i++)
                        path[i] = -1;

                    //Fill up path
                    while (setS[index].vertex != setS[startVertex].vertex) {
                        path[pathIndex] = setS[index].vertex;
                        index = setS[index].bestPred;
                        pathIndex++;
                    }
                    //Include starting vertex into the path
                    path[pathIndex] = setS[startVertex].vertex;

                    //Go through the path backward
                    std::cout << "PATH: ";
                    for (int i = pathIndex; i >= 0; i--) {
                        if (i >= 1)
                            std::cout << path[i] + 1 << ";";
                        else
                            std::cout << path[i] + 1 << std::endl;
                    }
                }
            }
            delete [] setS;
        }
    }

    return 0;
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
            q.relax(u, iter->vertex, iter->weight);
            iter = iter->next;
        }
    }

    //Sort s by vertex
    std::sort(setS, setS + numOfVertices, compare);

    return setS;
}

bool compare(MinHeap::element i, MinHeap::element j){ return (i.vertex < j.vertex);}

