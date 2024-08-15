#include <iostream>#include <cmath>#include <cstdio>#include <vector>#include <string>#include <cstdlib>#include <fstream>#include "Process.h"#include <iomanip>#include <algorithm>#include <queue>using namespace std;//Global Variablesint seed;double lambda;int bound;int t_cs;float alpha;int tslice;//overall average CPU burst time = totalCPU burst time / total CPU burstsdouble CPU_burst_time = 0;double CPU_total_bursts = 0;//overall average IO burst time = totalIO burst time / total IO burstsdouble IO_burst_time = 0;double IO_total_bursts = 0;//CPU Bound average CPU time = total CB CPU time / total CB CPU burstsdouble CB_CPU_time = 0;double CB_CPU_bursts = 0;//IO Bound average CPU time = total IB CPU time / total IB CPU burstsdouble IB_CPU_time = 0;double IB_CPU_bursts = 0;//CPU Bound average IO time = total CB IO time / total CB IO burstsdouble CB_IO_time = 0;double CB_IO_bursts = 0;//IO Bound average IO time = total IB IO time / total IBB IO burstsdouble IB_IO_time = 0;double IB_IO_bursts = 0;//will hold the CPU burst time and IO burst time for each CPU burstint CPU_burst = 0;int IO_burst = 0;void print_ready(vector<Process>& readyQueue, int &starting){    int count = 0;    int total = readyQueue.size();    for (int x = starting; x < total; x++){        count++;        printf("%s",readyQueue[x].returnID().c_str());        if (count != total-1){            printf(" ");        } else {            printf("]\n");        }    }}bool compareByArrival(const Process &a, const Process&b) {    return a.returnArrivalTime() < b.returnArrivalTime();}// FCFS: First-come-first-servedvoid FCFS(vector<Process> processList) {    printf("time 0ms: Simulator started for FCFS [Q empty]\n");    std::sort(processList.begin(), processList.end(), compareByArrival);    bool first = true;    bool cpu_in_use = false;    vector<Process> readyQueue;    vector<Process> io_list;    int current_time = 0;    int new_process = 0;    while(true){        if (readyQueue.size() > 0) {            if (cpu_in_use && current_time == readyQueue[0].returnEnd()){                new_process = current_time + t_cs;                readyQueue[0].burstComplete(current_time);                printf("time %dms: Process %s completed a CPU burst; %d bursts to go [Q ", current_time, readyQueue[0].returnID().c_str(), readyQueue[0].numBursts());                printf("time %dms: Process %s switching out of CPU; blocking on I/O until time %dms [Q ", current_time, readyQueue[0].returnID().c_str(), readyQueue[0].returnBlockTime());                io_list.push_back(readyQueue[0]);                if (readyQueue.size() == 0){                    printf("empty]\n");                } else {                    print_ready(readyQueue, 1);                }                readyQueue.erase(readyQueue.begin());                cpu_in_use = false;            }            if (!cpu_in_use && first && current_time == new_process ) {                first = false;                printf("time %dms: Process %s started using the CPU for %dms burst [Q  ", current_time, readyQueue[0].returnID().c_str(), readyQueue[0].returnBurst());                if (readyQueue.empty()){                    printf("empty]\n");                } else {                    print_ready(readyQueue, 1);                }                cpu_in_use = true;                readyQueue[0].add_end(current_time + readyQueue[0].returnBurst());            }            if (!cpu_in_use && current_time == new_process) {                printf("time %dms: Process %s started using the CPU for %dms burst [Q \n", current_time, readyQueue[0].returnID().c_str(), readyQueue[0].returnBurst());                if (readyQueue.empty()){                    printf("empty]\n");                } else {                    print_ready(readyQueue, 1);                }                cpu_in_use = true;                readyQueue[0].add_end(current_time + readyQueue[0].returnBurst());            }        }        if (processList.size() != 0) {            if (processList[0].returnArrivalTime() == current_time) {                if (processList[0].returnArrivalTime() - current_time == 0) {                    new_process = current_time + (t_cs/2);                    first = true;                }                printf("time %dms: Process %s arrived; added to ready queue [Q ", current_time, processList[0].returnID().c_str());                readyQueue.push_back(processList[0]);                if (readyQueue.empty()){                    printf("empty]\n");                } else {                    print_ready(readyQueue, 0);                }                processList.erase(processList.begin());            }        } else if (readyQueue.size() == 0){            break;        }    }}//// SJF: Shortest job first//void SJF(vector<Process> processList) {//    printf("time 0ms: Simulator started for SJF [Q empty]\n");//    int current_time = 0;//    while (!processList.empty()) {//        // you need to sort the readyQueue based on the burst time//        sort(readyQueue.begin(), readyQueue.end(), [](Process a, Process b) {//            return a.returnBurst() < b.returnBurst();//        });//        Process p = readyQueue.front();//        readyQueue.erase(readyQueue.begin());//        printf("time %dms: Process %s started using the CPU for %dms burst [Q ", current_time, p.returnID().c_str(), p.returnBurst());//        print_ready();//        current_time += p.returnBurst();//        printf("time %dms: Process %s completed its CPU burst [Q ", current_time, p.returnID().c_str());//        print_ready();//    }//}// SRT: Shortest remaning time//void SRT() {//    printf("time 0ms: Simulator started for SRT [Q empty\n");//    int current_time = 0;//    while (!processList.empty()) {//        // you need to sort the readyQueue based on the **remaining** time//        sort(readyQueue.begin(), readyQueue.end(), [](Process a, Process b) {////        })//    }////}//Round robin//void RR() {////}// define a function to generate the next exponential number for argv #3?double exp_dist(double lambda, int upper) {    while (true) {        double r = drand48();  /* uniform dist [0.00, 1.00), ln(0) = undefined */        /* generate the next pseudo-random value x */        double x = -log(r) / lambda;        /* log() is natural log */        //printf("%lf\n", x);        if (x <= upper) {            return x;        }    }}int main(int argc, char** argv){    if (argc != 9){        perror("ERROR: Not enough argument\n");        abort();    }    int processes = stoi(*(argv+1));    int cpu_bound = stoi(*(argv+2));    seed = stoi(*(argv+3));    lambda = stod(*(argv+4));    bound = stoi(*(argv+5));    t_cs = stoi(*(argv+6));    alpha = stof(*(argv+7));    tslice = stoi(*(argv+8));    if (processes <= 0){        perror("ERROR: # of processes not greater than zero\n");        abort();    }    if (processes > 260) {        perror("ERROR: # of processes too great\n");        abort();    }    if (lambda <= 0) {        perror("ERROR: lambda 0 or less\n");        abort();    }    if (cpu_bound > processes) {        perror("ERROR: cpu_bound cannot be greater than processes\n");        abort();    }    if (cpu_bound < 0) {        perror("ERROR: cpu_bound cannot be less than 0\n");        abort();    }    if (bound < 0) {        perror("ERROR: upper bound cannot be less than 0\n");        abort();    }    if (t_cs % 2 != 0 || t_cs < 0){        perror("ERROR: time either not even or negative\n");        abort();    }    if (alpha > 1 || alpha < 0){        perror("ERROR: alpha not between 0 and 1\n");        abort();    }    if (tslice < 0){        perror("ERROR: time slice not positive\n");        abort();    }    srand48(seed);    if (cpu_bound == 1) {        printf("<<< PROJECT PART I\n"               "<<< -- process set (n=%d) with %d CPU-bound process\n"               "<<< -- seed=%d; lambda=%lf; bound=%d\n", processes, cpu_bound, seed, lambda, bound);    } else {        printf("<<< PROJECT PART I\n"               "<<< -- process set (n=%d) with %d CPU-bound processes\n"               "<<< -- seed=%d; lambda=%lf; bound=%d\n", processes, cpu_bound, seed, lambda, bound);    }    vector<Process> processList;    //process creation loop    int letter = 65; // 65 is A, but can only go up to 90 which is Z    int number = 0;    for(int i = 0; i < processes; i++) {        char first = char(letter);        string ID = first + to_string(number);        if (i < cpu_bound) {            processList.emplace_back(ID, 0);        } else {            processList.emplace_back(ID, 1);        }        number++;        if (number > 9) {            number = 0;            letter++;        }    }    //process loop    for (int i = 0; i < processes; i++) {        int arrival = floor(exp_dist(lambda, bound));        int bursts = ceil(drand48() * 32);        processList[i].add_arrival(arrival);        CPU_total_bursts += bursts; //adds to total CPU bursts        IO_total_bursts += bursts-1; //adds to total IO bursts        if (i < cpu_bound) { //If the process is CPU Bound            CB_CPU_bursts += bursts;            CB_IO_bursts += bursts-1;            if (bursts == 1) {                printf("CPU-bound process %s: arrival time %dms; %d CPU burst:\n", processList[i].returnID().c_str(), arrival, bursts);            } else {                printf("CPU-bound process %s: arrival time %dms; %d CPU bursts:\n", processList[i].returnID().c_str(), arrival, bursts);            }        } else { //If the process is I/O Bound            IB_CPU_bursts += bursts;            IB_IO_bursts += bursts-1;            if (bursts == 1) {                printf("I/O-bound process %s: arrival time %dms; %d CPU burst:\n", processList[i].returnID().c_str(), arrival, bursts);            } else {                printf("I/O-bound process %s: arrival time %dms; %d CPU bursts:\n", processList[i].returnID().c_str(), arrival, bursts);            }        }        //processes each CPU Burst for the process        for(int j = 0; j < bursts; j++) {            CPU_burst = ceil(exp_dist(lambda, bound)); //CPU burst time of burst            if (j != bursts-1) {                //will get I/O burst time on all bursts except last                IO_burst = ceil(exp_dist(lambda, bound));            }            if (i < cpu_bound) { //If the process is CPU Bound                CPU_burst *= 4;                CB_CPU_time += CPU_burst;                if (j != bursts-1) { //add IO burst time on all bursts but last                    CB_IO_time += IO_burst;                }            } else { //If the process and I/O bound                if (j != bursts-1) { //we get I/O burst time if not last burst                    IO_burst *= 8;                    IB_IO_time += IO_burst;                }                IB_CPU_time += CPU_burst;            }            //adds the total burst time for CPU and IO            CPU_burst_time += CPU_burst;            if (j != bursts-1) {                IO_burst_time += IO_burst;            }            processList[i].addBurst(CPU_burst, IO_burst);            if (j == bursts-1) {                //printf("==> CPU burst %dms\n", CPU_burst);            } else {                //printf("==> CPU burst %dms ==> I/O burst %dms\n", CPU_burst, IO_burst);            }        }    }    printf("<<< PROJECT PART II\n"           "<<< -- t_cs=%dms; alpha=%.2f; t_slice=%dms", t_cs, alpha, tslice);    FCFS(processList);    //Calculates the averages with ceiling roundings    double CB_CPU_avg = 0; // CPU bound average CPU burst time    if (CB_CPU_time != 0 && CB_CPU_bursts != 0) {        CB_CPU_avg = CB_CPU_time/CB_CPU_bursts;        CB_CPU_avg = ceil(CB_CPU_avg * 1000) / 1000;    }    double IB_CPU_avg = 0; // I/O bound average CPU burst time    if (IB_CPU_time != 0 && IB_CPU_bursts != 0) {        IB_CPU_avg = IB_CPU_time/IB_CPU_bursts;        IB_CPU_avg = ceil(IB_CPU_avg * 1000) / 1000;    }    double CPU_avg = 0; // overall average CPU burst time    if (CPU_burst_time != 0 && CPU_total_bursts != 0) {        CPU_avg = CPU_burst_time/CPU_total_bursts;        CPU_avg = ceil(CPU_avg * 1000) / 1000;    }    double CB_IO_avg = 0; // CPU bound average IO bursts time    if (CB_IO_time != 0 && CB_IO_bursts != 0) {        CB_IO_avg = CB_IO_time/CB_IO_bursts;        CB_IO_avg = ceil(CB_IO_avg * 1000) / 1000;    }    double IB_IO_avg = 0; // IO bound average IO burst time    if (IB_IO_time != 0 && IB_IO_bursts != 0) {        IB_IO_avg = IB_IO_time/IB_IO_bursts;        IB_IO_avg = ceil(IB_IO_avg * 1000) / 1000;     }    double IO_avg = 0; // overall average IO burst time    if (IO_burst_time != 0 && IO_total_bursts != 0) {        IO_avg = IO_burst_time/IO_total_bursts;        IO_avg = ceil(IO_avg * 1000) / 1000;    }    FILE* outfile = fopen("simout.txt", "w");    if(outfile == NULL){    	perror("ERROR: failed to create file\n");        abort();    }//    fprintf(outfile, "-- number of processes: %d\n", processes);//    fprintf(outfile, "-- number of CPU-bound processes: %d\n", cpu_bound);//    fprintf(outfile, "-- number of I/O-bound processes: %d\n", io_bound);////    fprintf(outfile, "-- CPU-bound average CPU burst time: %0.3f ms\n", CB_CPU_avg);//    fprintf(outfile, "-- I/O-bound average CPU burst time: %0.3f ms\n", IB_CPU_avg);////    fprintf(outfile, "-- overall average CPU burst time: %0.3f ms\n", CPU_avg);////    fprintf(outfile, "-- CPU-bound average I/O burst time: %0.3f ms\n", CB_IO_avg);//    fprintf(outfile, "-- I/O-bound average I/O burst time: %0.3f ms\n", IB_IO_avg);////    fprintf(outfile, "-- overall average I/O burst time: %0.3f ms\n", IO_avg);    fclose(outfile);    return 0;}