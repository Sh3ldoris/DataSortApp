#pragma once
#include "Utils.h"
#include "structures/heap_monitor.h"
#include <string>

using namespace std;
class MyString
{
public:
	MyString(const char* value);
	MyString(const string& value);
	~MyString();
	MyString& operator=(const char* other);
	MyString& operator=(const string& other);
	bool operator==(const MyString& other);
	bool operator==(const string& other);
	bool operator!=(const string& other);
	bool operator!=(const MyString& other);
	bool operator<(const MyString& other);
	bool operator>(const MyString& other);
	string toString();
	friend ostream& operator<<(ostream& os, const MyString& other)
	{
		os << other.value_;
		return os;
	};

private:
	string value_;
};

inline MyString::MyString(const char* value = '\0') :
	value_(value)
{

}

inline MyString::MyString(const string& value) :
	value_(value)
{
}

inline MyString::~MyString() 
{
	
}

inline MyString& MyString::operator=(const char* other)
{
	value_ = other;
	return *this;
}

inline MyString& MyString::operator=(const string& other)
{
	value_ = other;
	return *this;
}

inline bool MyString::operator==(const MyString& other)
{
	return value_ == other.value_;
}

inline bool MyString::operator==(const string& other)
{
	return value_ == other;
}

inline bool MyString::operator!=(const string& other)
{
	return value_ != other;
}

inline bool MyString::operator!=(const MyString& other)
{
	return value_ != other.value_;
}

inline bool MyString::operator<(const MyString& other)
{
	if (value_ == other.value_)
	{
		return false;
	}

	int i = 0;
	char a = value_[i];
	char b = other.value_[i++];
	while (a != '\0' || b != '\0')
	{
		if (Utils::getValueCode(a) < Utils::getValueCode(b))
		{
			return true;
		} 
		else if (Utils::getValueCode(a) > Utils::getValueCode(b))
		{
			return false;
		}
		a = value_[i];
		b = other.value_[i++];
	}

	if (a == '\0' && b != '\0')
	{
		return true;
	}
	else 
	{
		return false;
	}
}

inline bool MyString::operator>(const MyString& other)
{
	if (value_ == other.value_)
	{
		return false;
	}

	int i = 0;
	char a = value_[i];
	char b = other.value_[i++];
	while (a != '\0' || b != '\0')
	{
		if (Utils::getValueCode(a) > Utils::getValueCode(b))
		{
			return true;
		}
		else if (Utils::getValueCode(a) < Utils::getValueCode(b))
		{
			return false;
		}
		a = value_[i];
		b = other.value_[i++];
	}

	if (a == '\0' && b != '\0')
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline string MyString::toString()
{
	return value_;
}
