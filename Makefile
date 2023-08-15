
## MAKEFILE

#VARIABLES
CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lstdc++ -lnvidia-ml -L/usr/share/doc/libimgui-dev
TARGET = build/gpumon


# RULES

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp cpu.cpp monitor.cpp gpu.cpp $(LDFLAGS)

clean:
	rm -f $(TARGET)	

.PHONY: all-clean

