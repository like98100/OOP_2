#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>

/*
1. Enemy hp �ο�, �ʱⰪ hp = 10, hp == 0�� �Ǹ� ���� ������ ȭ�鿡�� ������ ����.
2. ���� ������ ���� �Ұ�
3. ���� ��� ����, �÷��̾�� �ִ� 10���� 1������ �������� �� �� ����.�����̽��ٷ� ���� �� �� ����.źâ�� ����ٸ� 2�ʰ� cool time �����Ͽ� ���� �� �� ����.
4. �Ѿ��� ������ 1�� �������� ��
5. ���� ���� ������, ������ ��ġ���� spawn ������.
6. �ѹ��� spawn�� ���� �ִ� 5����.
7. ���� �÷��̾�� 1�ʿ� 2ĭ��(0.5�ʿ� 1ĭ) �̵���.
8. ���� �÷��̾� ������ 2ĭ �̳��� ���� �÷��̾�� 1�ʴ� 2��ŭ �������� ����(�� �����Ӹ��� ���������� �������� ����)
9. �÷��̾ �������� �޴� ���� �÷��̾� ����� ���ڱ��� �Ÿ�.�������� ���� ������ ���� ����.
10. �÷��̾ ������ ������ ����ǰ� ���� ���� ���� �÷��̾ ����ִ� �ð��� ȭ�鿡 ������

NOTE:
���� �ڵ�� �÷��̾�� ������ �Ÿ��� ���ϴ� ������ �ſ� �ܼ��ϰ� ǥ���Ǿ� ����. ������ �ʿ���.
�Ѿ� �̵��� ���� �Ѿ˰��� �Ÿ��� ���� ����� ����� �Ǿ� ���� ����.

*/

struct Position {

	int x;
	int y;
	Position(int x, int y) : x(x), y(y) {}
};

class Borland {

public:
	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Position* pos)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)pos->x, (SHORT)pos->y});
	}
};

class Renderer {
	static const int screen_size = 119;
	char display[screen_size + 1 + 1];
	Position origin;
	
public:
	Renderer() : origin( Borland::wherex(), Borland::wherey() ) {
		// ���� ���� �������� �õ尪�� 10���� �����Ͽ� ������ ���� ���ڰ� �����ǵ��� ����.
		// ����� ����.
		// release�ÿ��� time(nullptr)�� �ٲپ� �õ尪�� ���������� �����ؾ� ��.
		//srand(10);
		srand(time(nullptr));
	}


	bool checkRange(const char* shape, int pos)
	{
		if (!shape) return false;
		if (pos < 0) {
			if (pos + (int)strlen(shape) >= 0) return true;
		}
		else {
			if (pos + strlen(shape) < screen_size) return true;
		}
		return false;
	}

	bool checkRange(int pos)
	{
		return pos >= 0 && pos < (screen_size - 1);
	}

	void clear() {
		memset( display, ' ', screen_size);
		display[screen_size] = '\n';
		display[screen_size+1] = '\0';
	}
	
	void draw(const char* shape, int pos)
	{
		int dest_pos = pos;
		if (checkRange(shape, pos) == false) return;

		const char* source = shape;
		int len = strlen(shape);
		if (pos < 0) {
			source = shape - pos;
			len += pos;
			dest_pos = 0;
		}
		else if (pos + strlen(shape) > screen_size - 1) {
			len = screen_size - pos;
		}
		memcpy(display + dest_pos, source, len);
	}

	void render()
	{
		// make sure it should end with proper ending characters.
		display[screen_size] = '\n';
		display[screen_size + 1] = '\0';

		Borland::gotoxy(&origin);
		printf("%s", display);
		Borland::gotoxy(&origin);
	}

	int getScreenLength()
	{
		return screen_size;
	}
};

class GameObject
{
	float pos;
	char shape[100];

public:
	GameObject(float pos, const char* shape) : pos(pos) { strcpy(this->shape, shape); }
	//float getPosition() const { return pos; }
	int getPosition() const { return (int)pos; }
	virtual void move(int inc) { pos += inc; }
	const char* getShape() { return shape; }
	virtual void update() {}
};

class Player : GameObject{
	float hp;
	//float pos;
	//char face[100];
	int n_blinks;
	float damage_ratio;
	bool isDamanaged;
public:
	Player(int hp = 10, int pos = 20, const char *shape="(-_-)") : GameObject(pos, shape), hp(hp), n_blinks(0), damage_ratio(2.0f/30) { }
	void move(int inc) { float pos = getPosition();	pos += inc; }

	//int getPosition() const { return (int)pos;  }
	//const char* getShape() { return face; }	
	
	void update() {
		if (n_blinks > 0) n_blinks--;
	}

	bool isBlinking() { return n_blinks > 0;  }

	bool isAlive() { return hp > 0.0f;  }

	void getDamanagedIfIntruded(float enemy_pos) 
	{
		float pos = getPosition();
		if (fabs(pos - enemy_pos) > 2.0f) return;
		hp -= damage_ratio;
		n_blinks = 2;
	}

	void display_stat() 
	{
		printf("hp = %2d, n_blinks = %2d", (int)hp, n_blinks);
	}
};

class Players {
	static const int maxPlayers = 1;
	int n_players;
	Player* players[maxPlayers];
	Renderer* renderer;
	Player* main;

public:
	Players(Renderer* renderer) : renderer(renderer), n_players(0) {
		for (int i = 0; i < maxPlayers; i++) players[i] = nullptr;
		add(new Player());
	}

	Player* getMainCharacter()
	{
		if (n_players == 0) return nullptr;
		for (int i = 0; i < maxPlayers; i++)
			if (players[i] != nullptr) return players[i];
		return nullptr;
	}

	
	void add(Player* player)
	{
		if (n_players >= maxPlayers || player == nullptr) return;
		for (int i = 0; i < maxPlayers; i++) {
			if (players[i] == nullptr) {
				players[i] = player;
				n_players++;
				return;
			}
		}
		delete player;
		Borland::gotoxy(0, 2);  printf("there is no room for adding a new player");
	}

	void remove(Player* player)
	{
		if (n_players == 0 || player == nullptr) return;
		for (int i = 0; i < maxPlayers; i++) {
			if (players[i] == player) {
				delete players[i];
				n_players--;
				players[i] = nullptr;
				return;
			}
		}
	}

	void update()
	{
		for (int i = 0; i < maxPlayers; i++) {
			if (players[i] == nullptr) continue;
			players[i]->update();
		}

		for (int i = 0; i < maxPlayers; i++) {
			if (players[i] == nullptr) continue;
			if (players[i]->isAlive() == false) {
				remove(players[i]);
			}
		}
	}

	void draw()
	{
		for (int i = 0; i < maxPlayers; i++) {
			if (players[i] == nullptr) continue;
			if (players[i]->isBlinking()) {
				renderer->draw(rand() % 2 ? players[i]->getShape() : " ", players[i]->getPosition());
			}
			else {
				renderer->draw(players[i]->getShape(), players[i]->getPosition());
			}
		}
		Borland::gotoxy(0, 1); printf("player "); getMainCharacter()->display_stat();
		
	}

	
};


class Enemy : GameObject{
	float hp;
	//float pos;
	char face[100];
	char faceAttacked[100];
	//char shape[100];
	int nAnimations;
	Player* target;
	float speed = 2.0f/30;

public:
	Enemy(Player* target, int pos = 50, int hp = 5, const char* face="(*_*)", const char* faceAttacked="(>_<)") : GameObject(pos, face), target(target), nAnimations(0), hp(hp)
	{ 
		strcpy(this->face, face);
		strcpy(this->faceAttacked, faceAttacked);
		//strcpy(this->shape, face);
	}
	//void move(int inc) { pos += inc; }
	void move(float inc) { float pos = getPosition(); pos += inc; }
	//int getPosition() const { return (int)pos; }
	//const char* getShape() { return shape; }	

	void update()
	{
		float pos = getPosition();

		if (!target) return;
		int player_pos = target->getPosition();
		if (player_pos < pos) move(-1*speed);
		else if (player_pos > pos) move( 1*speed);
		else { } // do not move

		// attack if in range
		target->getDamanagedIfIntruded(pos);


		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			strcpy(shape, face);
		}
	}
	void OnHit()
	{
		hp -= 1.0f;
		nAnimations= 30;
		strcpy(shape, faceAttacked);
	}

	bool isAlive() {
		return hp > 0.0f;
	}
};


class Bullet : GameObject{
	//int pos;
	//char shape[10];
public:
	Bullet(int player_pos = -1, const char* shape = ">") : GameObject(player_pos, shape) {
		//strcpy(this->shape, shape);
	}
	//void move(int inc) { pos += inc; }
	//int getPosition() { return pos; }
	//const char* getShape() { return shape; }
	int getDirection() { char shape[10] = getShape(); return strcmp(shape, ">") == 0 ? 1 : -1; }

	void update()
	{
		if (isAlive() == false) return;
		if (strcmp(shape, ">") == 0) move(1);
		else if (strcmp(shape, "<") == 0) move(-1);
	}
	bool isAlive() { int pos = getPosition();	return pos != -1; }
};


class Enemies {
	static const int maxEnemies = 5;
	int n_enemies;
	Enemy* enemies[maxEnemies];
	int n_killed;

	Renderer* renderer;
	Player* target;

	int n_remainings_for_respawn;

public:
	Enemies(Renderer* renderer, Player* target) 
		: renderer(renderer), n_enemies(0), n_killed(0), n_remainings_for_respawn(30), target(target) {
		for (int i = 0; i < maxEnemies; i++) enemies[i] = nullptr;
		add(new Enemy(target, rand() % renderer->getScreenLength() ));
	}

	int getNumberOfKilled()
	{
		return n_killed;
	}

	void add(Enemy* enemy) {
		if (n_enemies >= maxEnemies || enemy == nullptr) return;

		for (int i=0; i < maxEnemies; i++)
		{
			if (enemies[i] == nullptr) {
				// found an empty slot
				enemies[i] = enemy;
				n_enemies++;
				return;
			}
		}
		delete enemy;
	}

	void remove(Enemy* enemy) {
		if (n_enemies == 0 || enemy == nullptr) return;

		for (int i = 0; i < maxEnemies; i++)
		{
			if (enemies[i] == enemy) {
				delete enemies[i];
				n_enemies--;
				enemies[i] = nullptr;
				return;
			}
		}
	}

	int indexOf(Enemy* enemy) {
		if (n_enemies == 0 || enemy == nullptr) return -1;

		for (int i = 0; i < maxEnemies; i++) 
		{
			if (enemies[i] == enemy) return i;
		}
		return -1;
	}

	void update()
	{
		// enemy spawning related code
		if (n_remainings_for_respawn <= 0) {
			// reset the timer for the next enemy spawning
			add(new Enemy(target, rand() % renderer->getScreenLength()));
			n_remainings_for_respawn = 30;
		}
		else
			n_remainings_for_respawn--;

		for (int i = 0; i < maxEnemies; i++) {
			if (enemies[i] == nullptr) continue;
			enemies[i]->update();
			if (enemies[i]->isAlive() == false) {
				n_killed++;
				remove(enemies[i]);
			}
		}
		Borland::gotoxy(0, 2); printf("# of enemies = %2d\n", n_enemies);
	}

	void draw()
	{
		for (int i = 0; i < maxEnemies; i++) {
			if (enemies[i] == nullptr) continue;
			renderer->draw(enemies[i]->getShape(), enemies[i]->getPosition());
		}
	}


	Enemy* findClosest(int pos)
	{
		Enemy* closest = nullptr;
		float dist = 0.0f;
		if (renderer->checkRange(pos) == false) return closest;
		for (int i = 0; i < maxEnemies; i++) {
			if (enemies[i] == nullptr || renderer->checkRange(enemies[i]->getPosition()) == false) continue;
			int enemy_pos = enemies[i]->getPosition();
			float current_dist = (pos - enemy_pos)*(pos - enemy_pos);
			if (closest == nullptr) {
				dist = current_dist;
				closest = enemies[i];
				continue;
			}
			// closest != nullptr;
			if (dist > current_dist) {
				current_dist = dist;
				closest = enemies[i];
			}
		}
		return closest;
	}

	bool isShoted(Bullet* bullet)
	{
		if (!bullet) return false;
		int bullet_pos = bullet->getPosition();
		Enemy* enemy = findClosest(bullet_pos);
		if (!enemy) return false;
		int enemy_pos = enemy->getPosition();
		int bullet_direction = bullet->getDirection();
		if ( (bullet_direction == 1 && enemy_pos < bullet_pos && bullet_pos - enemy_pos <= 2) 
			|| (bullet_direction == -1 && bullet_pos < enemy_pos && enemy_pos - bullet_pos <= 2)
			|| enemy_pos == bullet_pos) {
			enemy->OnHit();
			return true;
		}
		return false;
	}
};




class Bullets {
	static const int maxBullets = 10;
	int n_bullets;
	Bullet* bullets[maxBullets];
	Renderer* renderer;
	Players* players;
	Enemies* enemies;
	int n_remaining_cool_time;

public:
	Bullets(Renderer* renderer, Players* players, Enemies* enemies) 
	: renderer(renderer), players(players), enemies(enemies), n_bullets(0), n_remaining_cool_time(0) {
		for (int i = 0; i < maxBullets; i++) bullets[i] = nullptr;
	}

	void add(Bullet* bullet) {
		if (!bullet) return;
		if (n_remaining_cool_time > 0) {
			n_remaining_cool_time--;
			delete bullet;
			return;
		}
		if (n_bullets >= maxBullets) {
			if (n_remaining_cool_time == 0) {
				n_remaining_cool_time = 30*2;
			}
			delete bullet;
			return;
		}
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i] == nullptr) {
				bullets[i] = bullet;
				n_bullets++;
				return;
			}
		}
		delete bullet;
	}

	void remove(Bullet* bullet) {
		if (n_bullets == 0 || bullet == nullptr) return;

		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i] == bullet) {
				delete bullets[i];
				n_bullets--;
				bullets[i] = nullptr;
				return;
			}
		}
	}

	void fire(const Player* player)
	{
		if (player == nullptr || enemies == nullptr) return;
		Enemy* target = enemies->findClosest(player->getPosition());
		if (target == nullptr) return;
		int player_pos = player->getPosition();
		int enemy_pos = target->getPosition();
		if (player_pos == enemy_pos || renderer->checkRange(player_pos) == false || renderer->checkRange(enemy_pos) == false) return;
		char shape[2] = ">";
		if (player_pos > enemy_pos) shape[0] = '<';
		add(new Bullet(player_pos, shape));
	}

	void update()
	{
		if (n_remaining_cool_time > 0)
			n_remaining_cool_time--;
		for (int i = 0; i < maxBullets; i++) {
			if (bullets[i] == nullptr) continue;
			int pos = bullets[i]->getPosition();
			if (renderer->checkRange(pos) == false || enemies->isShoted(bullets[i]) == true) {
				remove(bullets[i]);
				continue;
			}
			bullets[i]->update();
		}
		Borland::gotoxy(0, 3); printf("# of bullets = %2d ", n_bullets);
		printf("%5s\n", n_remaining_cool_time == 0 ? "ready" : " ");
	}

	void draw()
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i] == nullptr) continue;
			renderer->draw(bullets[i]->getShape(), bullets[i]->getPosition());
		}
	}
};

int main()
{
	Renderer renderer;
	Players players(&renderer);
	Player* main = players.getMainCharacter();
	Enemies enemies(&renderer, main);
	Bullets bullets(&renderer, &players, &enemies);

	
	clock_t current_tick, last_tick;

	last_tick = current_tick = clock();
	while (true)
	{
		renderer.clear();

		if (_kbhit()) {
			char key = _getch();
			//printf("%d\n", key);
			if (key == 27) break;
			if (key == -32) {
				key = _getch();
			}

			switch (key) {
			case 'a': case 75:
				main->move(-1);
				break;
			case 'd': case 77:
				main->move(1);
				break;
			case 72:
				break;
			case 80:
				break;
			case ' ':
				bullets.fire(main);
				break;
			}				
		}
		enemies.update();
		bullets.update();
		players.update();
		main = players.getMainCharacter();
		if (main == nullptr) break;
		
		enemies.draw();
		bullets.draw();
		players.draw();
		
		renderer.render();
		Sleep(66);
		last_tick = current_tick;
	}
	renderer.clear();
	current_tick = clock();
	Borland::gotoxy(0, 1); printf("# of killed enemies = %d, elapsed survival duration = %d seconds\n", enemies.getNumberOfKilled(),
		(current_tick - last_tick) / CLOCKS_PER_SEC );


	return 0;
}