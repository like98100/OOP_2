#ifndef BULLETS_H_
#define BULLETS_H_

#include "Renderer.h"
#include "Bullet.h"
#include "Players.h"
#include "Enemies.h"

using namespace std;


class Bullets {
	Renderer&	renderer;
	Players&	players;
	Enemies&	enemies;
    vector<Bullet*> container;
	//Container<Bullet*> container;
	int			n_remaining_cool_time;

public:
	Bullets(Renderer& renderer, Players& players, Enemies& enemies)
		: container(10), renderer(renderer), players(players), enemies(enemies), n_remaining_cool_time(0)
	{}

	void add(Bullet* bullet)
	{
		if (!bullet) return;
		if (n_remaining_cool_time > 0) {
			n_remaining_cool_time--;
			delete bullet;
			return;
		}
		//if (container.count() >= container.capacity()) {
            if (container.size() >= container.capacity()) {
			if (n_remaining_cool_time == 0) {
				n_remaining_cool_time = 30 * 2;
			}
			delete bullet;
			return;
		}
		//container.add(bullet);
            container.push_back(bullet);
	}

	void fire(const Player& player)
	{
		//if (player == nullptr || enemies == nullptr) return;
		auto /*Enemy* */ target = enemies.findClosest(player.getPosition());
		if (target == nullptr) return;
		float player_pos = player.getPosition();
		float enemy_pos = target->getPosition();
		if (renderer.checkRange(player_pos) == false || renderer.checkRange(enemy_pos) == false) return;
		char shape[2] = ">";
		if (player_pos > enemy_pos) shape[0] = '<';
		add(new Bullet(renderer, player_pos, shape));
	}

	void update()
	{
		if (n_remaining_cool_time > 0)
			n_remaining_cool_time--;
        for(auto bullet : container) bullet->update();

        for (auto it = container.begin(); it != container.end();)
        {
            auto bullet = *it;
            if (renderer.checkRange(bullet->getPosition()) == false || enemies.isShoted(*bullet) == true)
            {
                container.remove(*it);
            }
            else it++;
        }
       /* container.erase(remove_if(container.begin(), container.end(),
            [](Bullet* bullet)
        {
            return renderer.checkRange(bullet->getPosition()) == false ||
             enemies.isShoted(*bullet) == true;
        })
        , container.end());*/

		//for (int i = 0; i < container.capacity(); i++) {
		//	if (!container[i]) continue;
		//	auto bullet = container[i];
		//	float pos = bullet->getPosition();
		//	if (renderer.checkRange(pos) == false || enemies.isShoted(*bullet) == true) {
		//		container.remove(bullet);
		//		continue;
		//	}
		//	bullet->update();
		//}

		//Borland::gotoxy(0, 3); printf("# of bullets = %2d ", container.count());
        Borland::gotoxy(0, 3); printf("# of bullets = %2d ", container.size());
		printf("%5s\n", n_remaining_cool_time == 0 ? "ready" : " ");
	}

	void draw()
	{
    for(auto bullet : container) bullet->draw();
		//for (int i = 0; i < container.capacity(); i++)
		//{
		//	if (!container[i]) continue;
		//	container[i]->draw();
		//}
	}
};

#endif
