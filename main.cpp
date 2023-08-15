#include "lib/imgui/imgui.h"
#include "lib/imgui/backends/imgui_impl_opengl3.h"
#include "lib/imgui/backends/imgui_impl_sdl2.h"

#include <string>
#include <iostream>
#include <nvml.h>


#include "cpu.h"
#include "gpu.h"
#include "monitor.h"
#include "error.h"

void print_proc_list();
int print_stats(int pid);


int main() {
    NVML_TRY(nvmlInitWithFlags(NVML_INIT_FLAG_NO_GPUS));
    std::cout << "\n";

    // imgui init
    /*IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    //ImGui_ImplSDL2_InitForOpenGL(window, YOUR_SDL_GL_CONTEXT);
    ImGui_ImplOpenGL3_Init();
    
    ImGui::ShowDemoWindow();*/

    Monitor* mon = Monitor::getInstance();
    mon->watch_info(1);

    nvmlShutdown();
    return 0;
}































