#pragma once
class Bullet
{
	int position[125];		//25¹ß ¿¬»ç * 5
	int cnt;
	char shape;
	//int cnt_first;
public:
	Bullet(int cnt, char shape) : cnt(cnt), shape(shape)
	{
		for (int i = 0; i < 125; i++) position[i] = -1;
	}
	void shot(int position_player)
	{
		//if (cnt_first != 125) cnt_first++;
		this->position[cnt] = position_player;
		this->cnt++;
	}

	void drive(char * scr, int leng, int pos_enemy, bool check)
	{
		for (int i = 0; i < this->cnt; i++)
		{
			if (this->position[i] >= 0 && this->position[i] <= leng && this->position[i] != -1)
			{
				if (this->position[i] < pos_enemy) { this->position[i]++; }
				else if (this->position[i] > pos_enemy) { this->position[i]--; }

				if (this->position[i] == pos_enemy)
				{
					this->position[i] = -1;
					check = true;
				}
			}
		}
	}

	void move(int pos_enemy, int index)
	{
		if (position[index] > pos_enemy)
		{
			position[index]--;
		}
		else if (position[index] < pos_enemy)
		{
			position[index]++;
		}
	}
	void check_attack(int pos_enemy, int index)
	{
		if (position[index] == pos_enemy)
		{
			position[index] = -1;
			//cnt--;
		}
	}

	int get_cnt()
	{
		return cnt;
	}
	
	int get_position_value(int index)
	{
		return position[index];
	}

	char get_shape()
	{
		return shape;
	}
	char * get_shape_pointer()
	{
		return &shape;
	}
};
