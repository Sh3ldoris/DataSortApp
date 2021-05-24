#pragma once
#include <iostream>
#include "Matrix.h"
#include "../array/array.h"
#include "../ds_routines.h"

namespace mystruct
{
    using namespace std;
    template<typename T>
    class CoherentMatrix : public Matrix<T>
    {
    public:
        CoherentMatrix(const int x, const int y);
        ~CoherentMatrix();
        T& item(const int x, const int y) override;
        const T item(const int x1, const int y1) const override;
        int getRowLength() override;
        int getColumnLength() override;
        void setValues(const int value) override;

    private:
        structures::Array<T>* array_;
        int base;
    };

    template<typename T>
    inline CoherentMatrix<T>::CoherentMatrix(const int x, const int y) :
        array_(new structures::Array<T>(x* y)),
        base(y)
    {
    }

    template<typename T>
    inline CoherentMatrix<T>::~CoherentMatrix()
    {
        delete array_;
        array_ = nullptr;
    }

    template<typename T>
    inline T& CoherentMatrix<T>::item(const int x, const int y)
    {
        //structures::DSRoutines::rangeCheckExcept(x, 0, getColumnLength(), "Invalid index!");
        //structures::DSRoutines::rangeCheckExcept(y, 0, getRowLength(), "Invalid index!");
        return (*array_)[x*base+y];
    }

    template<typename T>
    inline const T CoherentMatrix<T>::item(const int x1, const int y1) const
    {
        //structures::DSRoutines::rangeCheckExcept(x1, 0, getColumnLength(), "Invalid index!");
        //structures::DSRoutines::rangeCheckExcept(y1, 0, getRowLength(), "Invalid index!");
        return (*array_)[x1*base +y1];
    }

    template<typename T>
    inline int CoherentMatrix<T>::getRowLength()
    {
        return base;
    }

    template<typename T>
    inline int CoherentMatrix<T>::getColumnLength()
    {
        if (base == 0) {
            return array_->size();
        }
        else {
            return array_->size() / base;
        }
    }

    template<typename T>
    inline void CoherentMatrix<T>::setValues(const int value)
    {
        for (int i = 0; i < array_->size(); i++)
        {
            (*array_)[i] = value;
        }
    }

}