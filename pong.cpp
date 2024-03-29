#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };
class cBall
{
private:
	int x, y, originalX, originalY;
	eDir direction;
public:
	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX; y = posY;
		direction = STOP;
	}
	void reset()
	{
		x = originalX; y = originalY;
		direction = STOP;
	}
	void changeDirection(eDir d)
	{
		direction = d;
	}
	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
		Beep(350, 200);
	}
	 inline int getX() { return x; }
	 inline int getY() { return y; }
	 inline eDir getdirection() { return direction; }
	 void Move()
	 {
		 switch (direction)
		 {
		 case STOP:
			 break;
		 case LEFT:
			 if (x > 4)
				 x = x - 2;
			 else
				 x--;
			 break;
		 case RIGHT:
			 if (x < 65)
				 x = x + 2;
			 else
				 x++;
			 break;
		 case UPLEFT:
			 x--; y--;
			 break;
		 case DOWNLEFT:
			 x--; y++;
			 break;
		 case UPRIGHT:
			 x++; y--;
			 break;
		 case DOWNRIGHT:
			 x++; y++;
			 break;
		 default:
			 break;
		
		 }
	 }
	 friend ostream& operator<<(ostream& o, cBall c)
	 {
		 o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		 return o;
	 }
};
class cPaddle
{
private:
	int x, y, originalX, originalY;
public:
	cPaddle()
	{
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() 
	{ 
		y = y - 2;
	}
	inline void moveDown() 
	{
		y = y + 2;
	}
	friend ostream& operator<<(ostream& o, cPaddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}

};
class cGameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall *ball;
	cPaddle *player1, *player2;
public:
	cGameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w', up2 = '9';
		down1 = 's', down2 = '6';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall((w-1) / 2, h / 2);
		player1 = new cPaddle(1, h / 2 - 2);
		player2 = new cPaddle(w - 2, h / 2 - 2);
	}
	~cGameManager()
	{
		delete ball, player1, player2;
	}
	void ScoreUp(cPaddle *player)
	{
		if (player == player1) 
		{
			score1++;
			if (score1 > 9)
				score1 = score2 = 0;
		}
		else if (player == player2) 
		{
			score2++;
			if (score2 > 9)
				score2 = score1 = 0;
		}
		ball->reset();
		player1->reset();
		player2->reset();
	}
	void Draw()
	{
		int x = 0,y = 0;
		COORD coord;
		coord.X = x; // your X cord
		coord.Y = y; //your Y cord
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		for (int i = 0; i < width + 2; i++)
		{
			if (i == ((width + 1) / 2))
				cout << ":";
			
			else if (i == ((width + 1) / 2) - 1)
				cout << score1;
			else if (i == ((width + 1) / 2) + 1)
				cout << score2;
			else
			cout << "\xB2";
		}
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O"; //ball
				else if (player1x == j && player1y == i)
					cout << "\xDB"; // player1
				else if (player2x == j && player2y == i)
					cout << "\xDB"; // player2

				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB"; // player1
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB"; // player1
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB"; // player1

				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB"; // player2
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB"; // player2
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB"; // player2

				else if (j == ((width - 1) / 2))
					cout << "|";

				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
		{
			cout << "\xB2";
		}

		cout << endl << "Controls:\n" << "Start ball = space bar\n" << "Player 1 up/down = 'w' / 's'\n"
			<< "Player 2 up/down = '9' / '6'\n" << "Exit = 'q'";
	}
	void Input()
	{
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		if (_kbhit())
		{
			char current = _getch();
			if (current == up1)
				if (player1y > 1)
					player1->moveUp();
			if (current == up2)
				if (player2y > 1)
					player2->moveUp();
			if (current == down1)
				if (player1y + 3 < height - 2)
					player1->moveDown();
			if (current == down2)
				if (player2y + 3 < height - 2)
					player2->moveDown();

			if (ball->getdirection() == STOP && current == ' ')
				ball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
				{
					ball->changeDirection((eDir)((rand() % 3) + 4));
				}

		//right paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
				{
					ball->changeDirection((eDir)((rand() % 3) + 1));
				}

		//bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getdirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top wall
		if (bally == 0)
			ball->changeDirection(ball->getdirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width - 1)
			ScoreUp(player1);
		//left wall
		if (ballx == 0)
			ScoreUp(player2);
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};	

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void DisableMaxButton()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void disableMouse()
{
	DWORD prev_mode;
	HANDLE consoleHandle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(consoleHandle, &prev_mode);
	SetConsoleMode(consoleHandle, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}
int main()
{
	ShowConsoleCursor(false);
	DisableMaxButton();
	disableMouse();
	cGameManager c(70, 20); //c(w,h)
	c.Run();
    return 0;
}

