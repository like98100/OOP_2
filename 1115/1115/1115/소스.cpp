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
    //c = add(a, b);    // ���� ����ִ� �� �ƴ϶� ����(�߶󳻱Ⱑ �ƴ� ����) // temp��� ������ ���� �� ��ȯ�� ������� �� ������ �����Ѵ�.
    // �Ҵ� ������ : ���� ���� �Ҵ� / ���� ������ : �����ڿ� �ʿ��� ���� ����

    //c = a.add(b);
    //c = a.operator+(b);

    //operator+�� �̸��� �ٲ���� ���� ������ + �� ������ ��ħ
    c = a + b;  //(��� vs ����)���־� ���� ����Լ� �켱 �������� ����ȴ�
    c.printNum();

    d = a + b + c;
    //== d = ((a.operator+(b)).operator+(c));
    d.printNum();
    return 0;
}