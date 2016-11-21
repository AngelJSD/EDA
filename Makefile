CXX = g++
CXXFLAGS = -std=c++11 -pthread -o main.o

pbstree:
	@$(CXX) $(CXXFLAGS) BSTree_p/main.cpp
	@./main.o

mtx:
	@$(CXX) $(CXXFLAGS) Matrix/main.cpp
	@./main.o

qtree:
	@$(CXX) $(CXXFLAGS) QuadTree/main.cpp
	@./main.o

qptree:
	@$(CXX) $(CXXFLAGS) QuadPoint/main.cpp
	@./main.o

clean:
	rm *.o
