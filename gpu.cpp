#include <nvml.h>
#include <string>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "gpu.h"
#include "nvml_try.h"

Gpu::Gpu(unsigned int index){
    initialize_device(index);
}

void Gpu::initialize_device(unsigned int index){
    this->index = index;
    set_device_features();
    set_device_info();
}

void Gpu::set_device_features(){
    if(nvmlDeviceGetMemoryInfo(this->handle, &this->memory) == NVML_SUCCESS) {
        &this->features |= MEMORY_INFO;
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
}

void Gpu::set_device_info(){

}

void Gpu::display_info(){

}

void Gpu::watch_info(unsigned int interval){

}

