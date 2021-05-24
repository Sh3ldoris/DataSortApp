#pragma once

namespace mystruct
{
	template<typename T>
	class Matrix
	{
	public:
		virtual T& item(int x, int y) = 0;
		virtual const T item(int x1, int y1) const = 0;
		virtual ~Matrix();
		virtual int getRowLength() = 0;
		virtual int getColumnLength() = 0;
		virtual void setValues(const int value) = 0;
	};
	template<typename T>
	inline Matrix<T>::~Matrix()
	{
	}
}