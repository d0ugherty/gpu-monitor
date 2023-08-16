
## MAKEFILE

#VARIABLES
IMGUI_DIR = lib/imgui

CXX = g++

CXXFLAGS += -g -Wall -Wformat

CXXFLAGS = -std=c++11 -lstdc++ -lnvidia-ml -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

SOURCES = main.cpp cpu.cpp monitor.cpp gpu.cpp gui.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp 

TARGET = gpumon

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
LINUX_GL_LIBS = -lGL

# RULES

UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    ECHO_MESSAGE = "Linux"
    LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`
    CXXFLAGS += `sdl2-config --cflags`
endif


%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(TARGET)
	@echo Build complete for $(ECHO_MESSAGE)


$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)

