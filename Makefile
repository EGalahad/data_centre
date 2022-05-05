SOURCES := $(wildcard src/*.cpp)
INCLUDES := $(wildcard src/*.h)

CC_OPTIONS := -g -fsanitize=address

all: main

main: $(SOURCES) $(INCLUDES)
	g++ -o $@ $(SOURCES) $(CC_OPTIONS)
