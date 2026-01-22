# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11
DEBUGFLAGS = -g

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Target executable
TARGET = Assn.run

# Source and Object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Ensure obj directory exists and compile .cpp files into obj/*.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up compiled files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

