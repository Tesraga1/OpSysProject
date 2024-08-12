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

void Process::addBurst(int burst_time) {
    bursts.push_back(burst_time);
}

int Process::numBursts() {
    return bursts.size();
}

int Process::burst() {
    int bursty = bursts[0];
    bursts.erase(bursts.begin());
    return bursty;
}