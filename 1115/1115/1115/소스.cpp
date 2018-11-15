#include <iostream>

using namespace std;

class Complex
{
    int real;
    int imaginary;
    public:
    Complex(int r = 0, int i = 0) : real(r), imaginary(i) {}

    //1
    //void add(const Complex& c1, const Complex& c2)
    //{
    //    this->real = c1.real + c2.real;
    //    this->imaginary = c1.imaginary + c2.imaginary;
    //}

    //3
    //Complex add(const Complex& c)
    //{
    //    //Complex temp;
    //    //temp.real = this->real + c.real;
    //    //temp.imaginary = this->imaginary + c.imaginary;

    //    //return temp;
    //    return Complex(this->real + c.real, this->imaginary + c.imaginary);
    //}

    //3-1, 4
    Complex operator+(const Complex& c)
    {

        return Complex(this->real + c.real, this->imaginary + c.imaginary);
    }

    void printNum() { cout << "(" << real << " + " << imaginary << "i)" << endl; }

    //friend Complex add(const Complex& c1, const Complex& c2);
    //friend Complex operator+(const Complex& c1, const Complex& c2);

};

//2
//Complex add(const Complex& c1, const Complex& c2)
//{
//    Complex temp;
//    temp.real = c1.real + c2.real;
//    temp.imaginary = c1.imaginary + c2.imaginary;
//    return temp;
//}

//2-1, 4
//Complex operator+(const Complex& c1, const Complex& c2)
//{
//    Complex temp;
//    temp.real = c1.real + c2.real;
//    temp.imaginary = c1.imaginary + c2.imaginary;
//    return temp;
//}

int main()
{
    Complex a{1, 2};
    Complex b(3, 4);
    Complex c;
    Complex d;
    a.printNum();

    //c.add(a, b);
    //c = add(a, b);    // 값을 집어넣는 게 아니라 복사(잘라내기가 아닌 복붙) // temp라는 공간을 만든 후 반환한 결과값을 그 공간에 복사한다.
    // 할당 연산자 : 같은 값을 할당 / 복사 연산자 : 생성자에 필요한 것을 복사

    //c = a.add(b);
    //c = a.operator+(b);

    //operator+로 이름을 바꿨더니 실제 연산자 + 에 영향이 끼침
    c = a + b;  //(멤버 vs 전역)비주얼 기준 멤버함수 우선 기준으로 실행된다
    c.printNum();

    d = a + b + c;
    //== d = ((a.operator+(b)).operator+(c));
    d.printNum();
    return 0;
}