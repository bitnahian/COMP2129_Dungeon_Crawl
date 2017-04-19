#ifndef DUNGEON_H

#define DUNGEON_H

#define MAX_LENGTH 255
#define MAX_LINE 8192

typedef struct room_t room_t;

struct room_t {
	char name[30];
	room_t* north;
	room_t* south;
	room_t* east;
	room_t* west;

};


#endif
