#ifndef PLAYER_H_
#define PLAYER_H_

#include <map.h>
#include <constant.h>

struct player;

extern int nl;
// Creates a new player with a given number of available bombs
struct player* player_init(short bomb_number);
void   player_free(struct player* player);

// Returns the current position of the player
int player_get_x(struct player* player);
int player_get_y(struct player* player);

// Set the direction of the next move of the player
void player_set_current_way(struct player * player, enum direction direction);

// Set, Increase, Decrease the number of bomb that player can put
int  player_get_nb_bomb(struct player * player);
void player_inc_nb_bomb(struct player * player);
void player_dec_nb_bomb(struct player * player);

// Set, Increase, Decrease the number of key that player can put
int  player_get_nb_key(struct player * player);
void player_inc_nb_key(struct player * player);
void player_dec_nb_key(struct player * player);

//Set, increase, decrease the number of lives that player can put
short player_get_nb_lives(struct player* player);
void player_inc_nb_lives(struct player* player);
void player_dec_nb_lives(struct player* player);

// Load the player position from the map
void player_from_map(struct player* player, struct map* map);

// Move the player according to the current direction
int player_move(struct player* player, struct map* map);

// Display the player on the screen
void player_display(struct player* player);

//
int player_move_aux(struct player* player, struct map* map, int x, int y);

int player_get_scope(struct player* player);
void player_inc_scope(struct player* player);
void player_dec_scope(struct player* player);


#endif /* PLAYER_H_ */