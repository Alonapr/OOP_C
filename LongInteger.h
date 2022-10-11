#pragma once
#include<iostream>
#include<vector>

using namespace std;

class Long{
private:
	static const int BASE = 10;
	int sign;
	vector<int> digits;
	void normalize();
	Long(int sign, const vector<int>& digits);

	static Long random(int length);

public:
	Long();
	Long(const Long& oth);
	Long(long long num);
	Long(const string& str);

	Long& operator=(const Long& oth);
	friend bool operator==(const Long& a, const Long& b);
	friend bool operator!=(const Long& a, const Long& b);
	friend bool operator>=(const Long& a, const Long& b);
	
	friend Long operator-(const Long& x);

	friend Long operator+(const Long& a, const Long& b);
	friend Long operator-(const Long& a, const Long& b);
	friend Long operator*(const Long& a, const Long& b);
	friend Long operator/(const Long& a, const Long& b);
	friend Long Karatsuba(const Long& a, const Long& b);

	friend Long operator%(const Long& a, const Long& b);
	friend Long pow(Long a, Long b, const Long& mod);
	bool RabinMiller(int t = 20) const;
	bool SolovayStrassen(int t = 20) const;

	friend istream& operator>>(istream& in, Long& x);
	friend ostream& operator<<(ostream& out, const Long& x);
};