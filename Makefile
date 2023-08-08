
## MAKEFILE

#VARIABLES
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lstdc++
TARGET = build/procmon


# RULES

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp process.cpp $(LDFLAGS)

clean:
	rm -f $(TARGET)	

.PHONY: all-clean

