# Compiler
CXX = g++

# Path
SRC_PATH = src
BUILD_PATH = build

# Executable 
EXE = go

# Source 
SOURCES = $(SRC_PATH)/PA3_106501001.cpp 
OBJECTS = $(BUILD_PATH)/PA3_106501001.o 

# Compiler flags
CXXFLAG = -O3 -Wall
INCLUDE = -I$(SRC_PATH) 

# Make-command list
.PHONY: all run clean

# Target: Dependencies
# 	Shell-command
all: $(BUILD_PATH) $(EXE)


run: $(EXE)
	./go 

clean:
	@echo "Removing objects"
	@rm -rf $(BUILD_PATH)
	@echo "Removing executable file"
	@rm -rf $(EXE)

$(EXE): $(OBJECTS)
	@echo "Generating executable file: $^ -> $@"
	@$(CXX) $^ -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	@echo "Compiling: $< -> $@"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_PATH):
	
	@echo "Creating object directory"
	@mkdir -p $@
