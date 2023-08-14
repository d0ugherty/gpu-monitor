#include <string>
#include <iostream>
#include "cpu.h"
#include <nvml.h>

#include "gpu.h"
#include "monitor.h"
#include "error.h"

void print_proc_list();
int print_stats(int pid);
bool isNumber(const std::string& dir_name);

int main() {
    NVML_TRY(nvmlInitWithFlags(NVML_INIT_FLAG_NO_GPUS));
    std::cout << "\n";

    Monitor* mon = Monitor::getInstance();
    mon->watch_info(1);

    nvmlShutdown();
    return 0;
}































