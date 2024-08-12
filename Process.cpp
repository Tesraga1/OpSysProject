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

string Process::returnID() {
    return ID;
}

int Process::returnBound() {
    return bound;
}

void Process::addBurst(int CPU_time, int IO_time) {
    bursts.push_back(CPU_time);
    bursts.push_back(IO_time);
}

int Process::numBursts() {
    return bursts.size()/2;
}

int Process::returnBurst() {
    return bursts[0];
}

void Process::burstComplete(int currentTime) {
    bursts.erase(bursts.begin());
    IO_Block = currentTime + bursts[0];
    bursts.erase(bursts.begin());
}

int Process::returnBlockTime() {
    return IO_Block;
}
int Process::returnArrivalTime() {
    return arrival;
}
void Process::add_arrival(int a) {
    arrival = a;
}