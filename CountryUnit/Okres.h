#pragma once
#include "CountryUnit.h"
#include "../Utils.h"

#include <string>

class Okres : public CountryUnit
{
public:
	Okres(MyString name, int preProdCitizens, int prodCitizens,
		int poProdCitizens, double totalArea, double builtArea);
	Okres(MyString name);
	~Okres();
};

inline Okres::Okres(MyString name, int preProdCitizens,
	int prodCitizens, int poProdCitizens,
	double totalArea, double builtArea) :
	CountryUnit::CountryUnit(name, preProdCitizens,
		prodCitizens, poProdCitizens,
		totalArea, builtArea,
		CountryUnitType::OKRES)
{
}

inline Okres::Okres(MyString name) :
	Okres(name, 0, 0, 0, 0, 0)
{
}

inline Okres::~Okres()
{
}

