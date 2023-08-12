#ifndef CPU_H
#define CPU_H

#include <vector>

class Cpu {
public:
    Cpu();
    double get_load();
    void watch_load(unsigned int interval);
private:
    double utilization;
    double set_load(unsigned int interval);
    long get_cpu_time();
    std::vector<long long> get_idle();

};
#endif
