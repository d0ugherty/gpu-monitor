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

#include "gpu.h"

class Gui {
public:
    Gui(const std::string style, Gpu &device);
    void run();
    void shutdown();
private:
    SDL_WindowFlags window_flags;
    SDL_Window* window;
    SDL_GLContext gl_context;
    Gpu &device;
    ImGuiIO io;
    ///state 
    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;

    int setup_sdl();
    void setup_backends();
    void setup_window();
    void setup_context();
    void style_color(const std::string &style);
    void load_fonts();
    void init_state();

};