SOURCES := $(wildcard src/*.cpp)
INCLUDES := $(wildcard src/*.h)
OBJ := $(patsubst src/%.cpp,bin/%.o, $(SOURCES))

CC_OPTIONS := -g -fsanitize=address

check:
	@echo $(SOURCES)
	@echo $(INCLUDES)
	@echo $(OBJ)


all: main

bin/%.o: src/%.cpp
	g++ -c -o $@ $^

main: $(SOURCES) $(INCLUDES) $(OBJ)
	# @ g++ -o $@ $(SOURCES) $(CC_OPTIONS)
	g++ -o $@ $(OBJ) $(CC_OPTIONS)
