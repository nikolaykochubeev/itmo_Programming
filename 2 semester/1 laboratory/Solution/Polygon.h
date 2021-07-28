#pragma once
#include "Point.h"

template<typename T = float>
class Polygon{
private:
    size_t number_of_corners;

    static int ConvexCheckFunc(const Point<T>& a, const Point<T>& b){
        return (int) (a.x * b.y - a.y * b.x);
    }

    static bool positive(int value){
        return value>=0;
    }

    static bool negative(int value){
        return value<=0;
    }

protected:
    static T line_length(Point<T> &a, Point<T> &b){
        return sqrt(pow((a.getX()-b.getX()),2)+pow((a.getY()-b.getY()),2));
    }

public:
    std::vector <Point<T>> v;
    T area, perimeter;
    explicit Polygon(const std::vector<Point<T>> &m):v(m), number_of_corners(m.size()){
        Calculations();
    };

    Polygon(const Polygon &p):v(p.v), number_of_corners(p.number_of_corners), area(p.area), perimeter(p.perimeter){};

    Polygon(const Point<T> list[], int corners): number_of_corners(corners), v(list, list+corners){
        Calculations();
    }

    virtual void FindArea(){
        for (size_t i = 0; i < v.size(); ++i)
        {
            if(i != v.size() - 1)
                area += (v[i].getX() * v[i + 1].getY() - v[i].getY() * v[i + 1].getX());
            else
                area += (v[i].getX() * v[0].getY() - v[i].getY() * v[0].getX());
        }
        area = std::abs(area)/2;
    }

    virtual void FindPerimeter(){
        for (size_t i = 0; i < v.size(); ++i) {
            perimeter+= sqrt(pow(v[i].getX() - v[i + 1].getX(), 2) + pow(v[i].getY() - v[i + 1].getY(), 2));
        }
    }

    virtual bool InvarianceCheck(){
        Point<T> prev, next;
        prev.x=v[number_of_corners-1].x-v[number_of_corners-2].x;
        prev.y=v[number_of_corners-1].y-v[number_of_corners-2].y;

        next.x=v[0].x-v[number_of_corners-1].x;
        next.y=v[0].y-v[number_of_corners-1].y;

        bool (*sign)(int), result=true;
        sign= (ConvexCheckFunc(prev, next) >= 0) ? positive : negative;

        for (int i=1; i<number_of_corners && result; ++i){
            prev=next;
            next.x=v[i].x-v[i-1].x;
            next.y=v[i].y-v[i-1].y;
            result=sign(ConvexCheckFunc(prev, next));
        }
        return result;
    }

    virtual void Calculations(){
        if (!InvarianceCheck())
            throw std::logic_error("not convex polygon");
        FindPerimeter();
        FindArea();
    }
};
