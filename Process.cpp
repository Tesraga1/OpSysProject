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

#include "Process.h"

Process::Process(string ID_, int bound_) {
    ID = ID_;
    bound = bound_;
}

string Process::returnID() const{
    return ID;
}

int Process::returnBound() {
    return bound;
}

void Process::addBurst(int CPU_time, int IO_time) {
    bursts.push_back(CPU_time);
    bursts.push_back(IO_time);
}

int Process::numBursts() const{
    return bursts.size()/2;
}

int Process::returnBurst() const{
    return bursts[0];
}

void Process::burstComplete(int currentTime, int time) {
    bursts.erase(bursts.begin());
    IO_Block = currentTime + bursts[0] + time;
    bursts.erase(bursts.begin());
}

void Process::reduceBurst(int currentTime) {
    if (!bursts.empty()) {
        // reduce the first element of the bursts vector (current CPU time)
        bursts[0] -= currentTime;
        if (bursts[0] < 0) {
            bursts[0] = 0;
        }
    }
};

int Process::returnBlockTime() const{
    return IO_Block;
}
int Process::returnArrivalTime() const{
    return arrival;
}
void Process::add_arrival(int a) {
    arrival = a;
}

int Process::returnEnd() const{
    return end_time;
}

void Process::add_end(int a) {
    end_time = a;
}