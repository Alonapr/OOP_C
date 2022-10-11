#include <iostream>
#include "LongInteger.h"
#include "Rational.h"
//#include <time.h>

using namespace std;
int choise;
int menu() {
	cout << "1: LongInteger" << endl;
	cout << "2: Rational" << endl;
	cin >> choise;
	return choise;
}

void class1() {
	cout << "	LongInteger" << endl;
	Long a, b;
	cout << "Input number 1: ";
	cin >> a;
	cout << "Input number 2: ";
	cin >> b;
	cout << a << " + " << b << " = " << a + b << endl;
	cout << a << " - " << b << " = " << a - b << endl;
	cout << a << " * " << b << " = " << a * b << endl;
	cout << a << " / " << b << " = " << a / b << endl;
	cout << "\nKaratsuba = " << Karatsuba(a, b) << endl;

	cout << "\nRabin-Miller Test:" << endl;
	if (a.RabinMiller())
		cout << "1st number is prime" << endl;
	else
		cout << "1st number is not Prime" << endl;
	if (b.RabinMiller())
		cout << "2nd number is Prime" << endl;
	else
		cout << "2nd number is not Prime" << endl;

	cout << "\nSolovay-Strassen Test:" << endl;
	if (a.SolovayStrassen())
		cout << "1st number is prime" << endl;
	else
		cout << "1st number is not Prime" << endl;
	if (b.SolovayStrassen())
		cout << "2nd number is Prime" << endl;
	else
		cout << "2nd number is not Prime" << endl;
	/*
	double t1 = (double)clock();
	a*b;
	double t2 = ((double)clock() - t1) / CLOCKS_PER_SEC;
	cout << "Time for *: " << t2 << endl;
	double t3 = (double)clock();
	Karatsuba(a, b);
	double t4 = ((double)clock() - t3) / CLOCKS_PER_SEC;
	cout << "Time for Karatsuba: " << t4 << endl;
	*/
}

void class2() {
	cout << "	Rational" << endl;
	Rat<long> c, d;
	cout << "Input number 1: ";
	cin >> c;
	cout << "Input number 2: ";
	cin >> d;
	c.norm();
	d.norm();
	cout << "\n1st number after reduction: " << c << endl;
	cout << "2nd number after reduction: " << d << endl;
	cout << c << " + " << d << " = " << c + d << endl;
	cout << c << " - " << d << " = " << c - d << endl;
	cout << c << " * " << d << " = " << c * d << endl;
	cout << c << " / " << d << " = " << c / d << endl;
}

int main() {
	int choise = -1;
	while (choise) {
		cout << "\nChoose class:" << endl;
		choise = menu();
		if (!choise) break;
		switch (choise) {
		case 1: class1();
			break;
		case 2: class2();
			break;
		}
	}
	return 0;
}