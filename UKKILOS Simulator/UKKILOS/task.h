#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;


class Task{
    public:
    pid_t pid;
    int ram;
    int hardisk;
    int sharedcount;
    bool allowed;

    Task(){
        pid==-1;
        ram=0;
        hardisk=0;
        sharedcount=0;
        allowed=false;
    }
};

