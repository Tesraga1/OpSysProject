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
    vector<int> bursts;
    Process(string ID_, int bound_);
    int returnBound(); //return 0 if CPU bound and 1 if IO Bound
    string returnID(); //returns process ID
    void addBurst(int CPU_time, int IO_time);
    int numBursts();
    int returnBurst();
    void burstComplete(int currentTime);
    int returnBlockTime();
    int returnArrivalTime();
    void add_arrival(int a);
};


#endif //OPSYSPROJECT_PROCESS_H