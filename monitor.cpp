#include <nvml.h>
#include <stdio.h>
#include <string>

#include "monitor.h"

Monitor::Monitor(){
    nvmlReturn_t result;
    result = nvmlDeviceGetCount_v2(&this->device_count);
    
    for(int i = 0; i < device_count; i++){
        struct device* dev;
        initialize_device(dev);
    }
}
