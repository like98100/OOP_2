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
	bool monster_attacked = false;
	//int cnt_savemagnum = 0;
	//string screen;

	Player user(30, "(^,.^)");
	Enemy monster(50, "(¤Ñ,.¤Ñ)", "(¤·,.¤·)",30);
	Bullet magnum(0, '*');

	while (1)
	{
		memset(scr, 0, screen_leng);
		memset(scr, ' ', screen_leng);

		if (kbhit())
		{
			char key = getch();

			if (key == 27) return 0;
			//if (key == -32) key = getch();
			switch (key)
			{
			case -32:		//Left & Right Move
				key = getch();
				user.act(key);
				break;

			case ' ':		//Shot
				magnum.shot(user.get_position());
				break;

			default:
				break;
			}
		}

		user.check_range(user.get_position_point(), screen_leng);
		monster.check_range(monster.get_position_point(), screen_leng);


		monster.get_frame_attacked();
		
		magnum.drive(scr, screen_leng, monster.get_position(), monster_attacked);
		for (int i = 0; i < magnum.get_cnt(); i++) //scr[magnum.get_position_value(magnum.get_cnt())] = magnum.get_shape();
			::memcpy(&scr[magnum.get_position_value(i)], magnum.get_shape_pointer(), 1);
		
		if (monster_attacked) { monster.set_emotion(monster_attacked); monster.set_frame_start(); }

		::memcpy(&scr[user.get_position()], user.get_emotion(), strlen(user.get_emotion()));
		::memcpy(&scr[monster.get_position()], monster.get_emotion(), strlen(monster.get_emotion()));


		scr[screen_leng] = '\r'; scr[screen_leng+1] = 0;
		::cout << scr;
		
		monster.set_frame();

		Sleep(100);
	}

	return 0;
}