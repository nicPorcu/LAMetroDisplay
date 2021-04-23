CC = g++
CXX =g++

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++11

LDFLAGS = -g
LDLIBS  = -ljsoncpp -lcurl 

executables = main
objects = main.o

.PHONY: default
default: $(executables)

$(executables): $(objects) 



