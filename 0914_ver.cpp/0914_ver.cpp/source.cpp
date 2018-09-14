#include <iostream>
#include <Windows.h>
#include <conio.h>
//#include <string>

#include "player.h"
#include "enemy.h"
#include "bullet.h"
using namespace std;

int main()
{
	const int screen_leng = 119;
	char scr[screen_leng + 2];
	//string screen;

	Player user(30, "(^,.^)");
	Enemy monster(50, "(คั,.คั)", 30);
	Bullet magnum(0);

	while (1)
	{
		memset(scr, 0, screen_leng);
		memset(scr, ' ', screen_leng);

		if (kbhit())
		{
			char key = getch();

			if (key == -32) key = getch();

			switch (key)
			{
			case 75: case 77:		//Left & Right Move
				user.act(key);
				break;

			case ' ':		//Shot
				magnum.shot(user.get_position());
				break;

			default:
				break;
			}
		}

		
		Sleep(100);
	}

	return 0;
}