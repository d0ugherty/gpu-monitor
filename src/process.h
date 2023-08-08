#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
    public:
        Process(int pid);
        double getCpuUsage();
        int getPid();
    private:
        int pid;
        long utime;
        long stime;
        void readStatFile();
        std::string to_string();
};

#endif
