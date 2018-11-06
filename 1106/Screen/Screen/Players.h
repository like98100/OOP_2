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
	//Container<Player*>	container; //(��ü�� �����ؼ� �����̳ʰ� ������ �����Ƿ�) ���� �����ڷ� ���� ��ü�� 2���� ���� �� ����. 
                                                //�����̳ʿ��� �̹� ����� ������ �ּҸ� ������ ����

                                                //c++ 2015/2017 - move : �޸� ��ü �̵�(���簡 �ƴ� �̵�)

public:
	Players(Renderer& renderer) : container(1), renderer(renderer)
	{
		//container.add(new BlinkablePlayer(renderer));
        container.push_back(new BlinkablePlayer(renderer));
	}

	Player* getMainCharacter()      //�׾��� ���� ��ȯ�� ���� & ���x(&����ϸ� ������ ���� �۵��ϹǷ�)
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
        //���ͷ����� (C++ 2015~)
        //�ε��� ���۷��̼�(�迭 ����)�� range üũ�� ����(C# ����)
        //begin() : �������� / end() : ������(���� ����) ��ü�� ����(���� ������ ����)
        //vector<Player*>::iterator it;
        for (auto it = container.begin(); it != container.end(); it++)
        {
            (*it)->update();
        }
        //3
        //for each (���� : ���� ���� �ٲ�� �ȵ�)
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

         //lambda(����) function
         //remove_if : if���̸� ���� (#include <algorithm>)
         container.erase(remove_if(container.begin(), container.end(), 
         [](Player* player) {
            return player->isAlive() == false;
         }
         ), container.end());        //begin(), end()�� �ְ� []�Լ��� true�� ������ �ֽʽÿ�.(remove_if �κ�)
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
