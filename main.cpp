//
// Created by blancj4 on 7/21/2024.
//
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "errors.h"
int main(int argc, char** argv){
    if (argc < 5){
        std::perror("ERROR: Not enough arguments");
        abort();
    }
}