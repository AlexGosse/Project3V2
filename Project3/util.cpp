//
// Created by Alex on 11/9/2020.
//
#include "util.h"

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

//Print the shortest path from start to end node
//void printShortestPath(int s, int e, MinHeap::element *setS, int setSize){
//
//}

//void printShortestPath(int s, int e, MinHeap::element *setS, int setSize){
//    for(int i = 0; i < setSize; i++){
//        if(setS[i].vertex == e){
//            int pos = e;
//            while(setS[pos].vertex != s){
//                std::cout << setS[pos].vertex << " <- ";
//            }
//        }
//    }
//}
