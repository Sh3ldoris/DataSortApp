#pragma once
#include "CountryUnit.h"
#include "../Utils.h"

#include <string>

class Kraj : public CountryUnit
{
public:
	Kraj(MyString name, int preProdCitizens, int prodCitizens,
		int poProdCitizens, double totalArea, double builtArea);
	Kraj(MyString name);
	~Kraj();
};

inline Kraj::Kraj(MyString name, int preProdCitizens,
				int prodCitizens, int poProdCitizens, 
				double totalArea, double builtArea) :
	CountryUnit::CountryUnit(name, preProdCitizens, 
							prodCitizens, poProdCitizens, 
							totalArea, builtArea,
							CountryUnitType::KRAJ)
{
}

inline Kraj::Kraj(MyString name) :
	Kraj(name, 0, 0, 0 ,0, 0)
{
}

inline Kraj::~Kraj()
{
}

