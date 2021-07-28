#pragma once

template<class Iterator, class Predicate>
bool all_of(Iterator begin, Iterator end, Predicate predicate){
    for(; begin != end; begin++)
        if(!predicate(*begin))
            return false;
    return true;
}

template<class Iterator, class Predicate>
bool any_of(Iterator begin, Iterator end, Predicate predicate){
    for(; begin != end; begin++)
        if(predicate(*begin))
            return true;
    return false;
}

template<class Iterator, class Predicate>
bool none_of(Iterator begin, Iterator end, Predicate predicate){
    for(; begin != end; begin++)
        if(predicate(*begin))
            return false;
    return true;
}

template<class Iterator, class Predicate>
bool one_of(Iterator begin, Iterator end, Predicate predicate) {
    bool k = false;
    for (; begin != end; begin++){
        if (predicate(*begin) and !k)
            k = true;
        else if (predicate(*begin))
            return false;
    }
    return k;
}

template<class Iterator, class Predicate>
bool is_sorted(Iterator begin, Iterator end, Predicate predicate) {
    if (begin==end)
        return false;
    if (begin != end) {
        Iterator next = begin;
        while (++next != end) {
            if (!predicate(*begin, *next))
                return false;
            begin = next;
        }
    }
    return true;
}

template<class Iterator, class Predicate>
bool is_partitioned(Iterator begin, Iterator end, Predicate predicate) {
    if (begin == end)
        return false;
    for (; begin != end; ++begin)
        if (!predicate(*begin))
            break;
    for (; begin != end; ++begin)
        if (predicate(*begin))
            return false;
    return true;
}

template<class Iterator, class Predicate>
constexpr Iterator find_not(Iterator begin, Iterator end, const Predicate& predicate) {
    for (; begin != end; ++begin)
        if (*begin!= predicate)
            return begin;
    return end;
}

template<class Iterator, class Predicate>
constexpr Iterator find_backward(Iterator begin, Iterator end, const Predicate& predicate) {
    if (begin==end)
        return end;
    auto it = end;
    --it;
    for (; it != begin; --it)
        if (*it== predicate)
            return it;
    if (*begin == predicate)
        return begin;
    return end;
}

template<class Iterator, class Condition>
bool is_palindrome(Iterator begin, Iterator end, Condition condition) {
    if (begin==end)
        return false;
    auto temp = end;
    while(begin != --end and begin != temp){
        if(condition(*begin) != condition(*end))
            return false;
        begin++;
    }
    return true;
}

