#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include "process.h"

Process::Process(int pid) : pid(pid) {
    readStatFile();
}

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

double Process::getCpuUsage(int pid) {
}    
