CC = g++	# use g++ for compiling c++ code
CFLAGS = -g -Wall -std=c++11		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.

all: test
SRCS = graph.cpp heap.cpp main.cpp
DEPS = $(SRCS:.cpp=.d)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

test: main.o graph.o heap.o
	$(CC) heap.o graph.o main.o -o prog9
	
clean:
	rm *.o prog9
