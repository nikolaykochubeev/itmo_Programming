#pragma once
#include "Broken.h"

template<class T = float>
class LockBroken: public Broken<T>{
public:
    LockBroken(const Point<T> m[], T k):Broken<T>(m,k){};
    explicit LockBroken(const std::vector<Point<T>> &m):Broken<T>(m){
        Broken<T>::Calculations();
    };

    explicit LockBroken(const Broken<T> &p):Broken<T>(p){
        Broken<T>::Calculations();
    };

    T FindLength() override{
        T t = Broken<T>::FindLength();
        t += Broken<T>::line_length(Broken<T>::v[0], Broken<T>::v[Broken<T>::v.size() - 1]);
        return t;
    };

    ~LockBroken() override = default;
};