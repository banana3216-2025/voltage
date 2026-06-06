TARGET := ../bin/libengine.so
SRC_DIR := src
OBJ_DIR := obj

# Find all .c files recursively
SRCS := $(shell find . -type f -name "*.c")
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC := clang
CFLAGS := -g -shared -fdeclspec -fPIC -Wno-format -Wno-format-security
INCLUDES := -Isrc -I$(VULKAN_SDK)/include
LDFLAGS := -lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$(VULKAN_SDK)/lib -L/usr/X11R6/lib
DEFINES := -D_DEBUG -DKEXPORT

.PHONY: all clean

all: $(TARGET)

# Link the shared library
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(DEFINES) $(INCLUDES) $(LDFLAGS)

# Compile C source files to object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

