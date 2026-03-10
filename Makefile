CXX = g++    # g++ is the compiler used
CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude -O3  # Uses -O3 optimization

# Find all .cpp files in src directory
SRCS = $(wildcard src/*.cpp) # To find every .cpp file in src directory
OBJS = $(patsubst src/%.cpp,build/%.o,$(SRCS)) # To assign names for .o files in build directory

# Windows output has .exe extension
ifeq ($(OS),Windows_NT)
    TARGET = analyzer.exe
	RM_DIR = rmdir /s /q
    RM = del /q
    RM_OBJS = del /q src\*.o 2>nul || rm -f src/*.o
else
    TARGET = analyzer
    RM = rm -f
	RM_DIR = rm -rf
    RM_OBJS = rm -f src/*.o
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

build/%.o: src/%.cpp # Putting objects files in new build directory.
	@if not exist build mkdir build       
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist build $(RM_DIR) build
	$(RM_OBJS)
	$(RM) $(TARGET)

.PHONY: all clean   # To make sure that these are not considered as files
