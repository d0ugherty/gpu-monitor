#ifndef NVML_TRY_H
#define NVML_TRY_H

#include <nvml.h>
#include <iostream>

/**
 * Macro for error handling instead of putting each
 * NVML call inside a try-catch block.
 *
 * INPUT: calling function name, NVML API return enum
 * OUTPUT: 1 (FAIL) 0 (SUCCESS)
 */
#define NVML_TRY(function_name, ret_value) \
    do { \
        if ((ret_value) != NVML_SUCCESS && (ret_value) != NVML_ERROR_TIMEOUT) { \
            std::cerr << "Error at " << (function_name) << ": " << nvmlErrorString(ret_value) << std::endl; \
            return 1; \
        } \
    } while (false)

#endif