#include "lib/imgui/imgui.h"
#include "lib/imgui/backends/imgui_impl_opengl3.h"
#include "lib/imgui/backends/imgui_impl_sdl2.h"

#include <string>
#include <iostream>
#include <nvml.h>
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL2/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

#include "cpu.h"
#include "gpu.h"
#include "monitor.h"
#include "gui.h"
#include "error.h"

void print_proc_list();
int print_stats(int pid);


int main() {
    NVML_TRY(nvmlInitWithFlags(NVML_INIT_FLAG_NO_GPUS));
    std::cout << "\n";

     //imgui init
    Gui gui = Gui("dark");
    gui.run();
    gui.shutdown();

    nvmlShutdown();
    return 0;
}































