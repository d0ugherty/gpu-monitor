#ifndef MONITOR_H
#define MONITOR_H

#include <nvml.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "gpu.h"

/**
 * Singleton design to ensure only one instance of the 
 * Monitor is active at any given time
 * 
*/
class Monitor {
public:
    void display_info();
    void watch_info(int interval);
    static Monitor* getInstance();
private:
    unsigned int device_count;;
    std::vector<Gpu> devices;
    static Monitor* mon_;

    Monitor();
    Monitor(const Monitor&);
    Monitor& operator=(const Monitor&);
};

#endif
