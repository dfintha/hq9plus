BINARY_HQ9P=bin/hq9+
BINARY_H9P=bin/h9+
BINARY_HQ9PP=bin/hq9++

CXX=clang++
CXXFLAGS=-std=c++14 -Wall -Wextra -Werror -pedantic -O2

.PHONY: all, clean

all: $(BINARY_HQ9P) $(BINARY_H9P) $(BINARY_HQ9PP)

loc:
	@printf "[N] "
	@cat src/*| wc -l

$(BINARY_HQ9P): src/interpreter.cpp
	@mkdir -p bin
	@printf "[B] $@\n"
	@$(CXX) $(CXXLAGS) -c $< -o $@.o
	@$(CXX) $@.o -o $@
	@rm -f $@.o

$(BINARY_H9P): src/interpreter.cpp
	@mkdir -p bin
	@printf "[B] $@\n"
	@$(CXX) -DH9PLUS_MODE $(CXXFLAGS) -c $< -o $@.o
	@$(CXX) $@.o -o $@
	@rm $@.o

$(BINARY_HQ9PP): src/interpreter.cpp
	@mkdir -p bin
	@printf "[B] $@\n"
	@$(CXX) -DHQ9PLUSPLUS_MODE $(CXXFLAGS) -c $< -o $@.o
	@$(CXX) $@.o -o $@
	@rm $@.o

clean:
	@printf "[R] bin\n"
	@rm -rf bin

