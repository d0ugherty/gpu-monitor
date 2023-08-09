
## MAKEFILE

#VARIABLES
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lstdc++ -lnvidia-ml
TARGET = build/gpumon


# RULES

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp cpu.cpp monitor.cpp $(LDFLAGS)

clean:
	rm -f $(TARGET)	

.PHONY: all-clean

