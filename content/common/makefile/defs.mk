CC = gcc
MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
CPPFLAGS += -I $(MAKEFILE_DIR)/../utils
CFLAGS += -g -Wall -Wextra -Werror
