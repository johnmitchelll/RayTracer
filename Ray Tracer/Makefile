# Compiler and flags
CXX = g++
CXXFLAGS = -I/usr/local/Cellar/sfml/2.6.2/include/ -std=c++11 -Wall -Wextra -Werror
LDFLAGS = -L/usr/local/Cellar/sfml/2.6.2/lib/ -lsfml-graphics -lsfml-window -lsfml-system

# Source directories
SRCDIR = .
CPPDIR = CPP

# Automatically find all .cpp files in root and CPP directory
SRCS = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(CPPDIR)/*.cpp)

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main

# Build and run
run: clear_terminal $(TARGET)
	@echo "Cleaning up object files..."
	rm -f $(OBJS)
	@echo "Running the program..."
	./$(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean: clear_terminal
	rm -f $(OBJS) $(TARGET)

# Clear terminal at the start
clear_terminal:
	clear
