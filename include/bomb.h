#ifndef BOMB_H_
#define BOMB_H_

#include <player.h>
#include <game.h>
#include <SDL/SDL_stdinc.h>
#include <bomb.h>

struct bomb;

void bomb_new(struct game* game, struct player* player);

void update_bomb(struct game* game);

void explosion(struct game* game, struct bomb* bomb);

void destroyer(struct game* game, int x, int y, int explosion_stop);

void remove_bomb(struct game* game,struct bomb* bomb, struct bomb* prevBomb);

void explosion_cleaning(struct game* game, struct bomb* bomb) ;

#endif /* BOMB_H_ */
