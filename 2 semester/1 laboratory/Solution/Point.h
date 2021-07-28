#pragma once
#include <vector>
#include <cmath>
#include <iostream>

template<typename T = float>
class Point{
public:
    T x = 0, y = 0;
    Point(): x(0), y(0) {};
    Point(T _x, T _y): x(_x),y(_y){};
    Point(const Point &t): x(t.getX()), y(t.getY()){};

    void setX(T _x){
        x = _x;
    };

    void setY(T _y){
        y = _y;
    };

    [[nodiscard]] T getX() const{
        return x;
    };

    [[nodiscard]] T getY() const{
        return y;
    };

    Point& operator=(const Point &t){
        x=t.getX();
        y=t.getY();
        return *this;
    };

    Point operator+(const Point &a) const{
        Point t;
        t.setX(x+a.getX());
        t.setY(y+a.getY());
        return t;
    };
    ~Point()= default;
};
