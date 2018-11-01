#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <iostream>
#include <cmath>
#include "Renderer.h"
#include "Player.h"
#include "Container.h"

#include <vector>

class Players {
	Renderer*			renderer;
	Player*				main;
	//Container<Player*>	container;
    vector<Player*> container;

public:
	Players(Renderer* renderer) : /*container(1, (vector ver) nullptr),*/ renderer(renderer)
	{ 
        /*vector*/ auto it = container.begin();
		//container.add(new BlinkablePlayer(renderer));
        
        //container.insert(it, new BlinkablePlayer(renderer));
        container.push_back(new BlinkablePlayer(renderer));
	}

	Player* getMainCharacter()
	{
		if (container.size()/*count()*/ == 0) return nullptr;
        return container[0];
		//for (int i = 0; i < container.size()/*capacity() <- 동적화 할당으로 인해 의미가 없음*/; i++) {
		//	/*if (container[i] != nullptr)*/ return container[i];
		//}
		//return nullptr;
	}

	void update()
	{
		for (int i = 0; i < container.size()/*capacity()*/; i++) {
			//if (!container[i]) continue;
			container[i]->update();
		}

		for (int i = 0; i < container.size()/*capacity()*/; i++) {
			//if (!container[i]) continue;
            if (container[i]->isAlive() == false)
            {
                container.erase(container.begin() + i); i--; //container.remove(i);
            }
             
		}
	}

	void draw()
	{
		for (int i = 0; i < container.size()/*capacity()*/; i++) {
			//if (!container[i]) continue;
			container[i]->draw();
		}
		Borland::gotoxy(0, 1); printf("player "); getMainCharacter()->displayStat();
	}
};

#endif

