#ifndef MONITOR_H
#define MONITOR_H

//#define NVML_TRY(func, ret_value) nvml_try(__func__, ret_value)
#include <nvml.h>
#include <string>
#include <iostream>

//#include "nvml_try.h"
#include "device.h"

class Monitor {
    public:
        Monitor();
        void get_device_info(struct device dev);
        void initialize_device(struct device &dev, int index);
    private:
        unsigned int device_count;
        bool is_running;
        int interval;
       // void initialize_device(struct device &dev, int index);
       // wrapper function to error check the nvmlReturn_t values
       // instead of wrapping each call in a try-catch block
      // static inline int nvml_try(std::string& functionName, nvmlReturn_t ret_value);         
};

#endif
