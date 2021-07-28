#include "Polygon.h"

template<typename T = float>
class RegularPolygon: public Polygon<T> {
private:
    bool InvarianceCheck() override{
        std::vector<T> l;

        for (int i = 0; i < Polygon<T>::v.size(); i++){
            l.push_back(std::sqrt(
                    (Polygon<T>::v[i].getX() - Polygon<T>::v[i + 1].getX())
                    * (Polygon<T>::v[i].getX() - Polygon<T>::v[i + 1].getX())
                    + (Polygon<T>::v[i].getY() - Polygon<T>::v[i + 1].getY())
                      * (Polygon<T>::v[i].getY() - Polygon<T>::v[i + 1].getY())
            ));
            if((l[i] != l[i - 1] or l[i]*l[i-1] == 0) and i!=0)
                return false;
        }
        return true;
    }
public:
    void Calculations() override{
        if (!InvarianceCheck())
            throw std::logic_error("It isn't a regular polygon");
        Polygon<T>::FindPerimeter();
        Polygon<T>::FindArea();
    }
    explicit RegularPolygon(const std::vector<Point<T>> &m): Polygon<T>(m){
        Calculations();
    }
    RegularPolygon(const RegularPolygon &m)= default;;
};