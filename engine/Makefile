TARGET := ../bin/engine.dll
SRC_DIR := src
OBJ_DIR := obj

# Find all .c files recursively using POSIX shell syntax
SRCS := $(shell find . -type f -name "*.c")
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

CC := clang
# REMOVED -fPIC and -shared from compiler flags on Windows
CFLAGS := -g -fdeclspec -Wno-format -Wno-format-security
INCLUDES := -Isrc -I"$(VULKAN_SDK)/include"

# CHANGED: Replaced Linux X11/xcb libraries with Windows Vulkan library
LDFLAGS := -shared -luser32 -L"$(VULKAN_SDK)/lib" -lvulkan-1
DEFINES := -D_DEBUG -DKEXPORT -DVAPI="__declspec(dllexport)"

.PHONY: all clean

all: $(TARGET)

# Link the shared library (DLL)
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
