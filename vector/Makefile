.PHONY: all clean

CC                    := gcc
CFLAGS                := -Wall -g -std=gnu99
INCLUDE_PATH          := ../common
LIBRARY_PATH          := ../lib
LIBRARY_VERSION       := 0.0.1

VECTOR_UNIT_TEST_PROG := vector_unit_test
VECTOR_UNIT_TEST_SRCS := vector_unit_test.c vector.c vector_print.c
VECTOR_UNIT_TEST_OBJS := $(patsubst %.c,%.o,$(VECTOR_UNIT_TEST_SRCS))

VECTOR_LIB_TARGET     := libvector.so.$(LIBRARY_VERSION)
VECTOR_LIB_SRCS       := vector.c vector_print.c

all: build_vector_unit_test build_vector_lib

build_vector_unit_test:
	$(CC) $(CFLAGS) -c $(VECTOR_UNIT_TEST_SRCS) -I $(INCLUDE_PATH)
	$(CC) $(CFLAGS) -o $(VECTOR_UNIT_TEST_PROG) $(VECTOR_UNIT_TEST_OBJS)

build_vector_lib:
	$(CC) -shared -o $(LIB_DIR)/$(VECTOR_LIB_TARGET) -I $(INCLUDE_PATH) -fPIC $(VECTOR_LIB_SRCS)

clean:
	rm -rf *.o
	rm -rf $(VECTOR_UNIT_TEST_PROG)