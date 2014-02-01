#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>


 
 
#define for_x for (int x = 0; x < width; x++)
#define for_y for (int y = 0; y < height; y++)
#define for_xy for_x for_y


WINDOW *my_win=NULL;
unsigned win_x =0;
unsigned win_y =0;  
unsigned generation =0;

bool kbd(int ch,unsigned**,int,int);
WINDOW *create_newwin(int height, int width, int starty, int startx);


void destroy_win(WINDOW *local_win);

void show(unsigned **world, int width, int height)
{
	for_xy world[y][x] ? mvwaddch(my_win,y+1,x+1,ACS_CKBOARD) : mvwaddch(my_win,y+1,x+1,' ') ;
		
	
	refresh();
	
}
 
void evolution(unsigned **world, int width, int height)
{
	unsigned new[height][width];
 
	for_y for_x {
		int n = 0;
		for (int y1 = y - 1; y1 <= y + 1; y1++)
			for (int x1 = x - 1; x1 <= x + 1; x1++)
				if (world[(y1 + height) % height][(x1 + width) % width])
					n++;
 
		if (world[y][x]) n--;
		new[y][x] = (n == 3 || (n == 2 && world[y][x]));
	}
	for_xy world[y][x] = new[y][x];
}
 

 
void run_step(unsigned **world,int width, int height)
{
	
	show(world, width, height);
	evolution(world, width, height);
}









WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);	
	wrefresh(local_win);		

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	

	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');

	wrefresh(local_win);
	delwin(local_win);
	
}

int main(int argc, char *argv[])
{	
	int startx, starty, width, height;
	int win_width, win_height;
	int ch,l;
	unsigned **world; 
	struct winsize w;
	initscr();			
	cbreak();
	
	
	
	
	if(argc==3)
	{
	
		win_height=atoi(argv[1]) ;
		win_width=atoi(argv[2]);
	}

	
		
	//starty = ((LINES - win_height) / 2) +1;	
	//startx = ((COLS - win_width) / 2) ;	
	
	//printw("[q] to exit, [r] random mode, [n] next step, [space] togle cell, [arrows] move       ");
    
	mvprintw(0,0,"[q] to exit, [r] random mode, [n] next step, [space] togle cell, [arrows] move.    Generation:%d       ",generation);
	
	
	
	refresh();
	my_win = create_newwin(win_height, win_width, 1, 0);
	keypad(stdscr, TRUE);	
	
	width = win_width-2;
	height = win_height-2;
	
	
	world = (unsigned**)malloc(height * sizeof(unsigned*));
	for(l = 0; l < width; l++)
		world[l] = (unsigned*)malloc(width * sizeof(unsigned));
		
		

	for_xy world[y][x] = 0;
	//wmove(my_win,0, 0); 
	do
    { /* Keyboard loop */
		
		
        ch = getch();
    }
    while(kbd(ch,world,width,height));

	
	
	
		
	endwin();			/* End curses mode		  */
	return 0;
}

bool kbd(int ch, unsigned **world,int width, int height )
{
    int c_x,c_y; /* Holds the coordinates */
    getyx(my_win, c_y, c_x); /* Get the coordinates from curses life window */
  
    switch(ch)
    { 
        case 'q':
            return false;
            break;
        case 'n': 
		
		run_step(world,width,height);
		generation++;
        
            break;
        case 'r': 
			srand(time(NULL));
			for_xy world[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
			show(world,width,height);
			break;
			
        case ' ':

			
            world[c_y-1][c_x-1]=1;
			show(world,width,height);
	


            break;
			
			
        case KEY_UP: 
			c_y=(c_y-1)%(height+2);
			 if(c_y==0)
			{
				c_y=height;
			}
			 

          
            break;
        case KEY_DOWN: 
			
            c_y=(c_y+1)%(height+1);
			
			if(c_y==0)
			{
				c_y++;
			}

            break;
		 case KEY_LEFT: 
			
            c_x=(c_x-1)%(width+2);
			if(c_x==0)
			{
				c_x=width;
			}

            break;
		case KEY_RIGHT: 
          
            c_x=(c_x+1)%(width+1);
			if(c_x==0)
			{
				c_x++;
			}

            break;
    }			
	mvprintw(0,0,"[q] to exit, [r] random mode, [n] next step, [space] togle cell, [arrows] move.    Generation:%d       ",generation);
	refresh();	
	
	wmove(my_win,c_y, c_x); 
	wrefresh(my_win);
   

    return true;
}

