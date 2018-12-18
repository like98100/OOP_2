#pragma once

#include <vector>
#include "Component.h"

class Scene
{
	vector<GameObject*> gameObject;
	bool exitFlag;
public:
	Scene() : exitFlag(false)
	{
		auto player = new GameObject("player");
		player->AddComponent<MoveScript>();
		
		auto move = player->GetComponent<MoveScript>();
		move->Start();


		auto enemy = new GameObject("enemy");
		enemy->AddComponent<AutoMoveScript>();

		auto autoMove = enemy->GetComponent<AutoMoveScript>();
		autoMove->Start();

		enemy->AddComponent<MyNewScript>();
		auto myNew = enemy->GetComponent<MyNewScript>();
		myNew->Start();
	}
	void loop()
	{

	}
};