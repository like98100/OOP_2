#pragma once

class Player
{
	int position;
	char *emotion;		//pointer 사용 권장
	//string emotion;
public:
	Player(int pos, char* emo) : position(pos), emotion(emo) {}
	void act(int key)	//공격은 Bullet으로 분리 예정
	{
		if (key == 75) this->position--;		// Left
		else if (key == 77) this->position++; // Right
	}
	void check_range(int* pos, int screen_leng)
	{
		if (*pos < 0) *pos = 0;
		else if (*pos > screen_leng - 1) *pos = screen_leng - 1;
	}
	int get_position()
	{
		return position;
	}
	int* get_position_point()
	{
		return &position;
	}
	char* get_emotion()
	{
		return emotion;
	}
};