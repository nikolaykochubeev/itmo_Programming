#include <iostream>
#include "pugixml-1.11\src\pugixml.cpp"
#include <windows.h>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

template <class Key, class Value>
pair<Key, Value> findMaxValuePair(const unordered_map<Key, Value> &x){
    return *std::max_element(x.begin(), x.end(),[](const std::pair<Key, Value> &p1, const pair<Key, Value> &p2) {return p1.second < p2.second;});
}

void routes_with_the_most_stops(const pugi::xml_document& doc){
    unordered_map<string, int> m;
    unordered_map<string, pair<string, int>> m1;

    auto array = doc.child("dataset");
    for(auto &it : array){
        string temp = it.child("routes").text().as_string();
        char k = (temp.find(',') != string::npos) ? ',' : '.';
        vector<string> v;
        auto ss = istringstream(temp);
        string line;
        while(getline(ss, line, k))
            v.push_back(line);
        for (const auto& i: v)
            m[i+' '+it.child("type_of_vehicle").text().as_string()]++;
    }
    for (const auto& i: m){
        vector<string> v;
        auto ss = istringstream(i.first);
        string line;
        while(getline(ss, line, ' '))
            v.push_back(line);
        if (m1[v[1]].second < i.second){
            m1[v[1]].second = i.second;
            m1[v[1]].first = v[0];
        }
    }

    for (const auto& i: m1)
        cout << i.first << ' '<<i.second.first<<": "<<i.second.second << endl;
    cout << endl;
}

pair<basic_string<char>, int> street_with_maximum_number_of_stops(const pugi::xml_document& doc){
    unordered_map<string, int> m;
    auto array = doc.child("dataset");
    for(auto &it : array){
        if (it.child("location").text().empty()){
            if (it.child("the_official_name").text().empty())
                m[it.child("name_stopping").text().as_string()]++;
            else
                m[it.child("the_official_name").text().as_string()]++;
            continue;
        }
        m[it.child("location").text().as_string()]++;
    }
    cout << endl;
    return findMaxValuePair(m);
}

double rast(double x1, double x2, double y1, double y2){
    double l, y, x;
    x = x2-x1;
    y = y2-y1;
    l = sqrt(pow(fabs(x), 2)+pow(fabs(y), 2));
    return l;
}

void first_method(const unordered_map<string, vector<pair < double, double>>>& m1){
    unordered_map<string, pair<string, double>> maximum_route;
    for (const auto& i: m1){
        pair<string, string> v;
        auto ss = istringstream(i.first);
        getline(ss, v.first, ' ');
        getline(ss, v.second, ' ');

        for(auto j: i.second){
            for(auto qw: i.second){
                double R=rast(j.first, j.second, qw.first, qw.second);
                if(R > maximum_route[v.second].second){
                    maximum_route[v.second].second = R;
                    maximum_route[v.second].first = v.first;
                }
            }
        }
    }

    for (const auto& i: maximum_route)
        cout << i.first << ' ' << i.second.first << ' ' << i.second.second <<endl;
    cout << endl;
}

void second_method(const unordered_map<string, vector<pair < double, double>>>& m1){
    unordered_map<string, pair<string, double>> maximum_route;
    for (const auto& i: m1){
        pair<string, string> v;
        auto ss = istringstream(i.first);
        string line;
        getline(ss, v.first, ' ');
        getline(ss, v.second , ' ');
        double R;
        double k1 = i.second[0].first, k2 = i.second[0].second;
        for(auto qw: i.second){
            if (k1 != qw.first and k2!= qw.second){
                R+=rast(k1, k2, qw.first,qw.second);
                k1 = qw.first;
                k2 = qw.second;
            }
        }
        if(R > maximum_route[v.second].second){
            maximum_route[v.second].second = R;
            maximum_route[v.second].first = v.first;
        }
    }

    for (const auto& i: maximum_route)
        cout << i.first << ' ' << i.second.first << ' ' << i.second.second <<endl;
    cout << endl;
}

void longest_routes(const pugi::xml_document& doc){
    unordered_map<string, vector<pair<double, double>>> m1;
    auto array = doc.child("dataset");

    for(auto &it : array)
    {
        string temp = it.child("coordinates").text().as_string();
        pair<double, double> v;
        auto ss = istringstream(temp);
        string line;
        getline(ss, line, ',');
        v.first = stod(line);
        getline(ss, line, ',');
        v.second = stod(line);

        temp = it.child("routes").text().as_string();
        char k = (temp.find(',') != string::npos) ? ',' : '.';
        vector<string> v1;
        ss = istringstream(temp);

        while(getline(ss, line, k))
            v1.push_back(line);
        for (const auto& i: v1)
            m1[i+' ' + it.child("type_of_vehicle").text().as_string()].push_back(v);
    }
    first_method(m1);
    second_method(m1);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    pugi::xml_document doc;
    doc.load_file("data.xml");
    longest_routes(doc);
    routes_with_the_most_stops(doc);
    pair<basic_string<char>, int> street = street_with_maximum_number_of_stops(doc);
    cout << street.first << ' ' << street.second<< endl;

    return 0;
}