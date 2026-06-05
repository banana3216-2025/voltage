#define _POSIX_C_SOURCE 200809L

#include "defines.h"
#include "vmemory.h"

#include "core/logger.h"
#include "platform/platform.h"

//  TODO: custom string libary
#include <string.h>
#include <stdio.h>

// Make strdup work for windows and linux without changing code
#if VPLATFORM_WINDOW
  #define strdup _strdup
#endif

struct memory_stats {
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
} memory_stats;

static struct memory_stats stats;

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "
};

VAPI void initialize_memory() {
    platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory() {

}

VAPI void *vallocate(u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) { VWARN("vallocate called with MEMORY_TAG_UNKNOWN. Re-class this allocation"); }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    // TODO: memory aligment
    void *block = platform_allocate(size, FALSE);
    platform_zero_memory(block, size);
    return block;
}

VAPI void vfree(void *block, u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) { VWARN("vfree called with MEMORY_TAG_UNKNOWN. Re-class this allocation"); }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    // TODO: memory aligment
    platform_free(block, FALSE);
}

VAPI void *vzero_memory(void *block, u64 size) { return platform_zero_memory(block, size); }
VAPI void *vcopy_memory(void *dest, const void *source, u64 size) { return platform_copy_memory(dest, source, size); }
VAPI void *vset_memory(void *block, i32 value, u64 size) { return platform_set_memory(block, value, size); }

char *get_memory_useage_str() {
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    char buffer[8000] = "System memory use (tagged)\n";
    u64 offset = strlen(buffer);
    for (int i=0; i < MEMORY_TAG_MAX_TAGS; i++) {
        char unit[4] = "XiB";
        float amount = 1.0f;

        if (stats.tagged_allocations[i] >= gib) {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)gib;
        } else if (stats.tagged_allocations[i] >= mib) {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)mib;
        } else if (stats.tagged_allocations[i] >= kib) {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)kib;
        } else {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, "  %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }

    char *out_string = strdup(buffer);
    return out_string;
}