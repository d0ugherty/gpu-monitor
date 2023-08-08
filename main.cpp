#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <proc/readproc.h>
#include <algorithm>
#include "process.h"

void print_proc_list();
int print_stats(int pid);
bool isNumber(const std::string& dir_name);

using namespace std;

int main() {
    
    //print_proc_list();
    int pid = 350786;
    Process new_process = Process(pid);
    std::cout << "Process " << pid << " CPU usage is " << new_process.getCpuUsage() << std::endl; 
    return 0;
}


void print_proc_list() {
    DIR* proc_dir = opendir("/proc"); 
    
    if(!proc_dir) {
        std::cerr << "Failed to open /proc directory" << std::endl;
    }

    struct dirent* entry;
    
    while((entry = readdir(proc_dir)) != nullptr) {
        std::cout << "Entry name: " << entry ->d_name << std::endl;
        
        if(isNumber(entry -> d_name)){
            int pid =  std::atoi(entry -> d_name);
            print_stats(pid);
        }
    }
    
    closedir(proc_dir);
}

int print_stats(int pid) {
    std::string stat_filepath = "/proc/" + std::to_string(pid) + "/stat";
    std::ifstream stat_file(stat_filepath);

    if(!stat_file) {
        std::cerr << "Failed to open process stat file \n";
        return 1;
    }

    std::string proc_stats;
    std::getline(stat_file, proc_stats);
    
    stat_file.close();

    std::cout << "Process: " << pid << " statistics: " << proc_stats << std::endl;
    
    return 0;
}

bool isNumber(const std::string& dir_name) {
    return !dir_name.empty() && std::all_of(dir_name.begin(), dir_name.end(), ::isdigit);
}
    






























