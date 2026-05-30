#pragma once

#include "defines.h"

typedef enum memory_tag {
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MMEORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCREN,

    // Always be the last tag
    MEMORY_TAG_MAX_TAGS
} memory_tag;

void initialize_memory();
void shutdown_memeory();

VAPI void *vallocate(u64 size, memory_tag tag);
VAPI void  vfree(void *block, u64 size, memory_tag tag);
VAPI void *vzero_memory(void *block, u64 size);
VAPI void *vcopy_memory(void *dest, const void *source, u64 size);
VAPI void *vset_memory(void *block, i32 value, u64 size);
VAPI char *get_memory_useage_str();