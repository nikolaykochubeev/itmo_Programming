#pragma once
#include "Point.h"

template<typename T = float>
class Broken{
protected:
    static T line_length(Point<T> &a, Point<T> &b){
        return sqrt(pow((a.getX()-b.getX()),2)+pow((a.getY()-b.getY()),2));
    }
public:
    std::vector<Point<T>> v;
    Broken(const Point<T> m[],int k) : v(m, m + k){};
    explicit Broken(std::vector<Point<T>> m): v(std::move(m)){
        Calculations();
    };
    Broken(const Broken &p)= default;;
    virtual T FindLength(){
        T t=0;
        for(int i=0;i<v.size()-1;i++)
            t+= line_length(v[i], v[i + 1]);
        return t;
    };

    void Calculations(){
        FindLength();
    };

    virtual ~Broken()= default;
};