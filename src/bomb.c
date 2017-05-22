#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>

#include "bomb.h"
#include <game.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
//#include <bomb.h>

struct bomb {
	int x;
	int y;
	short level;
	int explosed;
	int scope;
	int time;

	struct bomb * next_bomb;
};

void bomb_new(struct game* game, struct player* player) {

	if (player_get_nb_bomb(player)>=1) {

		struct bomb * bomb = malloc(sizeof(struct bomb));
		bomb->x=player_get_x(player);
		bomb->y=player_get_y(player);
		bomb->scope = player_get_scope(player);
		bomb->level=game_get_current_level(game);
		bomb->time=SDL_GetTicks();
		bomb->explosed=0;
		bomb->next_bomb = game_get_bomb(game);
		game_set_bomb(game,bomb);
		player_dec_nb_bomb(player);
	}
}


void update_bomb(struct game* game){
	int t = SDL_GetTicks();
	struct map* map = game_get_current_map(game);

	struct bomb* bomb = game_get_bomb(game);
	struct bomb* prevBomb=NULL;

	while (bomb!=NULL) {
		int time = (t - bomb->time);
		if (game_get_current_level(game)==bomb->level) {
			if (time<=1000)
				map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB4);

			else if (time>1000 && time<=2000)
				map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB3);

			else if (time>2000 && time<=3000)
				map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB2);

			else if (time>3000 && time<=4000)
				map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB1);


			if( time>4000 && time<=4500 && bomb->explosed==0) {
				explosion(game, bomb);
			}

			if(time>4500) {
				explosion_cleaning(game, bomb);
				//remove_bomb(game ,bomb, prevBomb);
			}

			prevBomb=bomb;
			bomb=bomb->next_bomb;
		}
	}
}

void explosion(struct game* game, struct bomb* bomb) {
	int x = bomb->x;
	int y = bomb->y;
	int scope = bomb->scope;
	int explosion_stop = 0;
	struct map* map = game_get_current_map(game);
	map_set_cell_type(map, x, y, CELL_BOMB5);
	for (int i = x; i <= x + scope; i++ ) {
		if (!explosion_stop) {
		destroyer(game, i, y, explosion_stop); // explosion for positive x
			}
	}
	explosion_stop = 0;
	for (int i = x-1; i >= x-scope-1; i-- ) {
		if (!explosion_stop) {
			destroyer(game,i,y, explosion_stop); // explosion for negative x
		}
	}
	explosion_stop = 0;
	for (int i = y; i <= y + scope; i++ ) {
		if (!explosion_stop) {
			destroyer(game, x, i, explosion_stop);// explosion for positive y
		}
	}
	explosion_stop = 0;
	for (int i = y-1; i >= y-scope-1; i-- ) {
		if (!explosion_stop) {
			destroyer(game, x, i, explosion_stop); // explosion for negative y
		}
	}
	bomb->explosed=1;
}

void destroyer(struct game* game, int x, int y, int explosion_stop) {
	struct map* map=game_get_current_map(game);
	struct player* player=game_get_player(game);

	if (map_is_inside(map,x,y)) {
		unsigned char type = map_get_cell_type(map,x,y);

		switch (type) {
		case CELL_BOX:
			switch(map_get_cell_subtype(map,x,y)) {
			case BONUS_BOMB_RANGE_INC:
				map_set_cell_type(map, x, y, CELL_BONUS_BOMB_INC);
				break;

			case BONUS_BOMB_RANGE_DEC:
				map_set_cell_type(map, x, y, CELL_BONUS_BOMB_DEC);
				break;

			case BONUS_BOMB_NB_DEC:
				map_set_cell_type(map, x, y, CELL_BONUS_BOMB_NB_DEC);
				break;

			case BONUS_BOMB_NB_INC:
				map_set_cell_type(map, x, y, CELL_BONUS_BOMB_NB_INC);
				break;
			case BONUS_MONSTER:
				map_set_cell_type(map, x, y, CELL_EMPTY);
				//fonction qui fait apparaitre les monstres
				break;
			case BONUS_LIFE:
				map_set_cell_type(map, x, y, CELL_BONUS_LIFE);
				break;
			default:
				map_set_cell_type(map, x, y, CELL_EMPTY);
			}
			explosion_stop = 1;
			break;
		case CELL_BONUS:
			map_set_cell_type(map,x,y, CELL_EMPTY);
			break;
		case CELL_SCENERY:
			explosion_stop = 1;
			break;
		case CELL_MONSTER:
			// Fonction qui tue les monstres
			break;
		case CELL_EMPTY:
			map_set_cell_type(map,x,y, CELL_BOMB5);
			break;
		case CELL_PLAYER:
			player_dec_nb_lives(player);
			break;
		}
	}

}

/*void bomb_change_timer(struct game* game, int diffTime) {
	struct bomb* bomb=game_get_bomb(game);
	while (bomb!=NULL) {
		bomb->timer=bomb->timer+diffTime;
		bomb=bomb->next_bomb;
	}
}*/

void remove_bomb(struct game* game,struct bomb* bomb, struct bomb* prevBomb) {
	if (prevBomb==NULL) {
		game_set_bomb(game,bomb->next_bomb);
	}
	else if (bomb->next_bomb==NULL) {
		prevBomb->next_bomb=NULL;
	}
	else {
		prevBomb->next_bomb=bomb->next_bomb;
	}

	free(bomb);
	player_inc_nb_bomb(game_get_player(game));

}

void explosion_cleaning(struct game* game, struct bomb* bomb) {
	struct map* map= game_get_current_map(game);
	int x=bomb->x;
	int y=bomb->y;
	int scope = bomb->scope;
	for (int i= x-scope; i<=x+scope; i++) {
		if(map_is_inside(map,i,y)) {
			if(map_get_cell(map,i,y) == CELL_BOMB5 ) {
				map_set_cell_type(map, i, y, CELL_EMPTY);
			}
		}
	}

	for (int i= y-scope; i<=y+scope; i++) {
		if(map_is_inside(map,x,i)) {
			if(map_get_cell(map,x,i) == CELL_BOMB5 ) {
				map_set_cell_type(map,x , i, CELL_EMPTY);
			}
		}
	}

}

/*void remove_bomb_explosion_sprite(struct game* game, struct bomb* bomb) {
	struct map* map= game_get_current_map(game);
	int x=bomb->x;
	int y=bomb->y;
	int range = bomb->scope;

	for (int i= x-range; i<=x+range; i++) {
		if(map_is_inside(map,i,y)) {
			if(map_get_cell_type(map,i,y) == CELL_BOMB && map_get_cell_subtype(map,i,y)==BOMB_0)
				map_set_cell_type(map, i, y, CELL_EMPTY);
		}

	}

	for (int i= y-range; i<=y+range; i++) {
		if(map_is_inside(map,x,i)) {
			if(map_get_cell_type(map,x,i) == CELL_BOMB && map_get_cell_subtype(map,x,i) == BOMB_0)
				map_set_cell_type(map,x , i, CELL_EMPTY);
		}

	}

}
void bomb_save_info(struct bomb* first_bomb, FILE* txt_info) {

	struct bomb* bomb=first_bomb;
	while(bomb!=NULL) {
		fprintf(txt_info,"\n%d %d %d %d %d %d", bomb->x, bomb->y,bomb->range, SDL_GetTicks()-bomb->timer,bomb->level,bomb->explosed);
		bomb=bomb->next_bomb;
	}
	fprintf(txt_info," end-bomb\n");
}*/



