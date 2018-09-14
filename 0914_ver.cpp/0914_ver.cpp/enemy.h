#pragma once
class Enemy
{
	int position;
	char *emotion;		//pointer 사용 권장
	//string emotion;
	int frame_attacked;
public:
	Enemy(int pos, char* emo, int fram) : position(pos), emotion(emo), frame_attacked(fram) {}
	void check_range(int* pos, int screen_leng)
	{
		if (*pos < 0) *pos = 0;
		else if (*pos > screen_leng - 1) *pos = screen_leng - 1;
	}
	void move()
	{
		position = rand() % 5 - 2;
		check_range(&position, 119);	//119 -> 에비(상속사용 예정)
	}

	void change_emotion()
	{
		
	}

	int get_position()
	{
		return position;
	}
	char* get_emotion()
	{
		return emotion;
	}
	int get_frame_attacked()
	{
		return frame_attacked;
	}
};