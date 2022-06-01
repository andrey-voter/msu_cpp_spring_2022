CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
LINK_FLAGS=-o
TEST_LIBS=-lgtest_main -lgtest -lpthread
SRC=thread_pool

.PHONY: test clean
all: test

test: $(SRC).o test.o
	$(CC) $(FLAGS) $(LINK_FLAGS) $@ $^ $(TEST_LIBS)
%.o: %.cxx
	$(CC) $(FLAGS) -c $^ -o $@
clean:
	rm -f *.o test test_asan test_cov *.gcda *.gcno *.info
