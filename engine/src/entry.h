#pragma once

#include "core/applications.h"
#include "core/logger.h"
#include "game_types.h"
#include "core/vmemory.h"

// Externally defined function to create a game;
extern b8 create_game(game *out_game);

/**
 *  The main entry point of the application
 */
int main(void) {

    initialize_memory();

    game game_inst;
    if (!create_game(&game_inst)) { VFATEL("Could not create game!!"); return -1; }

    if (
        !game_inst.render ||
        !game_inst.update || 
        !game_inst.initialize || 
        !game_inst.on_resize
    ) {
        VFATEL("The game's function pointers must be assigned");
        return 2;
    }

    if (!application_create(&game_inst)) { VFATEL("Application failed to create"); return 1; }
    if (!application_run()) { VFATEL("application did not shutdwon gracefully"); return 2; }

    initialize_memory();

    return 0;
}