#include <nvml.h>
#include <string>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "gpu.h"
//#include "nvml_try.h"

Gpu::Gpu(unsigned int index){
    initialize_device(index);
}


void Gpu::initialize_device(unsigned int index){
    this->index = index;
    nvmlDeviceGetHandleByIndex_v2(index, &this->handle);

    nvmlDeviceGetName(this->handle, this->name, sizeof(this->name));
    nvmlDeviceGetSerial(this->handle, this->serial, sizeof(this->serial));
    nvmlDeviceGetUUID(this->handle, this->uuid, sizeof(this->uuid));

    set_device_features();
    set_device_info();
}
/**
 * Feature check using bitwise operations
 * 
*/
void Gpu::set_device_features(){

    if(nvmlDeviceGetMemoryInfo(this->handle, &this->memory) == NVML_SUCCESS) {
        features |= MEMORY_INFO;
    }

    if(nvmlDeviceGetUtilizationRates(this->handle, &this->utilization) == NVML_SUCCESS) {
        features |= UTILIZATION_INFO;
    }

    if(nvmlDeviceGetTemperature(this->handle, NVML_TEMPERATURE_GPU, &this->temperature) == NVML_SUCCESS) {
        features |= TEMPERATURE;
    }
    
    if(nvmlDeviceGetPowerUsage(this->handle, &this->power_usage) == NVML_SUCCESS) {
        features |= POWER_USAGE;
    }

    if(nvmlDeviceGetClock(this->handle, NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT, &this->clock_speed) == NVML_SUCCESS) {
        features |= CLOCK_INFO;
    }

    if(nvmlDeviceGetFanSpeed(this->handle, &this->fan_speed) == NVML_SUCCESS) {
        features |= FAN_INFO;
    }
    
    if(nvmlDeviceGetComputeMode(this->handle, &this->mode) == NVML_SUCCESS) {
        features |= COMPUTE_MODE;
    }
}

/**
 * Retrieve GPU statistics
 * 
*/

void Gpu::set_device_info(){
    nvmlDeviceGetPciInfo_v3(this->handle, &this->pci);

    if(this->features & MEMORY_INFO) {
        nvmlDeviceGetMemoryInfo(this->handle, &this->memory);
    }

    if(this->features & UTILIZATION_INFO){
        nvmlDeviceGetUtilizationRates(this->handle, &this->utilization);
    }

    if(this->features & TEMPERATURE){
        nvmlDeviceGetTemperature(this->handle,NVML_TEMPERATURE_GPU, &this->temperature);
    }
    
    if(this->features & POWER_USAGE) {
        nvmlDeviceGetPowerUsage(this->handle, &this->power_usage);
    }
    
    if(this->features & CLOCK_INFO){
        //nvmlDeviceGetClock(this->handle, NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT, &this->clock_speed);
        nvmlDeviceGetClockInfo(this->handle, NVML_CLOCK_GRAPHICS, &this->clock_speed);
    }

    if(this->features & FAN_INFO){
        nvmlDeviceGetFanSpeed(this->handle, &this->fan_speed);
    }

    if(this->features & COMPUTE_MODE){
        nvmlDeviceGetComputeMode(this->handle, &this->mode);
    }
}

/**
 * Print GPU info to console
 * 
 * TO DO: GUI
*/
void Gpu::display_info(){
    std::cout << this->name << "            Driver Version: " << driver_version << "\n";
    std::cout << "TEMPERATURE: " << this->temperature << "C                     POWER USAGE: " << this->power_usage <<"mW\n\n";
    std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    std::cout << "POWER USAGE: " << this->power_usage <<"mW\n";
    std::cout << "LOAD: " << this->utilization.gpu << "%                        Memory: " << this->utilization.memory << "%\n\n";
    std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    std::cout << "CLOCK SPEED: " << this->clock_speed << "MHz\n";
    std::cout << "FAN SPEED: " << this->fan_speed << "% of Max\n\n";
    std::cout << "===================================================================\n\n";
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
void Gpu::watch_info(unsigned int interval){
    while(true) {
        set_device_info();    
        display_info();
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

