MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILE_DIR)/defs.mk

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

$(OBJS): %.o: %.c

clean::
	-rm -f $(OBJS)

.PHONY: clean
