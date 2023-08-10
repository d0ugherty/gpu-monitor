#include <string>
#include <iostream>
#include "cpu.h"
#include <nvml.h>
#include "device.h"
#include "monitor.h"

void print_proc_list();
int print_stats(int pid);
bool isNumber(const std::string& dir_name);

int main() {
    bool running = true;
    nvmlReturn_t result;
    result = nvmlInitWithFlags(NVML_INIT_FLAG_NO_GPUS);

    if(result != NVML_SUCCESS) {
        std::cerr << "Error initializing NVML: " << nvmlErrorString(result) << std::endl;
        return 1;
    }

    Monitor monitor = Monitor();
    monitor.display_info();
    std::cout << "\n";
    monitor.watch_info(10);
    nvmlShutdown();
    return 0;
}































