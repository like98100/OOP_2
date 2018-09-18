#pragma once
class Enemy
{
	int position;
	char *emotion;		//pointer 사용 권장
	char *emotion_attacked;
	//string emotion;
	int frame_attacked;
public:
	Enemy(int pos, char* emo, char* emo_att, int fram) : position(pos), emotion(emo), emotion_attacked(emo_att), frame_attacked(fram) {}
	void check_range(int* pos, int screen_leng)
	{
		if (*pos < 0) *pos = 0;
		else if (*pos > screen_leng - 1) *pos = screen_leng - 1;
	}
	void move(int leng)
	{
		position = rand() % 5 - 2;
		check_range(&position, leng);
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
	int get_frame_attacked()
	{
		return frame_attacked;
	}
	void set_frame_start()
	{
		this->frame_attacked = 0;
	}
	void set_frame()
	{
		if (this->frame_attacked < 10) this->frame_attacked++;
	}
	void set_emotion(bool check)
	{
		char* temp;
		if (this->frame_attacked < 10)
		{
			if (emotion != "(ㅇ,.ㅇ)")
			{
				temp = emotion;	emotion = emotion_attacked;	emotion_attacked = temp;
			}
		}
		else 
		{ 
			check = false;
			temp = emotion;	emotion = emotion_attacked;	emotion_attacked = temp;
		}
	}
};