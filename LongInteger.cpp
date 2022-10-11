#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cassert>
#include"LongInteger.h"

void Long::normalize() {
	while (digits.size() > 1 && digits.back() == 0)
		digits.pop_back();
	if (digits.empty())
		digits.push_back(0);
	if (digits.size() == 1 && digits.back() == 0)
		sign = 1;
}

Long::Long(int sign, const vector<int>& digits) :sign(sign), digits(digits) {
	normalize();
}

Long::Long() : sign(1), digits{ 0 } {}

Long::Long(const Long& oth) : sign(oth.sign), digits(oth.digits) {}

Long::Long(long long num) {
	if (num >= 0)
		sign = 1;
	else
	{
		sign = -1;
		num = -num;
	}
	while (num > 0)
	{
		digits.push_back(num % BASE);
		num /= BASE;
	}
	normalize();
}

Long::Long(const string& str) {
	sign = 1;
	for (int i = (int)str.size() - 1; i >= 0; i--)
		if (str[i] == '-')
			sign = -1;
		else
			digits.push_back(str[i] - '0');
	normalize();
}

Long& Long::operator=(const Long& oth) {
	sign = oth.sign;
	digits = oth.digits;
	return*this;
}

bool operator==(const Long& a, const Long& b) {
	return a.sign == b.sign && a.digits == b.digits;
}

bool operator!=(const Long& a, const Long& b) {
	return !(a == b);
}

bool operator>=(const Long& a, const Long& b) {
	if (a.sign == 1)
		if (b.sign == 1)
			if (a.digits.size() > b.digits.size())
				return true;
			else if (a.digits.size() < b.digits.size())
				return false;
			else
			{
				for (int i = a.digits.size() - 1; i >= 0; i--)
					if (a.digits[i] > b.digits[i])
						return true;
					else if (a.digits[i] < b.digits[i])
						return false;
				return true;
			}
		else
			return true;
	else
		if (b.sign == 1)
			return false;
		else
			return (-b) >= (-a);
}

Long operator-(const Long& x) {
	return { -x.sign,x.digits };
}

Long operator+(const Long& a, const Long& b) {
	if (a.sign == 1)
		if (b.sign == 1) {
			vector<int> result;
			for (int i = 0, carry = 0; i < max(a.digits.size(), b.digits.size()) || carry; i++)
			{
				int cur = (i < a.digits.size() ? a.digits[i] : 0) + (i < b.digits.size() ? b.digits[i] : 0) + carry;
				result.push_back(cur % 10);
				carry = cur / 10;
			}
			return { 1,result };
		}
		else
			return a - (-b);
	else
		if (b.sign == 1)
			return b - (-a);
		else
			return -((-a) + (-b));
}

Long operator-(const Long& a, const Long& b) {
	if (a.sign == 1)
		if (b.sign == 1)
			if (a >= b)
			{
				vector<int> result;
				for (int i = 0, carry = 0; i < max(a.digits.size(), b.digits.size()); i++)
				{
					int cur = (i < a.digits.size() ? a.digits[i] : 0) - (i < b.digits.size() ? b.digits[i] : 0) - carry;
					if (cur >= 0)
					{
						result.push_back(cur);
						carry = 0;
					}
					else
					{
						result.push_back(cur + 10);
						carry = 1;
					}
				}
				return { 1,result };
			}
			else
				return -(b - a);
		else
			return a + (-b);
	else
		if (b.sign == 1)
			return -((-a) + b);
		else
			return (-b) - (-a);
}

Long operator*(const Long& a, const Long& b) {
	vector<int> result(a.digits.size() + b.digits.size());
	for (int i = 0; i < a.digits.size(); i++)
		for (int j = 0, carry = 0; j < b.digits.size() || carry; j++)
		{
			int cur = result[i + j] + a.digits[i] * (j < b.digits.size() ? b.digits[j] : 0) + carry;
			result[i + j] = cur % Long::BASE;
			carry = cur / Long::BASE;
		}
	return { a.sign * b.sign,result };
}

Long operator/(const Long& a, const Long& b) {
	if (b.sign == -1)
		return -(a / (-b));
	if (a.digits.size() < b.digits.size())
		return {};
	vector<int> result(a.digits.size() - b.digits.size() + 1);
	Long r(1, vector<int>(a.digits.end() - b.digits.size() + 1, a.digits.end()));
	for (int i = a.digits.size() - b.digits.size(); i >= 0; i--)
	{
		r = r * 10 + a.digits[i];
		int cur = 0;
		while (cur + 1 < Long::BASE && r >= b * (cur + 1))
			cur++;
		result[i] = cur;
		r = r - b * cur;
	}
	return { a.sign,result };
}

Long Karatsuba(const Long& a, const Long& b) {
	if (a.sign == -1)
		return -Karatsuba((-a), b);
	if (b.sign == -1)
		return -Karatsuba(a,(-b));
	if (a.digits.size() < 2 || b.digits.size() < 2)
		return a * b;
	int i = (a.digits.size() + b.digits.size()) / 4;
	if (i >= a.digits.size())
		i = a.digits.size() / 2;
	if (i >= b.digits.size())
		i = b.digits.size() / 2;
	Long x0;
	x0.digits.insert(x0.digits.begin(), a.digits.begin() + i, a.digits.end());
	Long x1;
	x1.digits.insert(x1.digits.begin(), a.digits.begin(), a.digits.begin() + i);
	Long y0;
	y0.digits.insert(y0.digits.begin(), b.digits.begin() + i, b.digits.end());
	Long y1;
	y1.digits.insert(y1.digits.begin(), b.digits.begin(), b.digits.begin() + i);
	Long c0 = x0 * y0;
	Long c1 = x1 * y1;
	Long c2 = (x0 + x1)*(y0 + y1) - c0 - c1;
	c2.digits.insert(c2.digits.begin(), i, 0);
	c0.digits.insert(c0.digits.begin(), i + i, 0);
	return c0 + c1 + c2;
}

Long operator%(const Long& a, const Long& b) {
	Long result = a - (a / b) * b;
	if (result.sign == -1) 
		result = result + b;
	return result;
}

Long pow(Long a, Long b, const Long& mod) {
	assert(b.sign == 1);
	Long result = 1;
	while (b != 0)
	{
		if (b.digits.front() % 2 == 1)
			result = result * a % mod;
		a = a * a % mod;
		b = b / 2;
	}
	return result;
}

Long Long::random(int length) {
	vector<int> result(length);
	for (int i = 0; i < length; i++)
		result[i] = rand() % BASE;
	return { 1,result };
}

bool Long::RabinMiller(int t) const {
	if (sign == -1)
		return false;
	if (*this == 2 || *this == 3)
		return true;
	if (digits.front() % 2 == 0 || *this == 1)
		return false;
	Long r = *this - 1;
	int s = 0;
	while (r.digits.front() % 2 == 0)
		s++,
		r = r / 2;
	for (int i = 1; i <= t; i++)
	{
		Long a = random(digits.size()) % (*this - 3) + 2;
		Long y = pow(a, r, *this);
		if (y != 1 && y != *this - 1)
		{
			int j = 1;
			while (j <= s - 1 && y != *this - 1)
			{
				y = y * y % *this;
				if (y == 1)
					return false;
				j++;
			}
			if (y != *this - 1)
				return false;
		}
	}
	return true;
}

bool Long::SolovayStrassen(int t) const {
	if (sign == -1)
		return false;
	if (*this == 2 || *this == 3)
		return true;
	if (digits.front() % 2 == 0 || *this == 1)
		return false;
	for (int i = 1; i <= t; i++)
	{
		Long a = random(digits.size()) % (*this - 3) + 2;
		Long k = pow(a, (*this - 1) / 2, *this);
		if (k != 1 && k != *this - 1)
			return false;
		Long j = pow(a, (*this - 1) / 2, *this);
		if (k != j % *this)
			return false;
	}
	return true;
}

istream& operator>>(istream& in, Long& x) {
	string str;
	in >> str;
	x = str;
	return in;
}

ostream& operator<<(ostream& out, const Long& x) {
	if (x.sign == -1)
		out << "-";
	for (int i = x.digits.size() - 1; i >= 0; i--)
		out << x.digits[i];
	return out;
}