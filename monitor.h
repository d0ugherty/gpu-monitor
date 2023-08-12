#ifndef MONITOR_H
#define MONITOR_H

//#define NVML_TRY(func, ret_value) nvml_try(__func__, ret_value)
#include <nvml.h>
#include <string>
#include <vector>
#include <iostream>
#include "gpu.h"

class Monitor {
public:
    Monitor();
    void get_device_info(struct gpu &dev);
    void display_info();
    void watch_info(int interval);
private:
    void initialize_device(struct gpu &dev, int index); 
    unsigned int device_count;
    char driver_version[128];
    std::vector<gpu> devices;
    bool is_running;
    int nvml_try(const char function_name[16], nvmlReturn_t ret_value);
    void get_device_features(struct gpu &dev);
};

#endif
