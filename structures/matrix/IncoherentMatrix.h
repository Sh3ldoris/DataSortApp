#pragma once
#include <iostream>
#include "Matrix.h"
#include "../array/array.h"
#include "../ds_routines.h"

namespace mystruct
{
	using namespace std;
	template<typename T>
	class IncoherentMatrix : public Matrix<T>
	{
	public:
		IncoherentMatrix(const int x, const int y);
		~IncoherentMatrix();
		T& item(const int x, const int y) override;
		const T item(const int x1, const int y1) const override;
		int getRowLength() override;
		int getColumnLength() override;
		void setValues(const int value) override;

	private:
		structures::Array<structures::Array<T>*>* array_;
		int rowLength;
		int columnLength;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(const int x, const int y) :
		rowLength(y),
		columnLength(x),
		array_(new structures::Array<structures::Array<T>*>(x))
	{
		for (int i = 0; i < array_->size(); i++)
		{
			(*array_)[i] = new structures::Array<T>(y);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (int i = 0; i < array_->size(); i++)
		{
			delete (*array_)[i];
		}
		delete array_;
		array_ = nullptr;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::item(const int x, const int y)
	{
		return (*(*array_)[x])[y];
	}

	template<typename T>
	inline const T IncoherentMatrix<T>::item(const int x1, const int y1) const
	{
		return (*(*array_)[x1])[y1];
	}

	template<typename T>
	inline int IncoherentMatrix<T>::getRowLength()
	{
		return rowLength;
	}

	template<typename T>
	inline int IncoherentMatrix<T>::getColumnLength()
	{
		return columnLength;
	}

	template<typename T>
	inline void IncoherentMatrix<T>::setValues(const int value)
	{
		for (int i = 0; i < array_->size(); i++)
		{
			structures::Array<T>* ar = (*array_)[i];
			for (int j = 0; j < ar->size(); j++)
			{
				(*ar)[j] = value;
			}
		}
	}
}

