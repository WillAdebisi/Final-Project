# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source and object files
SRC = src/main.cpp src/Event.cpp src/SaveSystem.cpp
OBJ = $(SRC:.cpp=.o)

# Output binary name
TARGET = game

# Default build rule
all: $(TARGET)

# Link object files to create final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files to .o files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean command
clean:
	rm -f src/*.o $(TARGET)
