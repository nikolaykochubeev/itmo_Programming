#pragma once
#include "Point.h"

template<typename T = float>
class Trapezoid{
public:
    std::vector<Point<T>> trapezoid;
    T a, b, c, d;
    T area, perimeter;

    void Calculations(){
        d = sqrt(pow((trapezoid[1].getX() - trapezoid[0].getX()), 2) + pow((trapezoid[1].getY() - trapezoid[0].getY()), 2));
        a = sqrt(pow((trapezoid[2].getX() - trapezoid[1].getX()), 2) + pow((trapezoid[2].getY() - trapezoid[1].getY()), 2));
        c = sqrt(pow((trapezoid[2].getX() - trapezoid[3].getY()), 2) + pow((trapezoid[2].getY() - trapezoid[3].getY()), 2));
        b = sqrt(pow((trapezoid[3].getX() - trapezoid[0].getX()), 2) + pow((trapezoid[3].getY() - trapezoid[0].getY()), 2));
        FindArea();
        FindPerimeter();
    };

    explicit Trapezoid(const Point<T> arr[]): trapezoid(arr, arr + 4){
        Calculations();
    };

    explicit Trapezoid(std::vector<Point<T>> arr): trapezoid(move(arr)){
        Calculations();
    };

    void FindArea(){
        area = ((a+b)/2*sqrt(pow(c,2)-pow(((pow(b-a,2)+pow(c,2)-pow(d,2), 2))/2*(b-a), 2)));
    };

    void FindPerimeter(){
        perimeter = a + b + c + d;
    };
};