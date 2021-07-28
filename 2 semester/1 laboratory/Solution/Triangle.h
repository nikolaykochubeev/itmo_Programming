#pragma once
#include "Polygon.h"

template<typename T = float>
class Triangle: public Polygon<T>{
private:
    bool InvarianceCheck() override {
        a = line_length(Polygon<T>::v[0], Polygon<T>::v[1]);
        b = line_length(Polygon<T>::v[0], Polygon<T>::v[2]);
        c = line_length(Polygon<T>::v[1], Polygon<T>::v[2]);
        if ((a + b > c && a + c > b && b + c > a) || a * b * c == 0)
            return false;
        return true;
    }
public:
    T a,b,c;

    void Calculations() override{
        if (InvarianceCheck() == false)
            throw std::logic_error("This is an irregular triangle");
        FindPerimeter();
        FindArea();
    }

    explicit Triangle(const std::vector<Point<T>> &m): Polygon<T>(m){
        Calculations();
    }

    Triangle(const Triangle &m): Polygon<T>(m) {
        Calculations();
    }

    void FindArea() override{
        T p = ((a + b + c)/3);
        Polygon<T>::area = std::sqrt(((p - a) * (p - b) * ( p - c) * p));
    }

    void FindPerimeter() override{
        Polygon<T>::perimeter = a+b+c;
    }
};
