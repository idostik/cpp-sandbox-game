NAME = sandbox_game
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -g -O2
LDFLAGS = -lncurses
TESTFLAGS = -DTEST

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)
OBJS = $(SOURCES:src/%.cpp=build/%.o)
TOBJS = $(SOURCES:src/%.cpp=build_test/%.o)

.PHONY: all compile valgrind run doc clean count

all: compile doc

compile: $(NAME)

# create the executable
$(NAME): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

run: compile
	./$(NAME)

# run with valgrind
valgrind: $(NAME)
	valgrind ./$(NAME)

# run with adress sanitizer
debug: $(OBJS)
	$(CXX) $^ -o $(NAME)_debug -fsanitize=address $(LDFLAGS)
	./$(NAME)_debug

# compile tests (with TESTFLAGS)
test: $(TOBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# run tests
test_run: test
	./test

# create documentation
doc:
	doxygen Doxyfile

# remove all generated files
clean:
	rm -rf build
	rm -f $(NAME) $(NAME)_debug
	rm -f Makefile.d
	rm -rf doc
	rm -rf .vscode
	rm -f test
	rm -rf build_test

# count number of lines
count:
	wc -l $(SOURCES) $(HEADERS)

# compile individual files
build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# compile individual files with test flags
build_test/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(TESTFLAGS) -c $^ -o $@

# create dependencies
Makefile.d: $(SOURCES) $(HEADERS)
	$(CXX) -MM $(SOURCES) > Makefile.d

include Makefile.d
