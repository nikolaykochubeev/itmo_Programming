#include <memory>
#include <stdexcept>

template<class T, class Alloc = std::allocator<T>>
class CircularBuffer{
private:
    unsigned int size_{}, capacity_{};
    T* arr, *begin_;
    T* end_;
    T* current_begin;
    T* current_end;
    Alloc alloc;
    using traits = std::allocator_traits<Alloc>;
public:
    explicit CircularBuffer(unsigned int size_): capacity_(size_ * 2), arr(traits::allocate(alloc, capacity_)), begin_(&arr[0]), end_(&arr[size_ - 1]), current_begin(&arr[0]), current_end(&arr[0]), size_(size_){}
    CircularBuffer(const CircularBuffer &c): size_(c.size_), capacity_(c.capacity_), arr(c.arr), begin_(c.begin_), end_(c.end_), current_begin(c.current_begin), current_end(c.current_end){} //передать аллокатор
    class iter: public std::iterator<std::random_access_iterator_tag, T> {
    private: T *current_value_;
    public:
        explicit iter(T *cur_value): current_value_(cur_value){}
        [[nodiscard]] T *current_value() const {
            return current_value_;
        }
        iter operator+(int i) {
            current_value_ += i;
            return *this;
        }
        iter operator-(int i) {
            current_value_ -= i;
            return *this;
        }
        T &operator*() const {
            return *current_value_;
        }
        T *operator->() const {
            return current_value_;
        }
        iter &operator++() {
            ++current_value_;
            return *this;
        }
        iter operator--() {
            --current_value_;
            return *this;
        }
        iter &operator=(T *i) {
            current_value_ = i;
            return *this;
        }
        bool operator==(const iter &i) {
            return this->current_value_ = i.current_value_;
        }
        bool operator!=(const iter &i) {
            return this->current_value_ != i.current_value_;
        }
        bool operator>(const iter &i) {
            return this->current_value_ > i.current_value_;
        }
        bool operator>=(const iter &i) {
            return this->current_value_ >= i.current_value_;
        }
        bool operator<(const iter &i) {
            return this->current_value_ < i.current_value_;
        }
        bool operator<=(const iter &i) {
            return this->current_value_ <= i.current_value_;
        }
    };
    [[nodiscard]] int size() const {
        return this->size_;
    }
    iter begin() {
        return iter(arr);
    }
    iter end() {
        return iter(arr + size_); //добавить закольцованность итератора
    }
    void push_front(const T &value) {
        //traits::destroy(alloc, current_begin); с проверкой на заполненность
        traits::construct(alloc, current_begin, value);// изначально указывают на одно и тоже место
        (begin_ == current_begin) ? current_begin = end_ : --current_begin;
    }
    void pop_front() {
        traits::destroy(alloc, current_begin);
        (current_begin == end_) ? current_begin = begin_ : ++current_begin;
    }
    void push_back(const T &value) {
        traits::construct(alloc, current_end, value); //если заполнен двигать две границы
        (end_ == current_end) ? current_end = begin_ : ++current_end;
    }
    void pop_back() {
        traits::destroy(alloc, current_end);
        (current_end == begin_) ? current_end = end_ : --current_end;
    }
    void change_capacity(int i) {
        if (i <= capacity_) throw std::invalid_argument("Invalid new capacity");
        T* new_arr = traits::allocate(alloc, i);
        for (int k = 0; k<capacity_;++k){ //проходиться от current_begin до current_end
            traits::construct(alloc, new_arr+k, arr[k]);
            traits::destroy(alloc, arr+k);
        }
        traits::deallocate(alloc, arr, capacity_);
        capacity_ = i;
        arr = new_arr;
    }
    T operator[](int i) const { //const перегрузка и не const
        return arr[i % capacity_];
    }
    ~CircularBuffer() {
        for (int i = 0; i < size_; ++i) traits::destroy(alloc, arr+i); //от current_begin до current_end
        traits::deallocate(alloc, arr, capacity_);
    }
};
// условие, чтобы end != begin
// выделять capacity ++
