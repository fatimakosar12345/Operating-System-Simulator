#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <sys/stat.h>
#include <iomanip>
#include <unistd.h>
#include <ctime>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//using namespace cv;
using namespace std;
void checkFileInfo(){
string file_path = "laiam.txt";
    struct stat file_stat;
    if(stat(file_path.c_str(), &file_stat) == 0)
    {
        cout<<"File size: "<<file_stat.st_size<<" bytes"<<endl;
        cout<<"Last modified time: "<<ctime(&file_stat.st_mtime);
    }
    else
        cout<<"Failed to get file info!";
    //return 0;
}
