# Makefile for Real Estate Sales Management System

# Variables
CC = g++
CFLAGS = -std=c++11 -Wall -g
EXECUTABLE = resms

# The main target
all: $(EXECUTABLE)

# Link the object files to create the executable
$(EXECUTABLE): project.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) project.o

# Compile the main source file
project.o: project.cpp Data.h Agent.h Property.h
	$(CC) $(CFLAGS) -c project.cpp

# Clean up build artifacts
clean:
	rm -f *.o $(EXECUTABLE)
