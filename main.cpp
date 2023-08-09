#include <string>
#include <iostream>
#include "cpu.h"
#include <nvml.h>
#include "device.h"

void print_proc_list();
int print_stats(int pid);
bool isNumber(const std::string& dir_name);

using namespace Cpu;

int main() {
    
    
    //std::cout << "Process " << pid << " CPU usage is " << new_process.getCpuUsage() << std::endl; 
    //std::cout << 
    nvmlReturn_t result;
    result = nvmlInitWithFlags(NVML_INIT_FLAG_NO_GPUS);
    
    struct device dev;
    dev.index = 0;
    unsigned int count;
    result = nvmlDeviceGetHandleByIndex_v2(0, &dev.handle);
    nvmlDeviceGetName(dev.handle, dev.name, sizeof(dev.name));
    nvmlDeviceGetCount_v2(&count);
    std::cout << dev.name << std::endl;
        
    std::cout << count << std::endl;
    return 0;
}

    






























