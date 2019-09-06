.PHONY: all clean

CC                 := gcc
CFLAGS             := -Wall -Wno-unused-value -Wno-unsed-function -Wno-pointer-to-int-cast -g -std=gnu99
INCLUDE_PATH       := ../common

HASHMAP_TEST_PROG  := hashmap_test
HASHMAP_TEST_SRCS  := hashmap_test.c hashmap.c hashmap_impl.c hashmap_chaining.c hash_func.c hash_equal_func.c
HASHMAP_TEST_OBJS  := $(patsubst %.c,%.o,$(HASHMAP_TEST_SRCS))

all: build_hashmap_test

build_hashmap_test:
	$(CC) $(CFLAGS) -c $(HASHMAP_TEST_SRCS) -I $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -o $(HASHMAP_TEST_PROG) $(HASHMAP_TEST_OBJS)

clean:
	rm -rf *.o
	rm -f $(HASHMAP_TEST_PROG)