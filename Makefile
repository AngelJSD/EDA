GCC = g++
CXXFLAGS = -std=c++11 -pthread -o main.o

pbstree:
	@$(GCC) $(CXXFLAGS) BSTree_p/main.cpp
	@./main.o

mtx:
	@$(GCC) $(CXXFLAGS) Matrix/main.cpp
	@./main.o

clean:
	rm main.o
