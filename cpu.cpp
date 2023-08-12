#include "cpu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <math.h>


Cpu::Cpu() {
    utilization = set_load(2);
}

double Cpu::set_load(unsigned interval_sec){
    long cpu_time_1, cpu_time_2;

    cpu_time_1 = get_cpu_time();

    std::this_thread::sleep_for(std::chrono::seconds(interval_sec));

    cpu_time_2 = get_cpu_time();

    if (cpu_time_1 == -1 || cpu_time_2 == -1) {
        std::cerr << "Failed to read CPU usage" << std::endl;
        return 1;
    }

    //calculate utilization percentage
    double delta = cpu_time_2 - cpu_time_1;
    double total_time = interval_sec * 100;
    double utilization =  delta / total_time;
    
    return utilization;
}

/**
 * Return current utilization of CPU 
 * 
 */
double Cpu::get_load(){
    return utilization;
}
    
/**
 * Retrieves the total CPU time excluding idle time
 *
 */
long Cpu::get_cpu_time(){
    std::ifstream stat_file("/proc/stat");
    
    if(!stat_file){
        std::cerr << "/proc/stat not found" << std::endl;
        return 1;
    }
    //parse file
    std::string line;
    std::getline(stat_file,line);
    stat_file.close();

    std::istringstream iss(line);

    std::string cpu_label;
    long user, nice, system, idle;

    iss >> cpu_label >> user >> nice >> system >> idle;

    long total_cpu_time = user + nice + system;
    return total_cpu_time;
}
