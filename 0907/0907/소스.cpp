#include <stdio.h>
//#include <stdlib.h>
#include <Windows.h>

//void check_range(int* pos, int rand, int screen_leng);
void check_range(int* pos, int screen_leng);

int main()
{

	const int screen_leng = 119;
	char scr[screen_leng + 1 + 1]; // \0, NULL
	///*const*/ char player[] = "(^,.^)";		//정적할당 상태(const 있는 것과 같음)
	///*const*/ char enemy[] = "(ㅡ,.ㅡ)";
	char player[100];
	char enemy[100];
	strcpy(player, "(^,.^)");		strcpy(enemy, "(ㅡ,.ㅡ)");
	int pos_player = 30;	int pos_enemy = 50; int rand_player, rand_enemy;
	while (1)
	{
		for (int i = 0; i < screen_leng; i++) scr[i] = ' ';
		
		strncpy(scr + pos_player, player, strlen(player));
		strncpy(scr + pos_enemy, enemy, strlen(enemy));

		rand_player = rand()%3 - 1;
		rand_enemy = rand()%5 - 2;

		pos_player += rand_player; pos_enemy += rand_enemy;
		
		check_range(&pos_player, screen_leng);
		check_range(&pos_enemy, screen_leng);

		/*check_range(&pos_player, rand_player, screen_leng);
		check_range(&pos_enemy, rand_enemy, screen_leng);*/

		//pos_player += rand_player; pos_enemy += rand_enemy;

		scr[screen_leng] = '\r';
		scr[screen_leng+1] = '\0';
		printf("%s", scr);

		Sleep(1);
	}

	return 0;
}

//void check_range(int/*&*/* pos, int rand, int screen_leng)
//{
//	if (rand + *pos < 0) rand = 0;
//	else if (rand + *pos > screen_leng) rand = -1;
//}

void check_range(int* pos, int screen_leng)
{
	if (*pos <= 0) *pos = 0;
	else if (*pos >= screen_leng) *pos = screen_leng -1;
}