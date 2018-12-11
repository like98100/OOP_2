#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "GameObject.h"
#include "InputManager.h"
using namespace std;


class Scene
{
    vector<GameObject*> gameObjects;
    bool exitFlag;
public:
    Scene() : exitFlag(false)
    {
        //GameObject player;  //
        //GameObject enemy;   // 지역변수
        //auto player = new GameObject();
        ////player->AddComponent<MoveScript>();
        //auto enemy = new GameObject();
        ////enemy->AddComponent<AutoMoveScript>();

        //gameObjects.push_back(player);
        //gameObjects.push_back(enemy);

    }

    ~Scene()
    {
        while (!gameObjects.empty())
        {
            auto object = gameObjects.back();
            delete object;
            gameObjects.pop_back();
        }
    }

    void loop()
    {
        while (!exitFlag)
        {
            // handle input
            if (InputManager::GetKeyDown(KeyCode::Escape)) break;
            //or exitFlag = true;


            for (auto obj : gameObjects)
            {
                //obj->update();
            }

            InputManager::endOffFrame();
        }
    }
};

#endif // _SCENE_H