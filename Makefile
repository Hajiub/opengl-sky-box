# Compiler
CC = clang++

# Source files
SRCS = main.cpp stb/stb_image.cpp core/camera.cpp core/mesh.cpp core/model.cpp core/shader.cpp utils/utils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o) glad/glad.o

# Executable name
EXEC = out

# Include directories
INCLUDE = -I./

# Libraries
LIBS = -lglfw -lGL -lassimp

# Compiler flags
CXXFLAGS = $(INCLUDE)

# Default target
all: $(EXEC)

# Rule for building the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIBS)

# Rule for building object files
%.o: %.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS)

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)

# Run the executable
run: $(EXEC)
	./$(EXEC)
