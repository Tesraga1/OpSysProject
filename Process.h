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
    int prediction;
    int decremented_prediction;
    int arrival;
    int IO_Block;
    int end_time;
    int saved_burst;
    bool preempt = false;
    int wait_time = 0;
    vector<int> bursts;
    Process(string ID_, int bound_, int prediction_);
    int returnBound(); //return 0 if CPU bound and 1 if IO Bound
    void increment_wait_time();
    int return_wait_time();
    void decrement_wait_time(int decrement);
    string returnID() const; //returns process ID
    void addBurst(int CPU_time, int IO_time);
    void save_burst();
    int return_saved_burst() const;
    int numBursts() const;
    int returnBurst() const;
    void burstComplete(int currentTime, int time);
    void reduceBurst();
    int returnBlockTime() const;
    int returnArrivalTime() const;
    void add_arrival(int a);
    void add_end(int a);
    int returnEnd() const;
    int return_prediction() const;
    void update_prediction(float alph, int type);
    void set_preempt();
    void unpreempt();
    bool return_preempt();

};


#endif //OPSYSPROJECT_PROCESS_H