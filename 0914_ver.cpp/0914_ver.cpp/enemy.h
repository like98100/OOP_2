#pragma once
class Enemy
{
	int position;
	char *emotion;		//pointer ��� ����
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
		check_range(&position, 119);	//119 -> ����(��ӻ�� ����)
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