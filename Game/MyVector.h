//
// Created by dartmoor on 18.12.18.
//

#ifndef NIGHTSWORD_MYVECTOR_H
#define NIGHTSWORD_MYVECTOR_H


template <class ValueType>
class vector {
public:
    typedef ValueType  value_type;
    typedef ValueType* pointer;
    typedef ValueType& reference;
    typedef pointer iterator;

    vector() : begin_(0), end_(0), end_of_storage_(0) {}

    ~vector() { delete [] begin_; }

    void clear() { end_ = begin_; }

    bool empty() const { return begin_ == end_; }

    unsigned long size() const { return end_ - begin_; }

    void reserve(unsigned long new_size) {
        if (new_size > size()) {
            auto new_begin = new ValueType[new_size];////////// auto pointer
            pointer new_end = new_begin;
            for (iterator i = begin(); i != end(); ++i)
                *new_end++ = *i;

            delete [] begin_;
            begin_ = new_begin;
            end_ = new_end;
            end_of_storage_ = begin_ + new_size;
        }
    }

    iterator begin() const { return begin_; }

    iterator end() const { return end_; }

    reference front() const { return *begin_; }

    reference back() const { return *(end_ - 1); }

    iterator erase(iterator what) {
        for (iterator i = what; i != end() - 1; ++i)
            *i = *(i + 1);
        --end_;
        return what;
    }

    reference at(int position) const { return begin_[position]; }

    iterator insert(iterator before, const value_type &value) {
        if (end_ == end_of_storage_) reserve(size() + 5);
        ++end_;
        for (iterator i = end() - 1; i != before; --i)
            *i = *(i - 1);
        *before = value;
        return before;
    }

    iterator push_back(const value_type &value) {

        if (end_ == end_of_storage_)
            reserve(size() + 5);
        *end_++ = value;
        return end_ - 1;
    }

    reference operator[](int position) const { return begin_[position]; }
private:
    pointer begin_;
    pointer end_;
    pointer end_of_storage_;
};


#endif //NIGHTSWORD_MYVECTOR_H
