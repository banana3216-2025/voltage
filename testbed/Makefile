TARGET := ../bin/testbed
SRC_DIR := src
OBJ_DIR := obj

SRCS := $(shell find . -type f -name "*.c")
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC := clang
CFLAGS := -g -fdeclspec -fPIC -O0 -include ../engine/src/core/logger.h -Wno-format -Wno-format-security
INCLUDES := -Isrc -I../engine/src
LDFLAGS := -L../bin -lengine -Wl,-rpath,'$$ORIGIN' -Wl,-rpath,.
DEFINES := -D_DEBUG -DKIMPORT

.PHONY: all clean

all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(DEFINES) $(INCLUDES) $(LDFLAGS)

# Compile C source files to object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
