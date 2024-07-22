#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include "Process.h"
using namespace std;

// define a function to generate the next exponential number for argv #3?
double exp_dist(double lambda, int upper) {
    while (true) {
        double r = drand48();  /* uniform dist [0.00, 1.00), ln(0) = undefined */
        /* generate the next pseudo-random value x */
        double x = -log(r) / lambda;        /* log() is natural log */
        //printf("%lf\n", x);
        if (x <= upper) {
            return x;
        }
    }
}
int main(int argc, char** argv){
    if (argc < 6){
        perror("ERROR: Not enough argument\n");
        abort();
    }
    int processes = stoi(*(argv+1));
    int cpu_bound = stoi(*(argv+2));
    int io_bound = processes - cpu_bound;
    int seed = stoi(*(argv+3));
    double lambda = stod(*(argv+4));
    int upper_bound = stoi(*(argv+5));
    if (processes < 0){
        perror("ERROR: # of processes not greater than 0");
        abort();
    }
    if (lambda <= 0) {
        perror("ERROR: lambda 0 or less");
        abort();
    }

    srand48(seed);

    vector<Process> processList;
    vector<Process> readyQueue;
    printf("<<< PROJECT PART I\n"
           "<<< -- process set (n=%d) with %d CPU-bound process\n"
           "<<< -- seed=%d; lambda=%lf; bound=%d\n", processes, cpu_bound, seed, lambda, upper_bound);

    //process creation loop
    int letter = 65; // 65 is A, but can only go up to 90 which is Z
    int number = 0;
    for(int i = 0; i < processes; i++) {
        char first = char(letter);
        string ID = first + to_string(number);
        if (i < cpu_bound) {
            processList.emplace_back(ID, 0);
        } else {
            processList.emplace_back(ID, 1);
        }
        number++;
        if (number > 9) {
            number = 0;
        }
        letter++;
        if (letter > 90) {
            perror("Extended process ID range!");
            return 1;
        }
    }

    for (int i = 0; i < cpu_bound; i++){
        int arrival = floor(exp_dist(lambda, upper_bound));
        int bursts = ceil(drand48() * 32);
        printf("CPU-bound process %s: arrival time %dms; %d CPU bursts\n", "A0", arrival, bursts);
    }
}