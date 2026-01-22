# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# .cpp source files in src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# .o files generated from .cpp sources
COMPILED_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Precompiled .o files (like SatComRelay.o, VehData.o)
EXTERNAL_OBJS = $(wildcard $(OBJ_DIR)/*.o)

# Final object list to link (avoid duplication)
OBJS = $(sort $(COMPILED_OBJS) $(EXTERNAL_OBJS))

# Output binary
TARGET = $(BIN_DIR)/Main.run

# Default target
all: $(TARGET)

# Link all object files into final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile .cpp into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean only newly created .o files (not precompiled ones)
clean:
	# Remove only newly created object files
	rm -f $(COMPILED_OBJS) $(TARGET)

.PHONY: all clean

