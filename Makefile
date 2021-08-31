CC = g++
DEBUG_FLAGS = -g
CFLAGS = -Wall -std=c++17
IncludeDir = include/
SRC = $(wildcard *.cpp)

debug:  $(SRC)
	$(CC) $(DEBUG_FLAGS) $(CFLAGS) $^ -I $(IncludeDir) -L lib -lraylib -lopengl32 -lwinmm -lgdi32 -o Snake.exe