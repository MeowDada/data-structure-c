.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99

INCLUDE_PATH          := ../common

QUEUE_TEST_PROG       := queue_test
QUEUE_TEST_SRCS       := queue_test.c queue.c queue_impl_by_array_.c queue_impl_by_linked_list.c queue_impl_by_vector.c
QUEUE_TEST_OBJS       := $(patsubst %.c,%.o,$(QUEUE_TEST_SRCS))

all: build_queue_test

build_queue_test:
	$(CC) $(CFLAGS) -c $(QUEUE_TEST_SRCS) -I $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -o $(QUEUE_TEST_PROG) $(QUEUE_TEST_OBJS)

clean:
	rm -rf *.
	rm -rf $(QUEUE_TEST_PROG)