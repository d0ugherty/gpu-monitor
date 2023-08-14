#include <nvml.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "nvml_try.h"
#include "gpu.h"
#include "cpu.h"
#include "monitor.h"

/**
 * TO-DO: CPU information
 */

Monitor* Monitor::mon_ = NULL;

Monitor::Monitor(){
    //initialize GPUs
    nvmlDeviceGetCount_v2(&this->device_count);
    for(unsigned int index = 0; index < device_count; index++) {
        struct Gpu device = Gpu(index);
        devices.push_back(device);
    } 

    //initialize CPU
}

Monitor* Monitor::getInstance(){
    if(mon_ == NULL){
        mon_ = new Monitor();
    }
    return(mon_);
}

/**
 * Print device information to the terminal
 *
 * would like to implement a GUI at some point
 */
void Monitor::display_info() {

    for(unsigned int i = 0; i < device_count; i++) {
        devices[i].watch_info(1);
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
    while(true) {
        display_info();
        std::this_thread::sleep_for(std::chrono::seconds(interval)); 
    }
}

