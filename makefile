PREFIX := $(shell brew --prefix)
CXX := g++

# Compiler flags: C++2b standard, maximum optimization
CXXFLAGS := -std=c++2b -O3 -I$(PREFIX)/include

# Linker flags: SFML libraries and prefix
LDFLAGS := -L$(PREFIX)/lib -lsfml-window -lsfml-graphics -lsfml-system

SRCS := main.cpp Ball.cpp Physics.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := phys_sim

.PHONY: release clean

# Default release target
release: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)