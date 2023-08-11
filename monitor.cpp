#include <nvml.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "monitor.h"

/**
 * TO-DO: Add feature check
 *
 *
 */
Monitor::Monitor() {
    nvmlReturn_t result;
    result = nvmlDeviceGetCount_v2(&this->device_count);
    nvml_try(__func__,nvmlSystemGetDriverVersion(driver_version, std::size(driver_version)));
    if (result == NVML_SUCCESS) {
        for(unsigned int i = 0; i < device_count; i++) {
            struct device dev;
            initialize_device(dev,i);
        }
    } else {
        std::cerr << "Error initiailizing GPU monitor: " << nvmlErrorString(result) << std::endl;
    }
}

/**
 * Initialize the device information and add
 * device to the class' "devices" vector
 *
 */
void Monitor::initialize_device(struct device &dev, int index) {
    dev.index = index;
    get_device_info(dev); 
    devices.push_back(dev);
}

/**
 * NVML API calls to retrieve device information
 *
 * TO DO: Figure out Clock info
 * 
 */
void Monitor::get_device_info(struct device &dev){

    nvml_try(__func__, nvmlDeviceGetHandleByIndex_v2(dev.index, &dev.handle));

    nvml_try(__func__, nvmlDeviceGetPciInfo_v3(dev.handle, &dev.pci));

    nvml_try(__func__,nvmlDeviceGetMemoryInfo(dev.handle, &dev.memory));

    nvml_try(__func__,nvmlDeviceGetUtilizationRates(dev.handle, &dev.utilization));
    nvml_try(__func__,nvmlDeviceGetTemperature(dev.handle, NVML_TEMPERATURE_GPU, &dev.temperature));
    nvml_try(__func__,nvmlDeviceGetPowerUsage(dev.handle, &dev.power_usage));

    nvml_try(__func__,nvmlDeviceGetClock(dev.handle, NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT, &dev.clock_speed));
//  nvmlDeviceGetClockInfo(__func__,dev.handle, NVML_CLOCK_SM, &dev.clock[NVML_CLOCK_SM]);
    nvml_try(__func__,nvmlDeviceGetFanSpeed(dev.handle, &dev.fan_speed));

    nvml_try(__func__,nvmlDeviceGetName(dev.handle, dev.name, sizeof(dev.name)));
    nvml_try(__func__,nvmlDeviceGetSerial(dev.handle, dev.serial, sizeof(dev.serial)));
    nvml_try(__func__,nvmlDeviceGetUUID(dev.handle, dev.uuid, sizeof(dev.uuid)));
}

/**
 * Print device information to the terminal
 *
 * would like to implement a GUI at some point
 */
void Monitor::display_info() {

    for(unsigned int i = 0; i < device_count; i++) {
        
        get_device_info(devices[i]);
        
        std::cout << "\nDEVICE: " << devices[i].name << "\n";
        std::cout << "TEMPERATURE: " << devices[i].temperature << "C\n";
        std::cout << "POWER USAGE: " << devices[i].power_usage << "mW\n";
        //std::cout << "USAGE RATE: " << devices[i].utilization << "%\n";
        std::cout << "FAN SPEED: " << devices[i].fan_speed << " of Max Speed\n";
    }

}

/**
 * Print device information to the terminal repetitively
 * according to a specified polling interval.
 *
 * This is a simple, yet inefficient polling function.
 *
 * TO DO: learn a better way to do this
 *
 */
void Monitor::watch_info(int interval) {
    std::cout << driver_version << "\n";
    while(true) {
        display_info();
        std::this_thread::sleep_for(std::chrono::seconds(interval)); 
    }
}

/**
 * Wrapper function for error handling instead of putting each
 * NVML call inside a try-catch block.
 *
 * TO DO: To implement this
 */
int Monitor::nvml_try(const char function_name[16], nvmlReturn_t ret_value) {
    if(ret_value != NVML_SUCCESS && ret_value != NVML_ERROR_TIMEOUT) {
        std::cerr << "Error at " << function_name << ": " << nvmlErrorString(ret_value) <<std::endl;
        return 1;
    }
    return 0;
}
