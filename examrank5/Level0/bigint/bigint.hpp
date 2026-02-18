#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>

typedef std::vector<int> bigV;

class bigint{
	public:
		bigint();
		bigint(const bigint&);
		bigint(unsigned long long);
		~bigint();

		bigint& operator+=(const bigint&);
		bigint 	operator+(const bigint&)const;

		bigint& operator++();
		bigint operator++(int);

		bigint 	operator<<(unsigned int)const;
		bigint& operator>>=(const bigint &);
		bigint& operator<<=(unsigned int);

		bool 	operator>=(const bigint&)const;
		bool 	operator>(const bigint&)const;
		bool 	operator<(const bigint&)const;
		bool 	operator==(const bigint&)const;
		bool 	operator!=(const bigint&)const;
		bool 	operator<=(const bigint&)const;
	
	friend std::ostream& operator<<(std::ostream&, const bigint&);

	private:
		bigV big;
} ;

#endif