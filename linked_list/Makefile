.PHONY: all clean

CC                      := gcc
CFLAGS                  := -Wall -g -std=gnu99

INCLUDE_PATH            := ../common
LIBRARY_PATH            := ../lib

SINGLE_LINKED_LIST_PROG := single_linked_list_test
SINGLE_LINKED_LIST_SRCS := single_linked_list_test.c single_linked_list.c 
SINGLE_LINKED_LIST_OBJS := $(patsubst %.c,%.o,$(SINGLE_LINKED_LIST_SRCS))

LINKED_LIST_LIB_TARGET  := libllist.so
LINKED_LIST_LIB_SRCS    := linked_list.c

all: build_single_linked_list_test build_linked_list_lib

build_single_linked_list_test:
	$(CC) $(CFLAGS) -c $(SINGLE_LINKED_LIST_SRCS) -I $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -o $(SINGLE_LINKED_LIST_PROG) $(SINGLE_LINKED_LIST_OBJS)

build_linked_list_lib:
	$(CC) $(CFLAGS) -shared -o $(LIBRARY_PATH)/$(LINKED_LIST_LIB_TARGET) -I $(INCLUDE_PATH) -fPIC $(LINKED_LIST_LIB_SRCS)

clean:
	rm -rf *.o
	rm -rf $(SINGLE_LINKED_LIST_PROG)