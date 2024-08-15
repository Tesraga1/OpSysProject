//
// Created by blancj4 on 7/21/2024.
//
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include "string"
#include "stdlib.h"
using namespace std;

#ifndef OPSYSPROJECT_PROCESS_H
#define OPSYSPROJECT_PROCESS_H


class Process {
public:
    int bound;
    string ID;
    int arrival;
    int IO_Block;
    int end_time;
    vector<int> bursts;
    Process(string ID_, int bound_);
    int returnBound(); //return 0 if CPU bound and 1 if IO Bound
    string returnID() const; //returns process ID
    void addBurst(int CPU_time, int IO_time);
    int numBursts() const;
    int returnBurst() const;
    void burstComplete(int currentTime);
    int returnBlockTime() const;
    int returnArrivalTime() const;
    void add_arrival(int a);
    void add_end(int a);
    int returnEnd() const;
    bool operator<(const Process& other) const{
        // Customize this comparison according to your needs
        return returnEnd() < other.returnEnd();  // Example: compare based on burst time
    }
};


#endif //OPSYSPROJECT_PROCESS_H