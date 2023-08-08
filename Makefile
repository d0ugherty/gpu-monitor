
## MAKEFILE

#VARIABLES
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lstdc++
TARGET = build/procmon


# RULES

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) src/main.cpp src/process.cpp src/cpu.cpp $(LDFLAGS)

clean:
	rm -f $(TARGET)	

.PHONY: all-clean

