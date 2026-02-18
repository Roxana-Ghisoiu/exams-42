#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

//1. class
class vect2
{
    private:
        int x, y;
    public:
    vect2(): x(0), y(0) {}
    vect2(int a, int b) : x(a), y(b) {}
    vect2(const vect2& other) : x(other.x), y(other.y) {}
    ~vect2(){}
    vect2& operator=(const vect2& other)
    {
        if(this !=&other)
        {
            x=other.x;
            y=other.y;
        }
        return *this;
    }
// access operator[]
int& operator[](int index)
{
    if (index == 0)
    return x;
return y;
}

const int& operator[](int index)const 
{
    if (index == 0)
    return x;
return y;
}
//3. math operator + - *, += -= *=,++ --(non int, int) ,unary

vect2 operator+(const vect2& other) const
{
    return vect2(x + other.x, y + other.y);
}

vect2 operator-(const vect2& other) const
{
    return vect2(x - other.x, y - other.y);
}

vect2 operator*(int k) const
{
    return vect2(x * k, y * k);
}

vect2& operator+=(const vect2& other)
{
    *this= *this + other;
    return *this;
}

vect2& operator-=(const vect2& other)
{
    *this= *this - other;
    return *this;
}

vect2& operator*=(int k)
{
    *this= *this * k;
    return *this;
}

vect2& operator++()
{
    x++;
    y++;
    return *this;
}

vect2& operator--()
{
    x--;
    y--;
    return *this;
}

vect2 operator++(int)
{
    vect2 temp(*this);
    ++*this;
    return temp;
}

vect2 operator--(int)
{
    vect2 temp(*this);
    --*this;
    return temp;
}

vect2 operator-() const
{
    return vect2(-x, -y);
}

//4. bool comparision ==, !=
bool operator==(const vect2& other)const
{
    return (x == other.x && y == other.y);
}

bool operator!=(const vect2& other) const
{
    return !(*this == other);
}

//5. outputt <<

friend std::ostream& operator<<(std::ostream& out, const vect2& v)
{
    out << "{" << v[0] << ", " << v[1] << "}";
    return out;
}
friend vect2 operator*(int k, const vect2& other)
{
    return vect2(k * other.x, k * other.y);
}
};
#endif