#include <SDL/SDL_image.h>
#include <assert.h>
#include <map.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <game.h>
#include <unistd.h>

struct player {
	int x, y;
	enum direction current_direction;
	short nb_bombs;
	short nb_keys;
	short nb_lives;
	int scope;
};

struct player* player_init(short bomb_number) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->current_direction = SOUTH;
	player->nb_bombs = bomb_number;
	player->nb_keys = 0;
	player->nb_lives = 3;
	player->scope = 1;

	return player;
}

void player_free(struct player* player) {
	assert(player);
	free(player);
}

int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}

void player_set_current_way(struct player* player, enum direction way) {
	assert(player);
	player->current_direction = way;
}

int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bombs;
}

void player_inc_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bombs += 1;
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bombs -= 1;
}

int player_get_nb_key(struct player* player) {
	assert(player);
	return player->nb_keys;
}

void player_inc_nb_key(struct player* player) {
	assert(player);
	player->nb_keys += 1;
}

void player_dec_nb_key(struct player* player) {
	assert(player);
	player->nb_keys -= 1;
}

short player_get_nb_lives(struct player* player) {
	assert(player);
	return player->nb_lives;
}

void player_inc_nb_lives(struct player* player) {
	assert(player);
	player->nb_lives += 1;
}

void player_dec_nb_lives(struct player* player) {
	assert(player);
	player->nb_lives -= 1;
}

int player_get_scope(struct player* player) {
	assert(player);
	return player->scope;
}

void player_inc_scope(struct player* player) {
	assert(player);
	player->scope += 1;
}

void player_dec_scope(struct player* player) {
	assert(player);
	player->scope -= 1;
}

void player_from_map(struct player* player, struct map* map) {
	assert(player);
	assert(map);

	int i, j;
	for (i = 0; i < map_get_width(map); i++) {
	  for (j = 0; j < map_get_height(map); j++) {	
	    if (map_get_cell_type(map, i, j) == CELL_PLAYER) {
	      player->x = i;
	      player->y = j;
	    }
	  }
	}
}

int player_move_aux(struct player* player, struct map* map, int x, int y) {


	if (!map_is_inside(map, x, y)) {
		return 0;
	}

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_BOX:
		return 2;
		break;

	case CELL_EMPTY:
		return 3;
		break;

	case CELL_BONUS:
		switch(map_get_cell_subtype(map,x,y)) {
		case BONUS_BOMB_RANGE_INC:
			return 41;
			break;

		case BONUS_BOMB_RANGE_DEC:
			return 42;
			break;

		case BONUS_BOMB_NB_DEC:
			return 43;
			break;

		case BONUS_BOMB_NB_INC:
			return 44;
			break;

		case BONUS_LIFE:
			return 45;
			break;
		}
		break;

		case CELL_DOOR:
			if ( (map_get_cell_subtype(map, x, y) & 1) == DOOR_OPENED)
			{
				return 5;
			}
			else
			{
				return 6;
			}
			break;


		case CELL_KEY:
			return 7;
			break;

		case CELL_BOMB:
			return 8;
			break;

		case CELL_MONSTER:
			break;

		case CELL_PLAYER:
			//return 0;
			break;

		default:
			break;
	}

	// Player has moved
	return 1;
}


int player_move(struct player* player, struct map* map) {
	int x = player->x;
	int y = player->y;
	int move = 0;
	switch (player->current_direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1) !=0 && player_move_aux(player, map, x, y-1)==2 && player_move_aux(player, map, x, y-2)==3) {
			map_set_cell_type(map, x, y-2, CELL_BOX);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y-1)==41) {
			player_inc_scope(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y-1)==42) {
			player_dec_scope(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y-1)==43) {
			player_dec_nb_bomb(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y-1)==44) {
			player_inc_nb_bomb(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y-1)==45) {
			player_inc_nb_lives(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y-1)==5) {
			player->y--;
			move=0;
		}
		else if (player_move_aux(player,map,x,y-1)==6) {
			if ( player->nb_keys > 0) {
				int cell = map_get_door_cell(map, x, y-1);
				map_set_cell_type(map, x, y-1, --cell);
				map_set_cell_type(map, x, y, CELL_EMPTY);
				player_dec_nb_key(player);
				move=0;
			}
		}
		else if (player_move_aux(player,map,x,y-1)==7) {
			player_inc_nb_key(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y--;
			move = 1;
		}
		else if (player_move_aux(player, map, x, y)==8) {
			map_set_cell_type(map, x, y, map_get_cell(map, x, y));
			player->y--;
			move = 0;
		}

		else if (player_move_aux(player, map, x, y - 1)==3) {
			player->y--;
			move = 1;
		}
		else {}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1) !=0 && player_move_aux(player, map, x, y+1)==2 && player_move_aux(player, map, x, y+2)==3) {
			map_set_cell_type(map, x, y+2, CELL_BOX);
			map_set_cell_type(map, x, y+1, CELL_EMPTY);
			player->y++;
			move = 1;
			//	 if the cell(x,y+1) is a box and cell(x,y+2) is empty we move
		}
		else if (player_move_aux(player,map,x,y+1)==41) {
			player_inc_scope(player);
			map_set_cell_type(map, x, y+1, CELL_EMPTY);
			player->y++;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y+1)==42) {
			player_dec_scope(player);
			map_set_cell_type(map, x, y+1, CELL_EMPTY);
			player->y++;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y+1)==43) {
			player_dec_nb_bomb(player);
			map_set_cell_type(map, x, y+1, CELL_EMPTY);
			player->y++;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y+1)==44) {
			player_inc_nb_bomb(player);
			map_set_cell_type(map, x, y-1, CELL_EMPTY);
			player->y++;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y+1)==45) {
			player_inc_nb_lives(player);
			map_set_cell_type(map, x, y+1, CELL_EMPTY);
			player->y++;
			move = 1;
		}
		else if (player_move_aux(player,map,x,y+1)==5) {
			player->y++;
			move=0;
		}
		else if (player_move_aux(player,map,x,y+1)==6) {
			if ( player->nb_keys > 0) {
				int cell=map_get_door_cell(map, x, y+1);
				map_set_cell_type(map, x, y+1, --cell);
				map_set_cell_type(map, x, y, CELL_EMPTY);
				sleep(1);
				player->nb_keys -= 1;
				//player->y++;
				move=0; }
		}
		else if (player_move_aux(player,map,x,y+1)==7) {
			player->nb_keys += 1;
			map_set_cell_type(map, x, y+1, CELL_EMPTY);
			player->y++;
			move = 1;
		}
		else if (player_move_aux(player, map, x, y)==8) {
			map_set_cell_type(map, x, y, map_get_cell(map, x, y));
			player->y++;
			move = 0;
		}
		else if (player_move_aux(player, map, x, y + 1)==3) {
			player->y++;
			move = 1;
			// if cell(x,y+1) is empty we move
		}
		else {}

		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y) !=0 && player_move_aux(player, map, x-1, y)==2 && player_move_aux(player, map, x-2, y)==3) {
			map_set_cell_type(map, x-2, y, CELL_BOX);
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
			//	 if the cell(x-1,y) is a box and cell(x-2,y) is empty we move
		}
		else if (player_move_aux(player,map,x-1,y)==5) {
			player->x--;
			move=0;
		}
		else if (player_move_aux(player,map,x-1,y)==41) {
			player_inc_scope(player);
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
		}
		else if (player_move_aux(player,map,x-1, y)==42) {
			player_dec_scope(player);
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
		}
		else if (player_move_aux(player,map,x-1, y)==43) {
			player_dec_nb_bomb(player);
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
		}
		else if (player_move_aux(player,map,x-1, y)==44) {
			player_inc_nb_bomb(player);
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
		}
		else if (player_move_aux(player,map,x-1, y)==45) {
			player_inc_nb_lives(player);
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
		}
		else if (player_move_aux(player,map,x-1,y)==6) {
			if ( player->nb_keys > 0) {
				int cell = map_get_door_cell(map, x-1, y);
				map_set_cell_type(map, x-1, y, --cell);
				map_set_cell_type(map, x, y, CELL_EMPTY);
				sleep(1);
				player->nb_keys -= 1;
				//player->x--;
				move=0;
			}
		}
		else if (player_move_aux(player,map,x-1,y)==7) {
			player->nb_keys += 1;
			map_set_cell_type(map, x-1, y, CELL_EMPTY);
			player->x--;
			move = 1;
		}
		else if (player_move_aux(player, map, x, y)==8) {
			map_set_cell_type(map, x, y, map_get_cell(map, x, y));
			player->x--;
			move = 0;
		}
		else if (player_move_aux(player, map, x - 1, y)==3) {
			player->x--;
			move = 1;
			//if cell(x-1,y) is empty we move
		}
		else {}

		break;


	case EAST:
		if (player_move_aux(player, map, x + 1, y ) !=0 && player_move_aux(player, map, x+1, y)==2 && player_move_aux(player, map, x+2, y)==3) {
			map_set_cell_type(map, x+2, y, CELL_BOX);
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
			//	 if the cell(x,y+1) is a box and cell(x,y+2) is empty we move
		}
		else if (player_move_aux(player,map,x+1,y)==5) {
			player->x++;
			move=0;
		}
		else if (player_move_aux(player,map,x+1, y)==41) {
			player_inc_scope(player);
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
		}
		else if (player_move_aux(player,map,x+1, y)==42) {
			player_dec_scope(player);
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
		}
		else if (player_move_aux(player,map,x+1, y)==43) {
			player_dec_nb_bomb(player);
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
		}
		else if (player_move_aux(player,map,x+1, y)==44) {
			player_inc_nb_bomb(player);
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
		}
		else if (player_move_aux(player,map,x+1, y)==45) {
			player_inc_nb_lives(player);
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
		}
		else if (player_move_aux(player,map,x+1,y)==6) {
			if ( player->nb_keys > 0) {
				int cell = map_get_door_cell(map, x+1, y);
				map_set_cell_type(map, x+1, y, --cell);
				map_set_cell_type(map, x, y, CELL_EMPTY);
				sleep(1);
				player->nb_keys -= 1;
				//player->x++;
				move=0;
			}
		}
		else if (player_move_aux(player,map,x+1,y)==7) {
			player->nb_keys += 1;
			map_set_cell_type(map, x+1, y, CELL_EMPTY);
			player->x++;
			move = 1;
		}
		else if (player_move_aux(player, map, x, y)==8) {
			map_set_cell_type(map, x, y, map_get_cell(map, x, y));
			player->x++;
			move = 0;
		}
		else if (player_move_aux(player, map, x + 1, y)==3) {
			player->x++;
			move = 1;
			//if cell(x+1,y) is empty we move
		}

		else {}

		break;
	}


	if (move) {
		map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_cell_type(map, player->x, player->y, CELL_PLAYER);
	}
	return move;
}

void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->current_direction),
			player->x * SIZE_BLOC, player->y * SIZE_BLOC);
}

