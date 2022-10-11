#include <iostream>
using namespace std;

template <class T> class Rat;
template <class T> istream& operator>>(istream& stream_in, Rat<T> &rvalue);
template <class T> ostream& operator<<(ostream& stream_out, const Rat<T> &rvalue);

template <class T>
class Rat {
	T ch, zn;
public:
	friend istream& operator>> <T> (istream& stream_in, Rat &rvalue);
	friend ostream& operator<< <T> (ostream& stream_out, const Rat &rvalue);
	T nod(T, T);
	T abs(T);
	Rat(int = 0, int = 1);
	void norm();
	Rat<T> operator+(const Rat<T> &rvalue) const;
	Rat<T> operator-(const Rat<T> &rvalue) const;
	Rat<T> operator*(const Rat<T> &rvalue) const;
	Rat<T> operator/(const Rat<T> &rvalue) const;
};

template <class T> T Rat <T>::abs(T x) {
	if (x < 0)
		return (-1)*x;
	return x;
}

template <class T> T Rat <T>::nod(T x, T y) {
	if (x == 0 || y == 0)
		return 1;
	while (x != y)
		if (x > y)
			x = x - y;
		else
			y = y - x;
	return x;
}

template <class T> Rat <T>::Rat(int x, int y) {
	if (!y || !x) {
		ch = 0;
		zn = 1;
	}
	ch = x;
	zn = y;
	this->norm();
}

template <class T> void Rat <T>::norm() {
	int sign = 1;
	if (ch*zn < 0)
		sign = (-1);
	ch = abs(ch);
	zn = abs(zn);
	T b = nod(ch, zn);
	if (ch == 0 || zn == 0)
		zn = 1;
	if (b == 1)
		return;
	ch = (ch / b)*sign;
	zn = zn / b;
}

template <class T> Rat<T> Rat<T>::operator+(const Rat<T> &rvalue) const {
	Rat<T> temp;
	temp.ch = rvalue.zn*this->ch + rvalue.ch*this->zn;
	temp.zn = this->zn * rvalue.zn;
	temp.norm();
	return temp;
}

template <class T> Rat<T> Rat<T>::operator-(const Rat<T> &rvalue) const {
	Rat<T> temp;
	temp.ch = rvalue.zn*this->ch - rvalue.ch*this->zn;
	temp.zn = this->zn * rvalue.zn;
	temp.norm();
	return temp;
}

template <class T> Rat<T> Rat<T>::operator*(const Rat<T> &rvalue) const {
	Rat<T> temp;
	temp.ch = this->ch * rvalue.ch;
	temp.zn = this->zn * rvalue.zn;
	temp.norm();
	return temp;
}

template <class T> Rat<T> Rat<T>::operator/(const Rat<T> &rvalue) const {
	Rat<T> temp;
	temp.ch = this->ch* rvalue.zn;
	temp.zn = this->zn * rvalue.ch;
	temp.norm();
	return temp;
}

template <class T> istream& operator>>(istream& stream_in, Rat<T> &rvalue) {
	stream_in >> rvalue.ch;
	stream_in.ignore();
	stream_in >> rvalue.zn;
	return stream_in;
}

template <class T> ostream& operator<<(ostream& stream_out, const Rat<T> &rvalue) {
	stream_out << rvalue.ch << "/" << rvalue.zn;
	return stream_out;
}