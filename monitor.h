#include <nvml.h>
#include <stdio.h>
#include <string>

#include "device.h"


class Monitor {
    public:
        Monitor();
        void initialize_device(struct device* dev);
        void get_device_info(struct device dev);
        
    private:
        unsigned int device_count;
        bool is_running;
        int interval;
};
