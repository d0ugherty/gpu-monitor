#include <string>
#include "process.h"

Process::Process(int pid) : pid(pid) {
    readStatFile();
}

