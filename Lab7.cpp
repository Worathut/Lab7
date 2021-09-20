#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
void gotoxy(int x, int y) {
	//setPosition
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcolor(int fg, int bg) {
	//setColor
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void setcursor(bool visible) {
	//setCursor
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void erase_Bg(int x, int y) {
	//erase background
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

void draw_ship(int x, int y) {
	//draw ship
	setcolor(2, 4);
	gotoxy(x, y);
	printf(" <-0-> ");
}

void erase_ship(int x, int y) {
	//erase ship
	gotoxy(x, y);
	printf("       ");
}

void draw_bullet(int x, int y) {
	//draw bullet
	setcolor(2, 0);
	gotoxy(x, y);
	printf("!");
}

void erase_bullet(int x, int y) {
	//erase bullet
	gotoxy(x, y);
	setcolor(7, 0);
	printf(" ");
}

void draw_star(int x, int y) {
	//draw star
	gotoxy(x, y);
	setcolor(4, 0);
	printf("*");
}

void Score(int point) {
	//print Score
	gotoxy(0, 1);
	setcolor(2, 0);
	printf("Score : %d", point);
}

char cursor(int x, int y) {//check char
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];

}

struct Bullet {
	int Active = 0;
	int x = 0, y = 0;
};

int main() {
	char ch = ' ';
	int action = 0;
	int x = 38, y = 29;
	Bullet bullets[5];
	int point = 0;
	Score(point);
	srand(time(NULL));
	for (int i = 0; i < 20; i++) {
		draw_star(10 + rand() % 61, 2 + rand() % 5);
	}
	draw_ship(x, y);
	setcursor(0);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' || ch == 'A') {
				action = 1;
			}
			if (ch == 'd' || ch == 'D') {
				action = 2;
			}
			if (ch == 's' || ch == 'S') {
				action = 0;
			}
			if (ch == ' ') {
				for (int i = 0; i < 5; i++) {
					if (bullets[i].Active == 0)
					{
						bullets[i].Active = 1;
						bullets[i].x = x + 3;
						bullets[i].y = y;
						break;
					}
				}
			}
			fflush(stdin);
		}

		for (int i = 0; i < 5; i++) {
			if (bullets[i].Active == 1) {
				erase_bullet(bullets[i].x, bullets[i].y);
				if (cursor(bullets[i].x, bullets[i].y - 1) == '*') {
					Beep(650, 100);
					bullets[i].Active = 0;
					erase_bullet(bullets[i].x, bullets[i].y - 1);
					draw_star(10 + rand() % 61, 2 + rand() % 5);
					point += 100;
					Score(point);
				}
				else if (bullets[i].y > 2) {
					draw_bullet(bullets[i].x, --bullets[i].y);
				}

				else {
					bullets[i].Active = 0;
				}

			}
		}
		if (action == 1 && x > 0)
		{
			erase_ship(x, y);
			erase_Bg(x, y);
			draw_ship(--x, y);

		}
		else if (action == 2 && x < 75)
		{
			erase_ship(x, y);
			erase_Bg(x, y);
			draw_ship(++x, y);
		}
		else
		{
			erase_ship(x, y);
			erase_Bg(x, y);
			draw_ship(x, y);
		}

		Sleep(100);
	} while (ch != 'x');
	return 0;
}