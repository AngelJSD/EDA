GCC = g++
CXXFLAGS = -std=c++11 -pthread -o main.o

all:
	$(GCC) $(CXXFLAGS) main.cpp
