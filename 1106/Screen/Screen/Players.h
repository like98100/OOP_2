#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <iostream>
#include <cmath>
#include "Renderer.h"
#include "Player.h"
//#include "Container.h"
#include <vector>
#include <algorithm>
using namespace std;

class Players {
	Renderer&			renderer;
	//Player*				main;
    vector<Player*> container;
	//Container<Player*>	container; //(객체를 복사해서 컨테이너가 가지고 있으므로) 복사 생성자로 인해 객체가 2개가 생길 수 있음. 
                                                //컨테이너에는 이미 만든게 있으니 주소만 가지고 있음

                                                //c++ 2015/2017 - move : 메모리 객체 이동(복사가 아닌 이동)

public:
	Players(Renderer& renderer) : container(1), renderer(renderer)
	{
		//container.add(new BlinkablePlayer(renderer));
        container.push_back(new BlinkablePlayer(renderer));
	}

	Player* getMainCharacter()      //죽었을 떄도 반환을 위해 & 사용x(&사용하면 존재할 때만 작동하므로)
	{
		//if (container.count() == 0) return nullptr;
        if (container.size() == 0) return nullptr;
        return container[0];

		//for (int i = 0; i < container.capacity(); i++) {
        //for (int i = 0; i < container.size(); i++) {
		//	if (container[i] != nullptr) return container[i];
		//}
		//return nullptr;
	}

	void update()
	{
        //1
		//for (int i = 0; i < container.capacity(); i++) {
        //for (int i = 0; i < container.size(); i++) {
		//	//if (!container[i]) continue;
		//	container[i]->update();
		//}

        //2
        //이터레이터 (C++ 2015~)
        //인덱스 오퍼레이션(배열 형식)은 range 체크를 안함(C# 제외)
        //begin() : 시작지점 / end() : 마지막(내가 만든) 객체의 다음(내가 만들지 않은)
        //vector<Player*>::iterator it;
        for (auto it = container.begin(); it != container.end(); it++)
        {
            (*it)->update();
        }
        //3
        //for each (단점 : 내부 값이 바뀌면 안됨)
        //for (auto player : container)
        //{
        //    player->update();
        //}

        //for (int i = 0; i < container.capacity(); i++) {
        //for (int i = 0; i < container.size(); i++) {
        //	if (!container[i]) continue;
        //	if (container[i]->isAlive() == false) container.remove(i);
        //}

        //for (auto it = container.begin(); it != container.end();)
        //{
        //    if((*it)->isAlive() == false) container.remove(*it);
        //    else it++;
        //}

         //lambda(람다) function
         //remove_if : if문이면 삭제 (#include <algorithm>)
         container.erase(remove_if(container.begin(), container.end(), 
         [](Player* player) {
            return player->isAlive() == false;
         }
         ), container.end());        //begin(), end()가 있고 []함수가 true면 삭제해 주십시오.(remove_if 부분)
	}

	void draw()
	{
        for(auto player : container) player->draw();
		//for (int i = 0; i < container.capacity(); i++) {
		//	if (!container[i]) continue;
		//	container[i]->draw();
		//}
		Borland::gotoxy(0, 1); printf("player "); getMainCharacter()->displayStat();
	}
};

#endif
