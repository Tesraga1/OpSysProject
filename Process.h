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
        vector<int> bursts;
        Process(string ID_, int bound_);
        int returnBound(); //return 0 if CPU bound and 1 if IO Bound
        string returnID(); //returns process ID
        void addBurst(int burst_time);
        int numBursts();
        int burst();
};


#endif //OPSYSPROJECT_PROCESS_H
