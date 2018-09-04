#include <stdio.h>
//#include <stdlib.h>
#include <Windows.h>
int main()
{

	//int i = 0;
	//while (1)
	//{
	//	//printf("  \r%d\r", i++ % 100);	//\r은 \n과 비슷하나 다음 문자를 쓸 때 커서의 위치가 현재 줄이다
	//	printf("%d\r", i++ % 100);
	//	/*_sleep(100);*/
	//	Sleep(100);
	//	//printf("  \r");
	//	system("cls");						//시스템 함수
	//}


	//카운트다운(숫자 가운데 정렬)

	//int i = 10;
	//while (1)
	//{

	//	for (int k = 0; k < 55; k++) printf(" ");
	//	printf("%d\r", i--);

	//	Sleep(1000);
	//	for (int k = 0; k < 55; k++) printf(" ");
	//	printf("  \r");

	//	if (i <= -1) break/*exit(0)*/;
	//}


	//const int screen_leng = 120;
	//char scr[screen_leng];
	//char player[] = "^,.^";
	//char enemy[] = "ㅡ,.ㅡ";
	//for(int i = 10; i >= 0; i--)
	//{

	//	for (int j = 0; j < screen_leng; j++) scr[j] = ' ';
	//	//printf("%d\r", i--);

	//	sprintf(scr + screen_leng / 2, "%2d", i);
	//	/*scr[screen_leng] = '\r';*/
	//	printf("%s \r", scr);
	//	Sleep(1000);

	//	//printf("  \r");
	//}

	const int screen_leng = 119;
	char scr[screen_leng +2];
	char player[] = "(^,.^)";
	char enemy[] = "(ㅡ,.ㅡ)";
	int pos_pl = 30;
	int pos_en = 50;
	for(int i = 10; i >= 0; i--)
	{

		for (int j = 0; j < screen_leng; j++) scr[j] = ' ';
		//printf("%d\r", i--);

		//strcpy(scr + pos_pl, player);	// null문자까지 복사됨
		strncpy(scr + pos_pl, player, strlen(player));	// 내가 원하는 부분까지 복사됨
		strncpy(scr + pos_en, enemy, strlen(enemy));

		scr[screen_leng] = '\r';
		scr[screen_leng+1] = '\0';

		//sprintf(scr + screen_leng / 2, "%2d", i);
		/*scr[screen_leng] = '\r';*/
		printf("%s \r", scr);
		Sleep(1000);

		//printf("  \r");
	}

	return 0;
}