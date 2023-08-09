

#include <nvml.h>
#include <string>

struct device {
    public:
        unsigned int  index;
        nvmlDevice_t handle;

        nvmlPciInfo_t pci;
        nvmlMemory_t memory;
        nvmlUtilization_t utilization;
        
        unsigned int temperature;

        unsigned int power_usage;

        nvmlClockType_t clock[NVML_CLOCK_COUNT], max_clock[NVML_CLOCK_COUNT];

        unsigned int fan_speed;

        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        char serial[NVML_DEVICE_SERIAL_BUFFER_SIZE];
        char uuid[NVML_DEVICE_UUID_BUFFER_SIZE];

        unsigned int features;

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
