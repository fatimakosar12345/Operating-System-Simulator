#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>

#include"createfile.cpp"
#include <sys/shm.h>
#include<iostream>

#include"task.h"


using namespace std;
void createfile();

void sigterm_handler(int signum)
{
    // Perform cleanup before exiting
    printf("Received SIGKILL signal. Cleaning up and exiting.\n");
   cout<<"hi"<<endl;

   sleep(2);
    exit(0);
}


int main(int argc, char** argv) {
    
     if (argc != 5)
    { // check for correct number of arguments
        fprintf(stderr, "Usage: %s <shm_id>\n", argv[0]);
        exit(1);
    }
    
    int mem=atoi(argv[1]);
    int hard=atoi(argv[2]);
    int count = atoi(argv[3]);
    int shm_id = atoi(argv[4]);
    
    Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
    


    
    cout<<"Entered amount of ram for process is:  ";
    cout<<argv[1];
    cout<<"\nEntered amount of hardisk for process is:  ";
    cout<<argv[2]<<endl;
     
        std::cout<<"\nRemaining RAM:  "<<shared_task->ram<<endl;
        std::cout<<"\nRemaining HARDISK:  "<<shared_task->hardisk<<endl;

    pid_t child_pid = fork(); // create a child process using fork()

    if (child_pid == 0) { // in the child process
        
         Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }

        while(shared_task->sharedcount!=count)
        {}
        
        createfile();
        shmdt(shared_task); // detach the shared memory segment
        shmctl(shm_id, IPC_RMID, NULL); // remove the shared memory segment
    } else if (child_pid < 0) { // check for errors
        perror("fork");
        exit(1);
    } else { // in the parent process
        // waitpid(child_pid, NULL, 0); // wait for the child process to exit
        sleep(3);
        signal(SIGKILL,sigterm_handler);
        Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
        
        sleep(2);

        cout<<"Enter key to quit createfile"<<endl;
        cin.get();
        shared_task->ram+=mem;
        shared_task->hardisk+=hard;
        shared_task->allowed=false;
        shared_task->sharedcount++;
            // kill child process
        int r = kill(shared_task->pid, SIGKILL);
        if(r == -1) {
            std::cout << "Error killing child process" << std::endl;;
            return 1;
        }
        cout<<r<<endl;

         cout<<"Child Process Killeddddd yahooooooooo"<<endl;

        shmdt(shared_task); // detach the shared memory segment
        shmctl(shm_id, IPC_RMID, NULL); // remove the shared memory segment
    }

    return 0;
}

