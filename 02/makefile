CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test main_bin main

parser.o: Tokenparser.cpp Tokenparser.hpp
	$(CC) $(FLAGS) Tokenparser.cpp -c
	
test_bin: Tokenparser.o test.cpp
	$(CC) $(FLAGS) Tokenparser.o test.cpp -o test_bin $(TEST_LIBS)

main_bin: Tokenparser.o main.cpp
	$(CC) $(FLAGS) Tokenparser.o main.cpp -o main_bin

main:
	./main_bin

test:
	./test_bin
