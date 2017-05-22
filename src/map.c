#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <player.h>
#include <map.h>
#include <constant.h>
#include <misc.h>
#include <sprite.h>
#include <window.h>

struct map {
	int width;
	int height;
	unsigned char* grid;
};

// #define CELL(i,j) ( (i) + (j) * map->width)

struct map* map_new(int width, int height)
{
	assert(width > 0 && height > 0);

	struct map* map = malloc(sizeof *map);
	if (map == NULL )
		error("map_new : malloc map failed");

	map->width = width;
	map->height = height;

	map->grid = malloc(height * width);
	if (map->grid == NULL) {
		error("map_new : malloc grid failed");
	}

	// Grid cleaning
	int i, j;
	for (i = 0; i < width; i++)
	  for (j = 0; j < height; j++)
	    map->grid[CELL(i,j)] = CELL_EMPTY;

	return map;
}

int map_is_inside(struct map* map, int x, int y) {

	assert(map);
	if (x>=0 && (y<map_get_height(map)) && (x<map_get_width(map)) && (y>=0)) {
		return 1;
	}
	return 0;

}



void map_free(struct map *map)
{
	if (map == NULL )
		return;
	free(map->grid);
	free(map);
}

int map_get_width(struct map* map)
{
	assert(map != NULL);
	return map->width;
}

int map_get_height(struct map* map)
{
	assert(map);
	return map->height;
}

enum cell_type map_get_cell_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 0xf0;
}

int map_get_cell_subtype(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 0x0f;
}

int map_get_door_level(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	int cell = map->grid[CELL(x,y)];
	printf("[DEBUG] door(%d,%d) : level = %d\n", x, y, cell);
	return (cell & 0x0e) >> 1;
}

int map_get_door_cell(struct map* map, int x, int y) {
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)];
}


int map_get_cell(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)];
}




void map_set_cell_type(struct map* map, int x, int y, enum cell_type type)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

void display_bonus(struct map* map, int x, int y, unsigned char type)
{
	// bonus is encoded with the 4 most significant bits
	switch (type & 0x0f) {
	case BONUS_BOMB_RANGE_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_INC), x, y);
		break;

	case BONUS_BOMB_RANGE_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_NB_INC), x, y);
		break;

	case BONUS_LIFE:
		window_display_image(sprite_get_banner_life(), x, y);
				break;
	}
}

void display_scenery(struct map* map, int x, int  y, unsigned char type)
{
	switch (type & 0x0f) { // sub-types are encoded with the 4 less significant bits
	case SCENERY_STONE:
		window_display_image(sprite_get_stone(), x, y);
		break;

	case SCENERY_TREE:
		window_display_image(sprite_get_tree(), x, y);
		break;
	case SCENERY_PRINCESS:
		window_display_image(sprite_get_princess(), x, y);
	}
}

void display_door(struct map* map, int x, int y, unsigned char type)
{
	switch (type & 1) { // Opened or closed door is encoded with the less significant bit
	case DOOR_OPENED:
		window_display_image(sprite_get_door_opened(), x, y);
		break;

	case DOOR_CLOSED:
		window_display_image(sprite_get_door_closed(), x, y);
		break;
	}
}

void display_bomb(struct map* map, int x, int y, unsigned char type) {
	switch (type & 7) {
	case BOMB1:
		window_display_image(sprite_get_bomb(1), x, y);
		break;
	case BOMB2:
		window_display_image(sprite_get_bomb(2), x, y);
		break;
	case BOMB3:
		window_display_image(sprite_get_bomb(3), x, y);
		break;
	case BOMB4:
		window_display_image(sprite_get_bomb(4), x, y);
		break;
	case BOMB5:
		window_display_image(sprite_get_bomb(0), x, y);
		break;
	}
}

void map_display(struct map* map)
{
	assert(map != NULL);
	assert(map->height > 0 && map->width > 0);

	int x, y;
	for (int i = 0; i < map->width; i++) {
	  for (int j = 0; j < map->height; j++) {
	    x = i * SIZE_BLOC;
	    y = j * SIZE_BLOC;

	    unsigned char type = map->grid[CELL(i,j)];
	    
	    switch (type & 0xf0) {
		case CELL_SCENERY:
		  display_scenery(map, x, y, type);
		  break;
	    case CELL_BOX:
	      window_display_image(sprite_get_box(), x, y);
	      break;
	    case CELL_BONUS:
	      display_bonus(map, x, y, type);
	      break;
	    case CELL_KEY:
	      window_display_image(sprite_get_key(), x, y);
	      break;
	    case CELL_BOMB:
	    	display_bomb(map, x, y, type);
	    	break;
	    case CELL_DOOR:
	      display_door(map, x, y, type);
	      break;
	    }
	  }
	}
}
int widthload(int map_number){
  FILE* mapfile=NULL;
  char path[50];
  sprintf(path, "data/map_%d.txt", map_number);
  mapfile=fopen(path ,"r");
  if (mapfile!=NULL) {
    char tab[100];
    fgets(tab,sizeof tab ,mapfile);
    sprintf(tab,"%c",tab[0]);
    fclose(mapfile);
    return atoi(tab);
  }
  else {
     printf("Error while opening the map file \n");
     return(EXIT_FAILURE);
  }
}



int heightload(int map_number){
  FILE* mapfile=NULL;
  char path[50];
  sprintf(path, "data/map_%d.txt", map_number);
  mapfile=fopen(path ,"r");
  if (mapfile!=NULL) {
    char tab[100];
    fgets(tab,sizeof tab ,mapfile);
    sprintf(tab,"%c",tab[2]);
    fclose(mapfile);
    return atoi(tab);
  }
  else {
     printf("Error while opening the map file \n");
     return(EXIT_FAILURE);
  }
}
struct map* mapload(int map_number) {
	FILE* mapfile=NULL;
	char path[50];
	sprintf(path, "data/map_%d.txt", map_number);
	mapfile=fopen(path,"r");
	struct map* map = map_new( widthload( map_number ), heightload( map_number ) );
	if (mapfile!=NULL) {
		char array[150];/* or other suitable maximum line size */
		char temp[3], temp0[3];
		fgets(array, sizeof(array), mapfile); /* read the first line */
		int i=0;
		while ( fgets (array, sizeof(array), mapfile ) != NULL ) {
			int j=0, k=0;
			while ( array[j]!='\0' ) {
				if (array[j]!=' ') {
					if (array[j+1]!=' ') {
						if (array[j+2]!=' ') {
							sprintf(temp,"%c",array[j]);
							sprintf(temp0,"%c",array[j+1]);
							strcat(temp, temp0);
							sprintf(temp0,"%c",array[j+2]);
							map->grid[CELL(k,i)] = atoi(strcat(temp, temp0));
							k++;
							j+=2;
						}
						else {
							sprintf(temp,"%c",array[j]);
							sprintf(temp0,"%c",array[j+1]);
							map->grid[CELL(k,i)] = atoi(strcat(temp, temp0));
							k++;
							j++;
						}
					}
					else {

						sprintf(temp,"%c",array[j]);
						map->grid[CELL(k,i)] = atoi(temp);
						k++;
						}
				}
				j++;
			}
			i++;
		}
		fclose (mapfile);
	}
	else
    	{
		printf("mapfile is NULL \n");
    	}
	return map;
	}

struct map* map_get_default(void)
{
	/*struct map* map = map_new(MAP_WIDTH, MAP_HEIGHT);

	unsigned char themap[MAP_WIDTH * MAP_HEIGHT] = {
	  CELL_EMPTY, CELL_EMPTY, CELL_PLAYER, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
	  CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_BOX, CELL_EMPTY, CELL_STONE, CELL_BOX, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_BOX, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_BOX, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_BOX, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY , CELL_EMPTY, CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_BOX, CELL_BONUS, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_TREE, CELL_TREE, CELL_TREE, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_BOX, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE,  CELL_BOX_LIFE, CELL_EMPTY,
	  CELL_EMPTY,  CELL_EMPTY, CELL_DOOR, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
		};

	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		map->grid[i] = themap[i];
*/
	return mapload(0);
}

