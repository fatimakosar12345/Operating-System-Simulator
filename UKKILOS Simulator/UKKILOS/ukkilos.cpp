#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

int fileRead(int RAM) {
    ifstream myfile;
    myfile.open("variable.txt");

    if (myfile.is_open()) {
        while (getline(myfile, str)) {
            RAM = stoi(str);
        }
    }
    else {
        cout << "File is not opened\n";
    }
    myfile.close();
    return RAM;
}

void fileWrite(int RAM, int ALLOCATE) {
    ofstream myfile;
    myfile.open("variable.txt");

    if (myfile.is_open()) {
        myfile << ALLOCATE << std::endl;
        myfile << RAM;
    }
    else {
        cout << "File is not opened\n";
    }
    myfile.close();
}

int firstFit(int processSize, queue<pair<int, int>>& freeList) {
    int allocatedMemory = -1;
    queue<pair<int, int>> temp;
    while (!freeList.empty()) {
        int start = freeList.front().first;
        int end = freeList.front().second;
        int size = end - start + 1;
        if (size >= processSize) {
            allocatedMemory = start;
            if (size > processSize) {
                freeList.push(make_pair(start + processSize, end));
            }
            freeList.pop();
            break;
        }
        temp.push(freeList.front());
        freeList.pop();
    }
    while (!temp.empty()) {
        freeList.push(temp.front());
        temp.pop();
    }
    return allocatedMemory;
}

int main() {
    int ram = 1024;
    queue<pair<int, int>> freeList;
    freeList.push(make_pair(0, ram - 1));

    queue<pair<string, int>> processQueue;

    int choice, allocate = 0;
    while (true) {
        cout << "Please enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Enter size of the process: " << endl;
            cin >> allocate;
            ram = fileRead(ram);
            int allocatedMemory = firstFit(allocate, freeList);
            if (allocatedMemory >= 0) {
                fileWrite(ram, allocate);
                string command = "gnome-terminal -- bash -c './time" + to_string(ram) + " " + to_string(allocate) + "; $SHELL'";
                int result = system(command.c_str()); // Execute the command
                processQueue.push(make_pair("time", allocatedMemory));
            }
            else {
                cout << "Memory not available, process added to queue.\n";
                processQueue.push(make_pair("time", allocate));
            }
            break;
        }
        case 2: {
            cout << "Enter size of the process: " << endl;
            cin >> allocate;
ram = fileRead(ram);
int allocatedMemory = firstFit(allocate, freeList);
if (allocatedMemory >= 0) {
fileWrite(ram, allocate);
string command = "gnome-terminal -- bash -c './novel" + to_string(ram) + " " + to_string(allocate) + "; $SHELL'";
int result = system(command.c_str()); // Execute the command
processQueue.push(make_pair("time", allocatedMemory));
}
else {
cout << "Memory not available, process added to queue.\n";
processQueue.push(make_pair("time", allocate));
}
break;
}
case 3: {
if (!processQueue.empty()) {
pair<string, int> process = processQueue.front();
processQueue.pop();
if (process.first == "time") {
int start = process.second;
int end = start + allocate - 1;
freeList.push(make_pair(start, end));
fileWrite(ram, allocate);
cout << "Process allocated memory has been freed.\n";
}
}
else {
cout << "No process in queue to remove.\n";
}
break;
}
case 4: {
cout << "Memory Map: " << endl;
for (int i = 0; i < ram; i++) {
int flag = 0;
for (auto freeBlock : freeList) {
if (i >= freeBlock.first && i <= freeBlock.second) {
cout << ".";
flag = 1;
break;
}
}
if (!flag) {
cout << "X";
}
}
cout << endl;
break;
}
case 5: {
exit(0);
}
default: {
cout << "Invalid choice, please enter again.\n";
}
}
}
return 0;
}

