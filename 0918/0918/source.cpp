#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

class Player
{
	int position = 20;
	char emotion[100] = "(^,.^)";
public:
	void move(int num)
	{
		this->position += num;
	}
	int get_position() const
	{
		return position;
	}
	void check_range(int size)
	{
		if (position < 0) position = 0;
		else if (position > size-1) position = size - 1;
	}
	void draw(char* screen, int screen_size)
	{
		check_range(screen_size);
		strncpy(screen + position, emotion, strlen(emotion));
	}
};

class Enemy
{
	int position = 50;
	char emotion[100] = "(天,.天)";
	char emotion_attacked[100] = "(仄,.仄)";
	int sec = -1;
	bool attacked = false;
public:
	void move(int num)
	{
		this->position += num;
	}
	void check_range(int size)
	{
		if (position < 0) position = 0;
		else if (position > size - 1) position = size - 1;
	}
	void draw(char* screen, int screen_size)
	{
		check_range(screen_size);
		strncpy(screen + position, emotion, strlen(emotion));
	}
	int get_position() const
	{
		return position;
	}
	void timer()
	{
		if(sec >= 0 && sec < 10) sec++;
		else attacked = false;
	}
	void act_damage()
	{
		attacked = true;
		sec = 0;
		//update_ver
		//sec = 10;
		//strcpy(emotion, emotion_attacked);
	}

	bool get_attacked()
	{
		return attacked;
	}
	void draw_attacked(char* screen, int size)
	{
		check_range(size);
		strncpy(screen + position, emotion_attacked, strlen(emotion_attacked));
	}

	//void update()
	//{
	//	if (sec == 0) return;
	//	sec--;
	//	if (sec == 0)
	//	{
	//		strcpy(emotion, "(天,.天)");
	//	}

	//}
};

class Bullet
{
	int position = -1;
	char shape = '-';
public:
	Bullet(int player_pos) : position(player_pos) {}
	void set_position(int pos)
	{
		this->position = pos;
	}
	void draw(char* screen)
	{
		screen[position] = shape;
	}
	int get_position() const
	{
		return position;
	}
	void move(int num)
	{
		this->position += num;
	}

	//void update(const Player& player, const Enemy& enemy)
	//{
	//	if (player.get_position() < enemy.get_position()) move(1);
	//	else if (player.get_position() > enemy.get_position()) move(-1);
	//}

	void update(const Player* player, const Enemy* enemy)
	{
		if (!player || !enemy) return;

		if (player->get_position() < enemy->get_position()) move(1);
		else if (player->get_position() > enemy->get_position()) move(-1);
	}
};


int main()
{
	const int screen_size = 119;
	char scr[screen_size + 1 + 1];

	Player player;
	Enemy enemy;
	Bullet* pBullet = nullptr;

	while (1)
	{
		memset(scr, 0, screen_size);
		memset(scr, ' ', screen_size);

		if (_kbhit())
		{
			char key = getch();
			if (key == 27) break;
			if (key == -32) key = getch();

			switch (key)
			{
			case 75:
				player.move(-1);
				break;
			case 77:
				player.move(1);
				break;
			case 72:
				enemy.move(-1);
				break;
			case 80:
				enemy.move(1);
				break;
			case ' ':
				if (pBullet == nullptr)
				{
					pBullet = new Bullet(player.get_position());
					//pBullet->set_position(player.get_position());
				}
					break;
			default:
				break;
			}
		}

		player.check_range(screen_size);
		enemy.check_range(screen_size);

		player.draw(scr, screen_size);
		enemy.draw(scr, screen_size);
		//If I need to draw bullet in screen..
		//Draw bullet
		if (pBullet != nullptr)
		{
			pBullet->draw(scr);
			//If bullet crash with enemy
			//Destroy bullet
			if (pBullet->get_position() == enemy.get_position())
			{

				enemy.act_damage();
				delete pBullet;		//delete object
				pBullet = nullptr;		//delete point address
			}

			//else
			//Move bullet
			else
			{
				//pBullet->update(player, enemy);		//& ver

				pBullet->update(&player, &enemy);	//* ver

				//if (pBullet->get_position() < enemy.get_position()) pBullet->move(1);	//move
				//else if (pBullet->get_position() > enemy.get_position()) pBullet->move(-1);
			}
		}

		if (enemy.get_attacked())
		{
			enemy.timer();	enemy.draw_attacked(scr, screen_size);
		}
		//enemy.update();

		scr[screen_size] = '\r'; scr[screen_size + 1] = 0;
		printf("%s", scr);
		Sleep(100);
	}

	return 0;
}