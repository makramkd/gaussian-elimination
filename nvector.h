//
// Created by Makram Kamaleddine on 10/19/15.
//

#ifndef MATRIX_NVECTOR_H
#define MATRIX_NVECTOR_H

#include <vector>

template<class T>
class nvector {
public:
    nvector()
    :data()
    {

    }

    nvector(typename std::vector<T>::size_type sz)
            :data(sz)
    {

    }

    nvector(std::vector<T> in)
            :data(in)
    {

    }

    nvector(const nvector& other)
            :data(other.data)
    {

    }

    typename std::vector<T>::size_type size() const {
        return data.size();
    }

    T& operator[](int i) {
        return data[i];
    }

    const T& operator[](int i) const {
        return data[i];
    }

    typename std::vector<T>::iterator begin() {
        return data.begin();
    }

    typename std::vector<T>::iterator end() {
        return data.end();
    }
private:
    std::vector<T> data;
};


#endif //MATRIX_NVECTOR_H
