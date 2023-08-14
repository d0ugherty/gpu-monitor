#include <string>
#include <iostream>
#include "cpu.h"
#include <nvml.h>

#include "gpu.h"
#include "monitor.h"

void print_proc_list();
int print_stats(int pid);
bool isNumber(const std::string& dir_name);

int main() {
    nvmlReturn_t result;
    result = nvmlInitWithFlags(NVML_INIT_FLAG_NO_GPUS);

    if(result != NVML_SUCCESS) {
        std::cerr << "Error initializing NVML: " << nvmlErrorString(result) << std::endl;
        return 1;
    }


    std::cout << "\n";
    Monitor _monitor = Monitor();
    _monitor.watch_info(1);
    nvmlShutdown();
    return 0;
}































