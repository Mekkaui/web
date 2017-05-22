#ifndef GAME_H_
#define GAME_H_

#include <player.h>
#include <map.h>
#include <bomb.h>

// Abstract data type
struct game;

// Create a new game
struct game* game_new();

// Free a game
void game_free(struct game* game);

// Return the player of the current game
struct player* game_get_player(struct game* game);

// Return the current map
struct map* game_get_current_map(struct game* game);

// Display the game on the screen
void game_display(struct game* game);

// update the game
int game_update(struct game* game);

// return the current level
short game_get_current_level(struct game* game) ;

// Set a bomb
void game_set_bomb( struct game* game, struct bomb* bomb ) ;

//Get a bomb
struct bomb* game_get_bomb(struct game* game);

#endif /* GAME_H_ */
