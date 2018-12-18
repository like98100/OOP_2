
#include <cmath>
class Vector2
{
	float x;
	float y;
public:
	Vector2(float x = 0.0f, float y = 0.0f): x(x), y(y) {}

	double magnitude()
	{
		return sqrt(x*x + y*y);
	}

	double sqrMagnitude()
	{
		return x*x + y*y;
	}

	static Vector2 one;
	static Vector2 zero;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;
};

//Vector2 Vector2::one(1.0f, 1.0f);
//Vector2 Vector2::zero(0.0f, 0.0f);
//Vector2 Vector2::up(0.0f, 1.0f);
//Vector2 Vector2::down(0.0f, -1.0f);
//Vector2 Vector2::left(-1.0f, 0.0f);
//Vector2 Vector2::right(1.0f, 0.0f);