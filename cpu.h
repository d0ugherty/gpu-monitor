#ifndef CPU_H
#define CPU_H

#include <vector>

namespace Cpu {
        double get_load(unsigned interval_seconds);
        long get_cpu_time();
        std::vector<long long> get_idle();

}
#endif
