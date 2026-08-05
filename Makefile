CXX = g++

CXXFLAGS = -std=c++17 -Wall -O2

TARGET = cs509

SRC = \
./common_wrapper/main.cpp \
./common_wrapper/menu.cpp \
./assignment_01/src/io/graph_io.cpp \
./assignment_01/src/csr/csr.cpp \
./assignment_01/src/bfs/bfs.cpp \
./assignment_01/src/dfs/dfs.cpp \
./assignment_01/src/sssp/sssp.cpp \
./assignment_01/driver/driver.cpp 

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)


clean:
	rm -f $(TARGET)