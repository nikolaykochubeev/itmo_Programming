#pragma once
#include <iostream>
#include <unordered_map>

class Polynomial{
public:
    std::unordered_map<float, float> map_v;
    explicit Polynomial(std::unordered_map<float, float> m): map_v(std::move(m)){};
    Polynomial(const std::unordered_map<float, float> &t) = default;;
    Polynomial()=default;;
    Polynomial& operator=(const Polynomial &t)= default;;
    bool operator==(const Polynomial&t) const{
        return (this->map_v == t.map_v);
    };
    bool operator!=(const Polynomial&t) const{
        return !(t == *this);
    };
    Polynomial operator+(const Polynomial&t) {
        Polynomial y(*this);
        return y+=t;
    }
    Polynomial operator-(){
        Polynomial e(*this);
        for (auto & item : e.map_v)
            item.second = -item.second;
        return e;
    };
    Polynomial operator-(Polynomial&t) const{
        return  -t + *this;
    }
    Polynomial& operator+=(const Polynomial&t) {
        for (auto i : t.map_v)
            this->map_v[i.first] = this->map_v.find(i.first)->second + i.second;
        return *this;
    }
    Polynomial& operator-=(Polynomial&t){
        return *this += -t;
    };
    Polynomial operator*(const float t) {
        Polynomial y(*this);
        return y*=t;
    }
    Polynomial operator/(const float t) {
        Polynomial y(*this);
        return y/=t;
    }
    Polynomial& operator*=(const float t) {
        for (auto & i : this->map_v)
            i.second *= t;
        return *this;
    }
    Polynomial& operator/=(const float t){
        for (auto & i : this->map_v)
            i.second /= t;
        return *this;
    };
    Polynomial operator*=(const Polynomial &t) {
        for (auto i: this->map_v)
            for (auto j: this->map_v)
                this->map_v[i.first+j.first] += i.second*j.second;
        return *this;
    }
    Polynomial operator*(const Polynomial &t){
        Polynomial e(*this);
        return e*=t;
    };
    float& operator[](float t){
        return this->map_v.find(t)->second;
    }
};
std::ostream& operator<< (std::ostream &o,const Polynomial& a){
    for (auto i: a.map_v)
        std::cout << i.first << ' ' << i.second << '\n';
    return o;
}
std::istream& operator>> (std::istream &in, Polynomial &a){
    std::cout << "Please enter pairs of an integers {power, coefficient} (to quit press q):\n";
    float i, k;
    while(std::cin >> i && std::cin>>k)
        a.map_v.insert({i,k});
    return in;
}