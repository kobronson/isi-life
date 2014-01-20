#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 

 
 
#define FOR_X for (int x = 0; x < width; x++)
#define FOR_Y for (int y = 0; y < height; y++)
#define FOR_XY FOR_X FOR_Y

void show(void *u, int width, int height)
{
	int (*world)[width] = u;
	printf("\033[H");
	FOR_Y {
		FOR_X printf(world[y][x] ? "\033[07m  \033[m" : "  ");
		printf("\033[E");
	}
	fflush(stdout);
}
 
void evolution(void *u, int width, int height)
{
	unsigned (*world)[width] = u;
	unsigned new[height][width];
 
	FOR_Y FOR_X {
		int n = 0;
		for (int y1 = y - 1; y1 <= y + 1; y1++)
			for (int x1 = x - 1; x1 <= x + 1; x1++)
				if (world[(y1 + height) % height][(x1 + width) % width])
					n++;
 
		if (world[y][x]) n--;
		new[y][x] = (n == 3 || (n == 2 && world[y][x]));
	}
	FOR_Y FOR_X world[y][x] = new[y][x];
}
 
void run(int width, int height)
{
	unsigned world[height][width];
	FOR_XY world[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
	while (1) {
		show(world, width, height);
		evolution(world, width, height);
		usleep(200000);
	}
}
 
int main(int c, char **v)
{
	int width = 30, height = 30;
	if (c > 1) width = atoi(v[1]);
	if (c > 2) height = atoi(v[2]);

	run(width, height);
}
