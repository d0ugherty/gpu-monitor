#ifndef GPU_H
#define GPU_H

#include <nvml.h>
#include <string>
#include <vector>

#include "nvml.h"


/**
 * At compile time, structs in C++ are treated as classes. I would have made
 * the GPU a class for the sake of consistency but the NVML API (written in C)
 * requres a struct
 *
 * */
struct Gpu {
public:
    Gpu(unsigned int index);
    void display_info();
    void watch_info(unsigned int interval);
    std::string info_string();
   
    const char* get_name();
    std::string get_driver_version();

    std::vector<unsigned int> get_device_info();

    int get_power_usage();
    int get_temperature();
    std::tuple<unsigned int, unsigned int> get_utilization();
    nvmlMemory_t get_memory_info();

    int get_fan_speed();
    int get_clock_speed();
    
    void set_device_info();


private:
    unsigned int index;
    nvmlDevice_t handle;

    nvmlPciInfo_t pci;
    nvmlMemory_t memory;
    nvmlUtilization_t utilization;
    nvmlComputeMode_t mode;

    unsigned int temperature;
    unsigned int power_usage;

    nvmlClockType_t clock[NVML_CLOCK_COUNT], max_clock[NVML_CLOCK_COUNT];
    unsigned int clock_speed;
    unsigned int fan_speed;
    unsigned int features;
    char driver_version[128];

    char name[NVML_DEVICE_NAME_BUFFER_SIZE];
    char serial[NVML_DEVICE_SERIAL_BUFFER_SIZE];
    char uuid[NVML_DEVICE_UUID_BUFFER_SIZE];

    void set_device_features();    
};

enum feature {
    TEMPERATURE      = 1 << 0,  // Bit 0: 0000 0001
    COMPUTE_MODE     = 1 << 1,  // Bit 1: 0000 0010
    POWER_USAGE      = 1 << 2,  // Bit 2: 0000 0100
    MEMORY_INFO      = 1 << 3,  // Bit 3: 0000 1000
    CLOCK_INFO       = 1 << 4,  // Bit 4: 0001 0000
    FAN_INFO         = 1 << 5,  // Bit 5: 0010 0000
    UTILIZATION_INFO = 1 << 6   // Bit 6: 0100 0000
};

#endif
