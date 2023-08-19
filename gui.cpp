#include "gui.h"
#include "gpu.h"


static void render(ImGuiIO io,ImVec4 clear_color, SDL_Window* window);
static void show_window(bool show_demo_window, bool show_another_window, ImVec4 clear_color, ImGuiIO& io, Gpu &device);
static void start_frame();
static void handle_event(bool &done, SDL_Window* &window);

/**
 * Breaking this down into serveral functions so
 * it's actually readable...
 * 
 * to me at least
 * 
*/


 Gui::Gui(const std::string style, Gpu &device) : device(device) {
    this->device = device;
    //setup_sdl();
    setup_window();
    setup_context();
    style_color(style);
    setup_backends();
    load_fonts();
    init_state();
}

/**
 * Main loop to run the GUI
 * 
*/
void Gui::run(){
    bool done = false;
    while (!done) {
        device.set_device_info();
        handle_event(done, this->window);

        // Start the Dear ImGui frame
        start_frame();

        //display window
        show_window(show_demo_window, show_another_window, this->clear_color, this->io, this->device);

        // Rendering
        render(io, this->clear_color, this->window);
    }
}

int Gui::setup_sdl(){
     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }
    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif
    return 0;
}

void Gui::setup_window(){
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    this->window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    this->window = SDL_CreateWindow("Resource Monitor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    this->gl_context = SDL_GL_CreateContext(this->window);
    SDL_GL_MakeCurrent(this->window, this->gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
}

void Gui::setup_context(){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->io = ImGui::GetIO(); (void)io;
    this->io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    this->io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Control
}

/**
 * Light & Dark style setting
*/
void Gui::style_color(const std::string &color){
    if(color == "dark" ){
        ImGui::StyleColorsDark();
    } else {
        ImGui::StyleColorsLight();
    }
}

void Gui::setup_backends() {
    ImGui_ImplSDL2_InitForOpenGL(this->window, this->gl_context);
    ImGui_ImplOpenGL3_Init();
}

void Gui::load_fonts(){
    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);
}

void Gui::init_state(){
    this->show_demo_window = true;
    this->show_another_window = false;
}

void Gui::shutdown(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * Helper functions for main loop
 * 
*/

// Event handler
static void handle_event(bool &done, SDL_Window* &window){
     SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
}

static void start_frame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

static void show_window(bool show_demo_window, bool show_another_window, ImVec4 clear_color, ImGuiIO& io, Gpu &gpu){
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
     // Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {

        ImGui::Begin(gpu.get_name());                          

        ImGui::Text("Utilization");
        float test = gpu.get_device_info()[2];
        ImGui::ProgressBar(test/100.0);  
        ImGui::Text("Clock Speed");
        //const char clock[16] = gpu.get_device_info()[4];
        //ImGui::Text(clock);
        float mem_total = gpu.get_memory_info().total;
        //float mem_free = gpu.get_memory_info().free;
        float mem_used = gpu.get_memory_info().used;
        ImGui::Text("Memory");
        ImGui::Text("%f/%f", mem_used, mem_total);
        ImGui::ProgressBar(mem_used / mem_total);
        
                 // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color


        ImGui::End();
    }
}

//Render function for main loop
static void render(ImGuiIO io,ImVec4 clear_color, SDL_Window* window){
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}