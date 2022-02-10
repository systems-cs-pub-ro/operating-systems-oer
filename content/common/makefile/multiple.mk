all: $(BINARIES)

# Get the relative path to the directory of the current makefile.
MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILE_DIR)/linux.mk

clean::
	-rm -f $(BINARIES)

.PHONY: all clean
