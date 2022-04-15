CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test main_bin main

my_matrix.o: my_matrix.cpp my_matrix.hpp
	$(CC) $(FLAGS) my_matrix.cpp -c

test_bin: my_matrix.o test.cpp
	$(CC) $(FLAGS) my_matrix.o test.cpp -o test_bin $(TEST_LIBS)

main_bin: my_matrix.o main.cpp
	$(CC) $(FLAGS) my_matrix.o main.cpp -o main_bin

main: main_bin
	./main_bin

test: test_bin
	./test_bin