#include <iostream>
#include <vector>
using namespace std;

class GameObject
{
	int id;
public:
	GameObject(int id) : id(id) {}
	int getId() { return id; }
	~GameObject() {}
};

ostream& operator << (ostream& out, const vector<int>& v)
{
	out << "( ";
	//vector<int>::iterator it;

	//for (int i = 0; i < v.size(); i++) out << v[i] << " ";
	//for (vector<int>::iterator it = v.begin(); it != v.end(); it++) out << (*it) << " ";
	//for (auto it = v.begin(); it != v.end(); it++) out << (*it) << " ";
	
	//for (auto it = v.rbegin(); it != v.rend(); it++) out << (*it) << " ";

	//const 사용 시 c 붙이면 됨
	for (auto it = v.cbegin(); it != v.cend(); it++) out << (*it) << " ";
	//for (auto it = v.crbegin(); it != v.crend(); it++) out << (*it) << " ";
	out << ")";
	return out;
}

ostream& operator << (ostream& out, const vector<GameObject *>& v)
{
	out << "( ";
	for (auto it = v.cbegin(); it != v.cend(); it++)
	{
		auto item = *it;
		out << item->getId() << " ";
	}
	out << ")";
	return out;
}

ostream& operator << (ostream& out, const vector<GameObject>& v)
{
	out << "( ";
	for (auto it = v.cbegin(); it != v.cend(); it++)
	{
		auto item = *it;
		out << item.getId() << " ";
	}
	out << ")";
	return out;
}

void main()
{
	//vector<int> v(10);

	//// 41,67,34,0,69,24,78,58,62,64
	//int arr_v[] = { 41,67,34,0,69,24,78,58,62,64 };

	//x
	//v.push_back(41); v.push_back(67); v.push_back(34);... // 명령이 세번 이상이면 그냥 함수 써라
	
	//1
	//for (int i = 0; i < v.size; i++) v.push_back(arr_v[i]);
	
	//2
	//vector<int> v{ 41,67,34,0,69,24,78,58,62,64 };
	//
	//cout << "Before " <<  v << endl;

	//동적 할당

	//vector<GameObject *> v_go{ new GameObject(41), new GameObject(67), new GameObject(34), new GameObject(0), new GameObject(69), new GameObject(24), 
	//	new GameObject(78), new GameObject(58), 
	//	new GameObject(62), new GameObject(64) };

	int v_arr[]{41, 67, 34, 0, 69, 24, 78, 58, 62, 64};
	vector<GameObject *> v_go(10);
	for (int i = 0; i < 10; i++)
	{
		v_go[i] = new GameObject(v_arr[i]);
	}
	cout << "Before " << v_go << endl;

	for (vector<GameObject *>::iterator it = v_go.begin(); it != v_go.end(); )
	{
		auto item = *it;	//복사 연산자 호출
		if (item->getId() % 2 == 0)
		{
			it = v_go.erase(it);
		}
		else it++;
	}

	/*for (int i = 0; i < v_go.size(); )
	{
		if (v_go[i]->getId() % 2 == 0)
		{
			for (auto j = i + 1; j < v_go.size(); j++)
			{
				auto temp = v_go[j];
				v_go[j+1] = v_go[j];
				v_go[j] = temp;
				//맨뒤로 보내버리고 pop 하면 되는데 뇌정지옴
			}
		}
		else i++;
	}*/
	cout << "After " << v_go << endl;

	//동적 해제

	for (auto it = v_go.begin(); it != v_go.end(); it++)
	{
		delete *it;	//GameObject라는 자료형을 가지고 있으므로 * 추가
		*it = nullptr;
	}


	cout << endl;

	//이 방법은 복사 생성자 함수를 호출함
	//추천하지 않는 방법
	vector<GameObject> v_npgo{ GameObject(41), GameObject(67), GameObject(34), GameObject(0), GameObject(69), GameObject(24),
	 GameObject(78), GameObject(58),
		GameObject(62), GameObject(64) };
	cout << "Before " << v_npgo << endl;

	for (vector<GameObject>::iterator it = v_npgo.begin(); it != v_npgo.end(); )
	{
		auto item = *it;	//복사 연산자 호출
		if (item.getId() % 2 == 0)
		{
			it = v_npgo.erase(it);
		}
		else it++;
	}
	cout << "After " << v_npgo << endl;



}