#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<iostream>
#include"task.h"
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include<sys/wait.h>

using namespace std;

// function prototypes


void showTime();

using namespace std::chrono_literals;

int main() {

   std::cout << "Loading: ";
for (int i = 0; i <= 100; i++) {
   // std::cout << i << "% ";
    std::this_thread::sleep_for(20ms);
    std::cout << "\rLoading: " << std::setw(3) << std::setfill(' ') << i << "%";
    std::cout.flush();
}

std::cout << "\n\n";

// wait for 3 seconds before displaying welcome message
std::this_thread::sleep_for(1s);

int count=0;
char hostname[256];
    gethostname(hostname, 256);
    std::cout << "Welcome to " << hostname << std::endl;
    showTime();
    
    // get hardware resources from user
    int available_ram = 2048; // default 2GB RAM
    int available_hardDrive = 256; // default 256GB hard drive
    int available_numCores = 8; // default 8 cores
    int ram,hardDrive,numCores=0;
    cout<<"Available RAM:"<<available_ram <<endl;
    cout<<"Available HardDrive:"<<available_hardDrive<<endl;
    cout<<"Available RAM:"<<available_numCores<<endl;
    cout << "\nPlease enter the amount of RAM (in MB): ";
    cin >> ram;
    
    while(ram > available_ram){
      cout<<"Insufficient RAM!!"<<endl;
      cout << "\nPlease enter the amount of RAM (in MB): ";
    cin >> ram;
    }
    
    cout << "Please enter the size of hard drive (in GB): ";
    cin >> hardDrive;
     while(hardDrive > available_hardDrive){
      cout<<"Insufficient!!"<<endl;
       cout << "Please enter the size of hard drive (in GB): ";
    cin >> hardDrive;
    }
    
    int shm_id = shmget(IPC_PRIVATE, sizeof(Task), IPC_CREAT | 0666); // create shared memory segment

    if (shm_id < 0) { // check for errors
        perror("shmget");
        exit(1);
    }
    char shm_id_str[43];
    sprintf(shm_id_str, "%d", shm_id); // convert shm_id to string
    
    Task* shared_task = (Task *)shmat(shm_id, NULL, 0); 
    if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
        
    shared_task->ram = ram;
    shared_task->hardisk = hardDrive;
        
    int allocateram = 0;
    int allocatehardisk = 0;
    int id = 0;
        
    // display available tasks
    int choice = 0;

    do {
        cout << "\nAvailable tasks:\n";
        cout << "1. Notepad\n";
        cout << "2. Calculator\n";
        cout << "3. Time\n";
        cout << "4. Create file\n";
        cout << "5. Move file\n";
        cout << "6. Copy file\n";
        cout << "7. Delete file\n";
        cout << "8. Check file info\n";
        cout << "9. Image viewer\n";
        cout << "10. Text editor\n";
        cout << "11. Game\n";
        cout << "12. Joke Generator\n";
        cout << "13. Timer\n";
        cout << "14. Contact Manager\n";
        cout << "15. Novel App\n";
        cout << "0. Exit\n";

        cout << "Please enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                {
                
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./notepadhome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
                }
                break;
            case 2:
            {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./calculatorhome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 3:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./timehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 4:
            {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./createfilehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 5:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./movefilehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 6:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./copyfilehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 7:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./deletefilehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 8:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./checkfileinfohome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 9:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./imagehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 10:
                {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./texteditorhome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 11:
             {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./gamehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
         break;
         case 12:
         {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./jokehome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
         break;
         case 13:
           {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./Timerhome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
         
             break;
            case 14:
            {
            
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./Contacthome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
             case 15:
            {
           
            Task* shared_task = (Task *)shmat(shm_id, NULL, 0); // attach the shared memory segment

        if ( (intptr_t)shared_task == -1) { // check for errors
            perror("shmat");
            exit(1);
        }
         cout<<"\nEnter amount of RAM to be allocated:  ";
         cin>>allocateram;
         cout<<"\nEnter amount of HARDISK to be allocated:  ";
         cin>>allocatehardisk;
         if(allocateram<shared_task->ram+1&&allocatehardisk<shared_task->hardisk+1)
         {
            shared_task->ram-=allocateram;
            shared_task->hardisk-=allocatehardisk;
            shared_task->allowed=true;
            count++;
         }
         else
         {
            std::cout<<"Memory/Hardisk not available\n";
            shared_task->allowed=false;}
            if(shared_task->allowed==true)
            {
               char MEM[43];
               sprintf(MEM, "%d", allocateram);
               char disk[43];
               sprintf(disk, "%d", allocatehardisk);
               char taskcount[43];
               sprintf(taskcount, "%d", count);
               if(shared_task->sharedcount==0)
               shared_task->sharedcount=1;
               std::string command = "gnome-terminal -- bash -c  ' ./Novelhome " +std::string(MEM)+" "+std::string(disk)+" "+std::string(taskcount)+" "+ std::string(shm_id_str)+ "; $SHELL' ";

               int result = system(command.c_str()); // Execute the command
            }
         }
                break;
            case 0:
                {
                  cout << "Exiting UKKILOS...\n";
                }
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    
    }while (choice != 0);

    shmdt(shared_task); // detach the shared memory segment
    shmctl(shm_id, IPC_RMID, NULL); // remove the shared memory segment
    return 0;
}

void showTime() {
    //cout << "Current Time...\n";
    
        auto now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        struct tm* local_time = localtime(&current_time);
        cout << "Current time: " << put_time(local_time, "%H:%M:%S") << endl;
        cout << "Current date: " << put_time(local_time, "%A, %B %d, %Y") << endl;
        this_thread::sleep_for(chrono::seconds(1)); // wait for 1 second
    cout<<endl;
}


