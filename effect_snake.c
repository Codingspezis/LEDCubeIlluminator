#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "communicator.h"
#include "utils.h"

struct Coordinate {
	int x;
	int y;
	int z;
};

struct Coordinate *snakeDots;
int snakeLength;

int equals(struct Coordinate a, struct Coordinate b) {
	return a.x==b.x && a.y==b.y && a.z==b.z;
}

int outOfRange(struct Coordinate p) {
	return p.x < 0 || p.y < 0 || p.z < 0 || p.x > 4 || p.y > 4 || p.z > 4;
}

int checkCollision(struct Coordinate p, int checkLast) {
	if(outOfRange(p))
		return -1;
	int i;
	for(i=0; i<snakeLength; i++) {
		if(i<(snakeLength-1) || (checkLast && i==(snakeLength-1))) {
			if(equals(snakeDots[i],p))
				return -1;
		}
	}
	return 0;
}

void snakeShift() {
	int i;
	for(i=snakeLength-2; i>=0; i--) {
		snakeDots[i+1] = snakeDots[i];
	}
}

struct Coordinate coordinateOfDirection(int direction) {
	struct Coordinate p = snakeDots[0];
	if(direction==0)
		p.x-=1;
	else if(direction==1)
		p.x+=1;
	else if(direction==2)
		p.y-=1;
	else if(direction==3)
		p.y+=1;
	else if(direction==4)
		p.z-=1;
	else if(direction==5)
		p.z+=1;
	return p;
}

void resetSnake() {
	int i;
	for(i=0; i<snakeLength; i++) {
		snakeDots[i].x = 0;
		snakeDots[i].y = 0;
		snakeDots[i].z = 0;
	}
}

void snakeMove() {
	int i;
	struct Coordinate p = coordinateOfDirection(rand()%6);
	for(i=-1; i<6; i++) {
		if(i>=0)
			p = coordinateOfDirection(i);
		if(!checkCollision(p, 0)) {
			snakeShift();
			snakeDots[0] = p;
			return;
		}
	}
	resetSnake();
}

void snakeEffectLoop(int length, int delayMs, int rounds) {
	int i, j;
	snakeLength = length;
	snakeDots = (struct Coordinate *)malloc(sizeof(struct Coordinate)*snakeLength);
	resetSnake();
	uint8_t *data = (uint8_t *)malloc(16);
	for(i=0; i<rounds; i++) {
		memset(data, 0, 16);
		for(j=0; j<snakeLength; j++) {
			if(!outOfRange(snakeDots[j]))
				setLed(data, snakeDots[j].x, snakeDots[j].y, snakeDots[j].z);
		}
		sendState(data);
		usleep(delayMs * 1000);
		snakeMove();
	}
	free(snakeDots);
	free(data);
}
