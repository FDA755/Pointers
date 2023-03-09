#include<iostream>
using namespace std;

//#define POINTER_START

void Exchange(int* a, int* b);


void main()
{
	setlocale(LC_ALL, "");

#ifdef POINTER_START
	int a = 2;
	int* pa = &a;
	cout << a <<endl;
	cout << &a << endl;
	cout << pa << endl;
	cout << *pa << endl;

	int* pb;
	int b = 3;
	pb = &b;
	cout << *pb << endl;
#endif
	int  a = 2, b = 3;
	cout << a << "\t" << b << endl;
	Exchange(&a, &b);
	cout << a << "\t" << b << endl;

}

void Exchange(int* a, int* b)
{
	int buffer = *a;
	*a = *b;
	*b = buffer;
}