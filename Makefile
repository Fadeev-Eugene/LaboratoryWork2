CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
GTEST_FLAGS = -lgtest -lgtest_main

all: tests

tests: test.o
	$(CXX) $(CXXFLAGS) -o tests test.o $(GTEST_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o main tests
