#include <stdio.h>
#include <stdlib.h>

#define BOARD_FILE "board.txt"

#define WALL_CHAR '#'
#define PLAYER_CHAR 'O'

#define HEIGHT 20
#define WIDTH 40

#define STARTX 1
#define STARTY 1

#define EXITCHAR 'x'
#define UPCHAR 'w'
#define LEFTCHAR 'a'
#define DOWNCHAR 's'
#define RIGHTCHAR 'd'

char help_str[] = "\r\nControls: w=UP / a=LEFT / s=DOWN / d=RIGHT / x=EXIT \r\n\n";

char board[HEIGHT][WIDTH];

int xpos;
int ypos;

void raw_mode_on();
void raw_mode_off();
void init_board();
void render();

int main() {

	int esi, edi;
	char al;

	raw_mode_on();

	init_board();

	xpos = STARTX;
	ypos = STARTY;

	while (1) {

		render();

		esi = xpos;
		edi = ypos;

		al = getchar();

		switch (al) {
			case EXITCHAR:	goto loop_end;
			case UPCHAR:	ypos--;	break;
			case LEFTCHAR:	xpos--;	break;
			case DOWNCHAR:	ypos++;	break;
			case RIGHTCHAR:	xpos++;	break;
		}

		if (board[ypos][xpos] == WALL_CHAR) {
			xpos = esi;
			ypos = edi;
		}

	}

	loop_end:

	raw_mode_off();	

}

void raw_mode_on() {

	system("stty raw -echo");

}

void raw_mode_off() {

	system("stty -raw echo");

}

void init_board() {

	FILE *fp;
	int linenum;

	fp = fopen(BOARD_FILE, "r");

	for (linenum=0; linenum<HEIGHT; linenum++) {

		fread(&board[linenum], 1, WIDTH, fp);
		fgetc(fp);

	}

	fclose(fp);

}

void render() {

	int x;
	int y;

	system("clear");

	printf(help_str);

	for (y=0; y<HEIGHT; y++) {

		for (x=0; x<WIDTH; x++) {

			if (xpos == x && ypos == y) {
				putchar(PLAYER_CHAR);
			} else {
				putchar(board[y][x]);
			}

		}

		putchar('\r');
		putchar('\n');

	}

}
