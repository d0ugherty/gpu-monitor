
#include <nvml.h>
#include <iostream>
#include <string>

#define NVML_TRY(code) nvml_try(code, #code)
#include "monitor.h"

/**
 * TO-DO: Add feature check
 *
 *
 */
Monitor::Monitor(){
    nvmlReturn_t result;
    result = nvmlDeviceGetCount_v2(&this->device_count);
    
    for(int i = 0; i < device_count; i++){
        struct device dev;
        initialize_device(dev,i);
    }
}

/**
 * Initialize device information
 *
 * TO DO: Add error handling
 */
void Monitor::initialize_device(struct device &dev, int index){
    dev.index = index;

    nvmlDeviceGetHandleByIndex_v2(dev.index, &dev.handle);

    nvmlDeviceGetPciInfo_v3(dev.handle, &dev.pci);

    nvmlDeviceGetMemoryInfo(dev.handle, &dev.memory);
    
    nvmlDeviceGetUtilizationRates(dev.handle, &dev.utilization);
    nvmlDeviceGetTemperature(dev.handle, NVML_TEMPERATURE_GPU, &dev.temperature);
    nvmlDeviceGetPowerUsage(dev.handle, &dev.power_usage);
    
    //nvmlDeviceGetClockInfo(dev.handle, NVML_CLOCK_COUNT, &dev.clock[NVML_CLOCK_COUNT]);
    
    nvmlDeviceGetName(dev.handle, dev.name, sizeof(dev.name));
    nvmlDeviceGetSerial(dev.handle, dev.serial, sizeof(dev.serial));
    nvmlDeviceGetUUID(dev.handle, dev.uuid, sizeof(dev.uuid));

    //add feature check
}

static inline int nvml_try(std::string& functionName, nvmlReturn_t ret_value) {
    if(ret_value != NVML_SUCCESS && ret_value != NVML_ERROR_TIMEOUT) {
        std::cerr << "Error at " << functionName << " with return return value " << ret_value <<std::endl;
            return 1;
    }
    return 0;
}
