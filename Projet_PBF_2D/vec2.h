#ifndef Vec2_H
#define Vec2_H

#include <cmath>

class Vec2
{
public:

    Vec2() : e{0.0f, 0.0f} {}
    Vec2(float e1, float e2) : e{e1,e2} {};

    float operator[](int i) const {return e[i];}
    float operator[](int i){return e[i];}

    // Opérateurs d'assignation
    Vec2& operator+=(const Vec2& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        return *this;
    }

    Vec2& operator-=(const Vec2& v)
    {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        return *this;
    }

    Vec2& operator*=(float t)
    {
        e[0] *= t;
        e[1] *= t;
        return *this;
    }

private:
    float e[2];
};

inline Vec2 operator+(const Vec2& v1, const Vec2& v2)
{
    return Vec2(v1[0]+v2[0],v1[1]+v2[1]);
}

inline Vec2 operator*(const Vec2& v, const float t)
{
    return Vec2(v[0]*t,v[1]*t);
}

inline Vec2 operator*(const float t, const Vec2& v)
{
    return Vec2(v[0]*t,v[1]*t);
}

inline Vec2 operator-(const Vec2& v1, const Vec2& v2)
{
    return Vec2(v1[0]-v2[0],v1[1]-v2[1]);
}

inline Vec2 operator-(const Vec2& v)
{
    return Vec2(-v[0],-v[1]);
}

inline Vec2 operator/(const Vec2& v, float t)
{
    return v * (1.0f/t);
}

inline float dot(const Vec2& v1, const Vec2& v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1];
}

inline float squaredLength(const Vec2& v)
{
    return v[0]*v[0]+v[1]*v[1];
}

inline float norm(const Vec2& v)
{
    return std::sqrt(squaredLength(v));
}

inline bool operator==(const Vec2& v1, const Vec2& v2)
{
    if (v1[0]==v2[0] and v1[1]==v2[1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif // Vec2_H
