CC=gcc
CFLAGS=-g -Wall
OBJS=lexer.o
EXE=phantom

TEST_DIR=tests
TEST_EXE=phantom_tests

all: phantom

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

phantom: $(OBJS) main.c
	$(CC) $(CFLAGS) -o $@ $^

# TODO: Look at the "proper" way to do tests via a makefile
#       I'm kind of just doing my own thing here and somebody
#       who knows gnumake is gonna look at this and cringe
test: $(OBJS) $(TEST_DIR)/test.c
	$(CC) $(CFLAGS) -o $(TEST_DIR)/$(TEST_EXE) $^
	./$(TEST_DIR)/$(TEST_EXE)

clean_test:
	rm $(TEST_DIR)/$(TEST_EXE)

clean:
	rm $(EXE) *.o *.gch
