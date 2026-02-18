#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include <vector>
#include <stddef.h>

typedef std::vector <int> bigV; // vector<int>

//1. class
class bigint
{
    private:
        bigV big;
    public:
    bigint(){big.push_back(0);} // default constructor
    bigint(const bigint& other) {big=other.big;} // copy constructor 
    bigint(unsigned long long nb) // long nb consttructor
    {
        if (nb == 0)
            big.push_back(0);
        while(nb)
        {
            big.push_back(nb % 10);
            nb /=10;
        }
    }

    ~ bigint (){}

//2.adition

bigint& operator+=(const bigint& other)
{
    size_t i = 0;
    int c = 0;
    while(i < big.size() || i < other.big.size() || c)
    {
        int sum = c;

        if(i < big.size())
            sum+=big[i];
        else
            big.push_back(0);

        if (i < other.big.size())
            sum+=other.big[i];
        
        big[i]= sum % 10;
        c = sum / 10;
        i++;
    }
    return *this;
}

bigint operator+(const bigint& other) const
{
    bigint temp(*this);
    temp+= other;
    return temp;
}

//3. increment

bigint& operator++()
{
    *this+=1;
    return *this;
}

bigint operator++(int)
{
    bigint temp(*this);
    *this +=1;
    return temp;
}

//4.shifts
bigint operator<<(unsigned int shift) const
{
    bigint temp(*this);
    for(; shift; shift--)
        temp.big.insert(temp.big.begin(), 0);
    return temp;
}

bigint& operator<<=(unsigned int shift)
{
    for(; shift; shift--)
        big.insert(big.begin(), 0);
    return *this;
}

bigint& operator>>=(const bigint& other)
{
    unsigned int shift = 0;
    for(int i = other.big.size() -1; i >= 0; i--)
        shift = shift * 10 + other.big[i];
    
    if(shift >=big.size())
        {
            big.clear();
            big.push_back(0);
        }
        else
            big.erase(big.begin(), big.begin() + shift);
    
    return *this;
}

//5. bool comparision

bool operator>(const bigint& other) const
{
    if(big.size() != other.big.size())
        return big.size() > other.big.size();
    
    for(int i = big.size() - 1; i >= 0; i--)
        if(big[i] != other.big[i])
            return big[i] > other.big[i];

    return false;
}
bool operator<(const bigint& other)const{ return other > *this;}
bool operator==(const bigint& other) const{ return big == other.big;}
bool operator!=(const bigint& other)const{return !(*this == other);}
bool operator<=(const bigint& other)const{return !(*this > other);}
bool operator>=(const bigint& other)const{return !(*this < other);}

//6.Output

friend  std::ostream& operator<<(std::ostream& out, const bigint& value)
{
    for(int i = value.big.size() - 1; i >= 0; i--)
        out << value.big[i];
    return out;
}
};
#endif
