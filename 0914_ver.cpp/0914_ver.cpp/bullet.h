#pragma once
class Bullet
{
	int position[125];		//25¹ß ¿¬»ç * 5
	int cnt;
	//int cnt_first;
public:
	Bullet(int cnt) : cnt(cnt)
	{
		for (int i = 0; i < 125; i++) position[i] = -1;
	}
	void shot(int position)
	{
		//if (cnt_first != 125) cnt_first++;
		position[&cnt] = position;
		cnt++;
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
			cnt--;
		}
	}

	int get_cnt()
	{
		return cnt;
	}

};
