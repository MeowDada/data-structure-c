.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99
INCLUDE_PATH          := ../common

VECTOR_UNIT_TEST_PROG := vector_unit_test
VECTOR_UNIT_TEST_SRCS := vector_unit_test.c vector.c vector_print.c
VECTOR_UNIT_TEST_OBJS := $(patsubst %.c,%.o,$(VECTOR_UNIT_TEST_SRCS))

all:
	$(CC) $(CFLAGS) -c $(VECTOR_UNIT_TEST_SRCS) -I $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -o $(VECTOR_UNIT_TEST_PROG) $(VECTOR_UNIT_TEST_OBJS)

clean:
	rm -rf *.o
	rm -rf $(VECTOR_UNIT_TEST_PROG)