# Ajusta esto con tu compilador
CXX = clang++ -std=c++17

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses 

FLAGS = -DDEBUG -D_GLIBCXX__PTHREADS -g -O0 $(WARN) -Wno-invalid-source-encoding

INCLUDE = -I.


all: test

test: solitaire.hpp test.cpp
	$(CXX) $(FLAGS) $(INCLUDE) $@.cpp -o $@

clean:
	$(RM) *~ test
