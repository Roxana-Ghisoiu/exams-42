#include "bigint.hpp"

/* ================= CONSTRUCTORI ================= */

bigint::bigint()
{
	big.push_back(0);
}

bigint::bigint(const bigint& other)
{
	big = other.big;
}

bigint::bigint(unsigned long long nb)
{
	if (nb == 0)
		big.push_back(0);
	while (nb)
	{
		big.push_back(nb % 10);
		nb /= 10;
	}
}

bigint::~bigint()
{
}

/* ================= ADD ================= */

bigint& bigint::operator+=(const bigint& other)
{
	size_t max = big.size() > other.big.size() ? big.size() : other.big.size();
	int carry = 0;

	if (big.size() < max)
		big.resize(max, 0);

	for (size_t i = 0; i < max; i++)
	{
		int a = big[i];
		int b = (i < other.big.size()) ? other.big[i] : 0;
		int sum = a + b + carry;

		big[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry)
		big.push_back(carry);

	return *this;
}

bigint bigint::operator+(const bigint& other) const
{
	bigint tmp(*this);
	tmp += other;
	return tmp;
}

/* ================= INCREMENT ================= */

bigint& bigint::operator++()
{
	*this += 1;
	return *this;
}

bigint bigint::operator++(int)
{
	bigint tmp(*this);
	*this += 1;
	return tmp;
}

/* ================= SHIFT ================= */

bigint bigint::operator<<(unsigned int shift) const
{
	bigint tmp(*this);
	for (; shift; shift--)
		tmp.big.insert(tmp.big.begin(), 0);
	return tmp;
}

bigint& bigint::operator>>=(const bigint& other)
{
	unsigned int shift = 0;

	for (int i = other.big.size() - 1; i >= 0; i--)
		shift = shift * 10 + other.big[i];

	if (shift >= big.size())
	{
		big.clear();
		big.push_back(0);
	}
	else
		big.erase(big.begin(), big.begin() + shift);

	return *this;
}

bigint& bigint::operator<<=(unsigned int shift)
{
	for (; shift; shift--)
		big.insert(big.begin(), 0);
	return *this;
}

/* ================= COMPARISON ================= */

bool bigint::operator>=(const bigint& other) const
{
	return !(*this < other);
}

bool bigint::operator>(const bigint& other) const
{
	if (big.size() != other.big.size())
		return big.size() > other.big.size();

	for (int i = big.size() - 1; i >= 0; i--)
		if (big[i] != other.big[i])
			return big[i] > other.big[i];

	return false;
}

bool bigint::operator<(const bigint& other) const
{
	return other > *this;
}

bool bigint::operator==(const bigint& other) const
{
	return big == other.big;
}

bool bigint::operator!=(const bigint& other) const
{
	return !(*this == other);
}

bool bigint::operator<=(const bigint& other) const
{
	return !(*this > other);
}

/* ================= OUTPUT ================= */

std::ostream& operator<<(std::ostream& out, const bigint& value)
{
	for (int i = value.big.size() - 1; i >= 0; i--)
		out << value.big[i];
	return out;
}