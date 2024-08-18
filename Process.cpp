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

Process::Process(string ID_, int bound_, int prediction_) {
    ID = ID_;
    bound = bound_;
    prediction = prediction_;
}

string Process::returnID() const{
    return ID;
}

//returns if io or cpu bound
int Process::returnBound() {
    return bound;
}

//allows us to save the original burst time since the one in the array might decrement
void Process::save_burst() {
    saved_burst = bursts[0];
}

//adds bursts to the process while initializing
void Process::addBurst(int CPU_time, int IO_time) {
    bursts.push_back(CPU_time);
    bursts.push_back(IO_time);
}

//return numeber of bursts
int Process::numBursts() const{
    return bursts.size()/2;
}

//returns the current burst time
int Process::returnBurst() const{
    return bursts[0];
}

//completes a burst by erasing it and creating the io block time
void Process::burstComplete(int currentTime, int time) {
    bursts.erase(bursts.begin());
    IO_Block = currentTime + bursts[0] + time;
    bursts.erase(bursts.begin());
}

//decrements the current burst time
void Process::reduceBurst() {
    bursts[0]--;
}

//returns the current block time
int Process::returnBlockTime() const{
    return IO_Block;
}

//returns arrival time
int Process::returnArrivalTime() const{
    return arrival;
}

//adds arrival time to process
void Process::add_arrival(int a) {
    arrival = a;
}

//returns the end time of current burst
int Process::returnEnd() const{
    return end_time;
}

//creates the end time of the current burst
void Process::add_end(int a) {
    end_time = a;
}

//returns the prediction for SRT and SJF
int Process::return_prediction() const {
    return prediction;
}

//updates the current prediction
void Process::update_prediction(float alph, int type) {
    prediction = ceil((alph*saved_burst) + ((1.0-alph)*prediction));
}

//returns the original burst aomount
int Process::return_saved_burst() const{
    return saved_burst;
}

//sets the process to preempt
void Process::set_preempt() {
    preempt = true;
}

//unpreempts the process
void Process::unpreempt() {
    preempt = false;
}

//lets us know if the process is preempt
bool Process::return_preempt() {
    return preempt;
}

void Process::increment_wait_time() {
    wait_time++;
}

int Process::return_wait_time() {
    return wait_time;
}

void Process::decrement_wait_time(int decrement) {
    wait_time-=decrement;
}