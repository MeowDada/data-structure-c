.PHONY: all clean

CC                      := gcc
CFLAGS                  := -Wall -g -std=gnu99

INCLUDE_PATH            := ../common

SINGLE_LINKED_LIST_PROG := single_linked_list_test
SINGLE_LINKED_LIST_SRCS := single_linked_list_test.c single_linked_list.c 
SINGLE_LINKED_LIST_OBJS := $(patsubst %.c,%.o,$(SINGLE_LINKED_LIST_SRCS))

all: build_single_linked_list_test

build_single_linked_list_test
	$(CC) $(CFLAGS) -c $(SINGLE_LINKED_LIST_SRCS) -I $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -o $(SINGLE_LINKED_LIST_PROG) $(SINGLE_LINKED_LIST_OBJS)

clean:
	rm -rf *.o
	rm -rf $(SINGLE_LINKED_LIST_PROG)