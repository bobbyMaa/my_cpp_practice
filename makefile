CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -g
TARGET   := main

SRCS := main.cpp $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(OBJS) $(TARGET)

.PHONY: all clean
