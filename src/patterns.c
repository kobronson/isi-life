void glider(unsigned **world,int y, int x)
{
	world[y][x] = 1;
	world[y+1][x+1]=1;
	world[y+1][x+2]=1;
	world[y-1][x+2]=1;
	world[y][x+2]=1;

}

void lwss(unsigned **world,int y, int x)
{
	world[y][x] = 1;
	world[y-1][x+1] = 1;
	world[y-1][x+4] = 1;
	world[y+1][x] = 1;
	world[y+2][x] = 1;
	
	world[y+2][x+1] = 1;
	world[y+2][x+2] = 1;
	world[y+2][x+3] = 1;
	
	world[y+1][x+4] = 1;
}

void air_carrier(unsigned **world,int y, int x)
{
	world[y][x] = 1;
	world[y-1][x] = 1;
	world[y][x+1] = 1;
	

	world[y-1][x+3] = 1;
	world[y-2][x+3] = 1;
	world[y-2][x+2] = 1;
}

void block(unsigned **world,int y, int x)
{
	world[y][x] = 1;
	world[y][x+1] = 1;
	world[y+1][x] = 1;
	world[y+1][x+1] = 1;
}

void toad(unsigned **world,int y, int x)
{
	world[y][x] = 1;
	world[y][x+1] = 1;
	world[y][x+2] = 1;
	
	world[y-1][x+1] = 1;
	world[y-1][x+2] = 1;
	world[y-1][x+3] = 1;

}

void blinker(unsigned **world,int y, int x)
{
	world[y][x] = 1;
	world[y][x+1] = 1;
	world[y][x+2] = 1;


}
