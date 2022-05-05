SOURCES := $(wildcard src/*.cpp)
INCLUDES := $(wildcard src/*.h)

all: main

main: $(SOURCES) $(INCLUDES)
	g++ -o $@ $(SOURCES)
