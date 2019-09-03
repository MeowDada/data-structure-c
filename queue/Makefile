.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99

INCLUDE_PATH          := ../common ../vector
LIBRARY_PATH          := ../lib

QUEUE_TEST_PROG       := queue_test
QUEUE_TEST_SRCS       := queue_test.c queue.c queue_impl_by_array.c queue_impl_by_linked_list.c queue_impl_by_vector.c
QUEUE_TEST_OBJS       := $(patsubst %.c,%.o,$(QUEUE_TEST_SRCS))
QUEUE_TEST_LIBS       := vector

all: build_queue_test

build_queue_test:
	$(CC) $(CFLAGS) -c $(QUEUE_TEST_SRCS) $(addprefix -I,$(INCLUDE_PATH))
	$(CC) $(CFLAGS) -o $(QUEUE_TEST_PROG) $(QUEUE_TEST_OBJS) -L$(LIBRARY_PATH) -l$(QUEUE_TEST_LIBS)

clean:
	rm -rf *.
	rm -rf $(QUEUE_TEST_PROG)