#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>	//need to use kbhit
#define bullet 25

//void check_range(int& pos, int screen_leng)
//{
//	if (pos < 0) pos = 0;
//	if (pos >= screen_leng - 1) pos = screen_leng - 1;
//}

void check_range(int* pos, int screen_leng)
{
	if (*pos < 0) *pos = 0;
	if (*pos >= screen_leng - 10) *pos = screen_leng - 10;
}

int main()
{

	const int screen_leng = 119;
	char scr[screen_leng + 1 + 1]; // \0, NULL
	int pos_player = 30;
	int pos_enemy = 50;
	char player[100];
	char enemy[100];

	//int pos_bullet = -1;
	int pos_bullet[bullet*5];
	int sec_enemy = 20;
	int cnt_bullet = 0;
	int cnt_bullet_first = 0;

	for (int i = 0; i < bullet*5; i++) pos_bullet[i] = -1;

	while (1)
	{
		//for (int i = 0; i < screen_leng; i++) scr[i] = ' ';

		memset(scr, 0, screen_leng);
		memset(scr, ' ', screen_leng);											//scr[3]과 같이 입력할 경우 scr[3]부터 screen_leng 개 만큼 채워진다.

		//pos_player += rand() % 3 - 1;
		//pos_enemy += rand() % 5 - 2;

		//char move = getchar();	// getchar() -> Blocking Function(need Enter)
		//switch (move)
		//{
		//case 'a':
		//	pos_player -= 1;
		//	break;
		//case 'd':
		//	pos_player += 1;
		//	break;
		//default:
		//	break;
		//}

		// _kbhit, _getchar, etc... _Function == 비표준
		if (_kbhit())			//Non-Blocking Fuction
		{
			char move = getch();
			//printf("%d", move);

			if (move == 27) break; //esc == 27
			if (move == -32) move = getch();		//arrow pad
			switch (move)
			{
			case 'a': case 75:		//Left
				pos_player -= 3;
				break;
			case 'd': case 77:		//Right
				pos_player += 3;
				break;
			case 80:					//Up
				pos_enemy += 3;
				break;
			case 72:
				pos_enemy -= 3;		//Down
				break;
			case ' ':					//shot
				if(cnt_bullet_first != bullet*5) cnt_bullet_first++;
				if (cnt_bullet < bullet)
				{
					pos_bullet[cnt_bullet] = pos_player;
					cnt_bullet++;
				}
				break;
			case 'r':				//reload
					//cnt_bullet = 0;
					break;
			default:
				break;
			}
		}

		check_range(&pos_player, screen_leng);
		check_range(&pos_enemy, screen_leng);


		strcpy(player, "(ㅅ,.ㅅ)");

		if(sec_enemy < 10) strcpy(enemy, "(ㅇ,.ㅇ)");
		else strcpy(enemy, "(ㅡ,.ㅡ)");


		//strncpy(scr + pos_player, player, strlen(player));
		//strncpy(scr + pos_enemy, enemy, strlen(enemy));

		memcpy(&scr[pos_player], player, strlen(player));
		memcpy(&scr[pos_enemy], enemy, strlen(enemy));

		for (int i = 0; i < cnt_bullet_first; i++)
		{
			if (pos_bullet[i] >= 0 && pos_bullet[i] <= screen_leng && pos_bullet[i] != -1)
			{
				if (pos_bullet[i] < pos_enemy + 1) { pos_bullet[i]++; scr[pos_bullet[i]] = '>'; }
				else if (pos_bullet[i] > pos_enemy - 1) { pos_bullet[i]--; scr[pos_bullet[i]] = '<'; }
				if (pos_bullet[i] == pos_enemy + 1 || pos_bullet[i] == pos_enemy - 1 || pos_bullet[i] == pos_enemy)
				{
					pos_bullet[i] = -1;
					//cnt_bullet--;
					if (cnt_bullet < 0 || cnt_bullet >= 6) cnt_bullet = 0;
					sec_enemy = 0;
					strcpy(enemy, "(ㅇ,.ㅇ)");
					memcpy(&scr[pos_enemy], enemy, strlen(enemy));
				}
		}

		
		}



		scr[screen_leng] = '\r';	 scr[screen_leng + 1] = 0;
		printf("%s", scr);

		if (sec_enemy < 10) sec_enemy++;

		Sleep(100);

		//Sleep(10);
	}


	return 0;
}