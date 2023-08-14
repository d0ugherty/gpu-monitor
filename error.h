#include <nvml.h>
#include <iostream>


/**
* the macro expands to a call to the nvml_try function, 
* passing the return value of the NVML function 
* and a string representation of the function code.
*
* '#code' turns the code argument into a string
*/
#define NVML_TRY(code) nvml_try(code, #code)

/**
 * Macro for error handling instead of putting each
 * NVML call inside a try-catch block.
 *
 * INPUT: calling function name, NVML API return enum
 * OUTPUT: 1 (FAIL) 0 (SUCCESS)
 */
static inline int nvml_try(nvmlReturn_t ret, const std::string fn)
{
  if(ret != NVML_SUCCESS && ret != NVML_ERROR_TIMEOUT) {
    std::cout << "Error at " << fn << ": " << nvmlErrorString(ret) << "\n";
    return 1;
  }

  return 0;
}

