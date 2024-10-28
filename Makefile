# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source files
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/window/*.cpp) $(wildcard $(SRC_DIR)/texture/*.cpp) $(wildcard $(SRC_DIR)/shader/*.cpp) $(wildcard $(SRC_DIR)/renderer/*.cpp) $(wildcard $(SRC_DIR)/model/*.cpp) $(wildcard $(SRC_DIR)/vendor/stb_image/*.cpp)

# Output executable
OUTPUT = main

# Libraries and frameworks
LIB_DIR = lib
LIBS = -L./$(LIB_DIR) -lglfw3 -framework Cocoa -framework IOKit -framework CoreFoundation

# Build target
$(OUTPUT): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(LIBS) -o $(OUTPUT)

# Clean target
clean:
	rm -f $(OUTPUT)