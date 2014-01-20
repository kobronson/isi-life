#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


 
 
#define for_x for (int x = 0; x < width; x++)
#define for_y for (int y = 0; y < height; y++)
#define for_xy for_x for_y

void show(void *u, int width, int height)
{
	int (*world)[width] = u;
	for_y {
		for_x world[y][x] ? mvaddch(  (( (LINES - height) / 2) +1)+y,((COLS - width) / 2)+x,'#') : mvaddch(y,x,' ') ;
		
		//printf(world[y][x] ? "\033[07m  \033[m" : "  ");
		//printf("\033[E");
	}
	refresh();
	//fflush(stdout);
}
 
void evolution(void *u, int width, int height)
{
	unsigned (*world)[width] = u;
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
	for_y for_x world[y][x] = new[y][x];
}
 
void run(int width, int height)
{
	unsigned world[height][width];
	char s[10];
	int x0,y0;
	
	for_xy  world[y][x] = 0;
	
	// while(s[0] != 's' ){
		// printf("Chose cells to populate:\n");
		// printf("X:");
		// scanf("%d",&x0);
		// printf("Y:");
		// scanf("%d",&y0);
		// printf("Start life or toggle next cell? (s/n) ");
		// scanf("%s",s);
		// world[y0][x0] = 1;
	
	
		// show(world, width, height);
	
	// }
	
	for_xy world[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
	
	
	while (1) {
		show(world, width, height);
		evolution(world, width, height);
		usleep(200000);
	}
}
 






WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);



WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
	
}

int main(int argc, char *argv[])
{	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();			/* Start curses mode 		*/
	cbreak();			/* Line buffering disabled, Pass on
					 * everty thing to me 		*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

	height = LINES -1;
	width = COLS;
	starty = ((LINES - height) / 2) +1;	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	printw("Press q to exit");
    
	refresh();
	my_win = create_newwin(height, width, starty, startx);
	
	// int width = 30, height = 30;
	// if (c > 1) width = atoi(v[1]);
	// if (c > 2) height = atoi(v[2]);

	run(width, height);
	
	
	
		
	endwin();			/* End curses mode		  */
	return 0;
}

bool kbd(int ch)
{
    int x,y; /* Holds the coordinates */
  //  getyx(life, y, x); /* Get the coordinates from curses life window */
    switch(ch)
    { /* hjkl + q + space + enter */
        case 'q':
            return false;
            break;
        case 'l': /* Go right */
          //  x=(x+1)%CMAX;
            break;
        case 'h': /* Go left */
         //   x=(x-1)%CMAX;
            break;
        case 'j': /* Go down */
          //  y=(y+1)%LMAX;
            break;
        case 'k': /* Go up */
          //  y=(y-1)%LMAX;
            break;
        case ' ': /* Activate a cell */
           
            break;
        case 10: /* Enter. Start the tick */
          //  tick();
            break;
        case KEY_UP: /* Increase tick size */

          
            break;
        case KEY_DOWN: /* Reduce tick size */
          
           
            break;
    }
    //wmove(life, y, x); 
    //wrefresh(life);

    return true;
}

