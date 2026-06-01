#include "core/event.h"
#include "core/vmemory.h"
#include "core/logger.h"
#include "containers/darray.h"

// TODO: add event priority for events

// The lowest level 1 object per event
typedef struct registered_event {
    void *listner;
    PFN_on_event callback;
} registered_event;

// A container to hold multiple of the same event
typedef struct event_code_entry {
    registered_event *events;
} event_code_entry;

#define MAX_MESSAGE_CODES 16384

typedef struct event_system_state {
    event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

static b8 is_initialized = FALSE;
static event_system_state state;

b8 event_initialize() {
    if (is_initialized == TRUE) return FALSE;
    vzero_memory(&state, sizeof(state));
    is_initialized = TRUE;

    VDEBUG("Event system initialized");
    return TRUE;
}

void event_shutdown() {
    for (u16 i=0; i < MAX_MESSAGE_CODES; i++) {
        if (state.registered[i].events != 0 ) {
            darray_destroy(state.registered[i].events);
            state.registered[i].events = 0;
        }
    }
}

b8 event_register(u16 code, void *listner, PFN_on_event on_event) {
    if (is_initialized == FALSE) return FALSE;

    if (state.registered[code].events == 0) {
        state.registered[code].events = darray_create(registered_event);
    }

    u64 registered_count = darray_length(state.registered[code].events);
    for (u64 i=0; i < registered_count; i++) {
        if (state.registered[code].events[i].listner == listner) {
            VWARN("event listner already create, failed to register. Event code: %i", code);
            return FALSE;
        }
    }

    registered_event event;
    event.listner = listner;
    event.callback = on_event;
    darray_push(state.registered[code].events, event);

    return TRUE;
}

b8 event_unregister(u16 code, void *listner, PFN_on_event on_event) {
    if (is_initialized == FALSE) return FALSE;
    if (state.registered[code].events == 0) { VWARN("event_unregister called but event code not yet initialized, doing nothing"); return FALSE; }

    u64 registered_count = darray_length(state.registered[code].events);
    for (u64 i=0; i < registered_count; i++) {
        if (state.registered[code].events[i].listner == listner) {
            registered_event popped_event;
            darray_pop_at(state.registered[code].events, i, &popped_event);
            return TRUE;
        }
    }

    return FALSE;
}

// TODO: multi-theading

b8 event_fire(u16 code, void *sender, event_context context) {
    if (is_initialized == FALSE) return FALSE;
    if (state.registered[code].events == 0) { VWARN(" event_fire called but event code not yet initialized, doing nothing"); return FALSE; }

    u64 registered_count = darray_length(state.registered[code].events);
    for (u64 i=0; i < registered_count; i++) {
        registered_event e = state.registered[code].events[i];
        if (e.callback(code, sender, e.listner, context)) {
            return TRUE;
        }
    }

    return FALSE;
}