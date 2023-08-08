#include <string>
#include <iostream>
#include <fstream>
#include <sys/unistd.h>
#include <sys/types.h>
#include "process.h"

Process::Process(int pid) : pid(pid) {
    readStatFile();
}

int Process::getPid(){
    return pid;
}

/**
 * Function to get the CPU time shared by the process
 * 
 */
double Process::getCpuUsage() {
    long clock_ticks_per_sec = sysconf(_SC_CLK_TCK);
    std::cout << "Total clock ticks per secod: " << clock_ticks_per_sec << "\n";
    // u time = user time , stime = kernel time
    double cpu_time = (utime + stime) / static_cast<double>(clock_ticks_per_sec); //
    return cpu_time;
}

/**
 * Utility function to read the stat file of a process 
 *
 *
 */
void Process::readStatFile(){
    std::string stat_filepath = "/proc/" + std::to_string(pid) + "/stat";
    std::ifstream stat_file(stat_filepath);

    if(!stat_file) {
        std::cerr << "Failed to find stat file " << pid << std::endl;
        return;
    }

    std::string line;
    std::getline(stat_file, line);
    stat_file.close();

    std::sscanf(line.c_str(),"%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %ld %ld", &utime, &stime);
}
