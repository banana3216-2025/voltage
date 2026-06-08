TARGET := ../bin/testbed.exe
SRC_DIR := src
OBJ_DIR := obj

SRCS := $(shell find . -type f -name "*.c")
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC := clang
# REMOVED -fPIC
CFLAGS := -g -fdeclspec -O0 -include ../engine/src/core/logger.h -Wno-format -Wno-format-security
INCLUDES := -Isrc -I../engine/src

# CHANGED: Replaced Linux rpath flags with standard Windows library directory linking
LDFLAGS := -L../bin -lengine
# Ensure this line in testbed/Makefile looks like this:
DEFINES := -D_DEBUG -DKIMPORT -DVAPI="__declspec(dllimport)"

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
