# Makefile

# Variables
CC = g++
CFLAGS = -Wall -O3
LDFLAGS =

# Source directory
SRC_DIR = src

# Object directory
OBJ_DIR = obj

# Binary directory# Makefile

# Variables
CC = g++
CFLAGS = -Wall -O3 -I/opt/homebrew/opt/sfml/include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source directory
SRC_DIR = src

# Object directory
OBJ_DIR = obj

# Binary directory
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Target
TARGET = $(BIN_DIR)/main

# Create directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)/*  # Remove all files under /obj directory
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Target
TARGET = $(BIN_DIR)/main

# Create directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)/*  # Remove all files under /obj directory