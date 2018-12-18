#pragma once

#include <iostream>
#include "Vector2.h"
#include "InputManager.h"
class GameObject;
class Transform;

using namespace std;

class Component
{
	GameObject* gameObject;
	Transform* transform;
	friend class GameObject;
protected:
	virtual void start() { cout << "comp start" << endl; }
	virtual void update() {}
	virtual void onDestroy() {}
public:
	Component(GameObject* gameObject, Transform* transform) : gameObject(gameObject), transform(transform)
	{

	}


};

class Transform : public Component
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
public:
	Transform(GameObject* gameObject, 
		const Vector2& pos = Vector2::zero, 
		const Vector2& rotation = Vector2::zero, 
		const Vector2& scale = Vector2::one) :
		Component(gameObject, this), position(pos), rotation(rotation), scale(scale) {}
};

class MoveScript : public Component
{
protected:
	void start() { cout << "move script start" << endl;}
	void update();
	/*void update()
	{
		if (InputManager::GetKeyDown(KeyCode::LeftArrow))
		{
			cout << "move left" << endl;
			cout << gameObject->getName() << endl;
		}
		if (InputManager::GetKeyDown(KeyCode::RightArrow))
		{
			cout << "move right" << endl;
		}
	}*/
public:
	MoveScript(GameObject* gameObject, Transform* transform) : Component(gameObject, transform) {}
};


class AutoMoveScript : public Component
{
protected:
	void start() { cout << "auto move script start" << endl; }
	void update();
};

// virtual void start() { cout << "comp start" << endl; }
// movescript -> start() { cout << "move script start" << endl;}
// automove -> start() { cout << "auto move script start" << endl;}


//transform -> Transform(GameObject* gameObject, const Vector2& pos = Vector2::zero, const Vector2& rotation = Vector2::zero, const Vector2& scale = Vector2:: one) :


//template<Typename T>
//Component* GetComponent()
//{
//	for (auto comp : components)
//	{
//		if (dynamic_cast<T *>(comp) != nullptr) return comp;
//	}
//	return nullptr;
//}

//	Component(gameObject, this), position(pos), rotation(rotation), scale(scale) {}

class MyNewScript : public Component
{
	int n_frames;
protected:
	void start();
	void update();
public:
	MyNewScript(GameObject* gameObject, Transform* transform) : Component(gameObject, transform){}
};