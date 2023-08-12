#include <nvml.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "nvml_try.h"
#include "gpu.h"
#include "monitor.h"

/**
 * TO-DO: CPU information
 *
 * Might refactor this and divide it between GPU & CPU
 */
Monitor::Monitor(){
    nvml_try(__func__,nvmlDeviceGetCount_v2(&this->device_count));
    NVML_TRY(__func__,nvmlSystemGetDriverVersion(driver_version, std::size(driver_version)));
    for(unsigned int i = 0; i < device_count; i++) {
        struct gpu dev;
        initialize_device(dev,i);
    } 
}

/**
 * Initialize the GPU information and add
 * device to the class' "devices" vector
 *
 */
void Monitor::initialize_device(struct gpu &dev, int index) {
    dev.index = index;
    nvml_try(__func__,nvmlDeviceGetHandleByIndex_v2(dev.index, &dev.handle));
    get_device_features(dev);
    get_device_info(dev); 
    devices.push_back(dev);
}

/**
 * Check for supported GPU features
 *
 */
void Monitor::get_device_features(struct gpu &dev) {
    
    if(nvmlDeviceGetMemoryInfo(dev.handle, &dev.memory) == NVML_SUCCESS) {
        dev.features |= MEMORY_INFO;
    }

    if(nvmlDeviceGetUtilizationRates(dev.handle, &dev.utilization) == NVML_SUCCESS) {
        dev.features |= UTILIZATION_INFO;
    }

    if(nvmlDeviceGetTemperature(dev.handle, NVML_TEMPERATURE_GPU, &dev.temperature) == NVML_SUCCESS) {
        dev.features |= TEMPERATURE;
    }
    
    if(nvmlDeviceGetPowerUsage(dev.handle, &dev.power_usage) == NVML_SUCCESS) {
        dev.features |= POWER_USAGE;
    }

    if(nvmlDeviceGetClock(dev.handle, NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT, &dev.clock_speed) == NVML_SUCCESS) {
        dev.features |= CLOCK_INFO;
    }

    if(nvmlDeviceGetFanSpeed(dev.handle, &dev.fan_speed) == NVML_SUCCESS) {
        dev.features |= FAN_INFO;
    }
    
    if(nvmlDeviceGetComputeMode(dev.handle, &dev.mode) == NVML_SUCCESS) {
        dev.features |= COMPUTE_MODE;
    }
}


/**
 * NVML API calls to retrieve GPU  information
 *
 * TO DO: Figure out Clock info
 * 
 */
void Monitor::get_device_info(struct gpu &dev){
    nvml_try(__func__, nvmlDeviceGetPciInfo_v3(dev.handle, &dev.pci));

    if(dev.features & MEMORY_INFO) {
        nvml_try(__func__,nvmlDeviceGetMemoryInfo(dev.handle, &dev.memory));
    }

    if(dev.features & UTILIZATION_INFO) {
        nvml_try(__func__,nvmlDeviceGetUtilizationRates(dev.handle, &dev.utilization));
    }
    
    if(dev.features & TEMPERATURE) {
        nvml_try(__func__,nvmlDeviceGetTemperature(dev.handle, NVML_TEMPERATURE_GPU, &dev.temperature));
    } 
    
    if(dev.features & POWER_USAGE) {
        nvml_try(__func__,nvmlDeviceGetPowerUsage(dev.handle, &dev.power_usage));
    }

    if(dev.features & CLOCK_INFO) {
        nvml_try(__func__,nvmlDeviceGetClock(dev.handle, NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT, &dev.clock_speed));
    }  
    
    if(dev.features & FAN_INFO) {
        nvml_try(__func__,nvmlDeviceGetFanSpeed(dev.handle, &dev.fan_speed));
    }

    if(dev.features & COMPUTE_MODE) {
        nvml_try(__func__, nvmlDeviceGetComputeMode(dev.handle, &dev.mode));
    }

    nvml_try(__func__,nvmlDeviceGetName(dev.handle, dev.name, sizeof(dev.name)));
    nvml_try(__func__,nvmlDeviceGetSerial(dev.handle, dev.serial, sizeof(dev.serial))); // not suppored on my gpu
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


