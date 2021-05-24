#pragma once
#include "CountryUnit.h"
#include "../Utils.h"

#include <string>

using namespace std;
class Obec : public CountryUnit
{
public:
	Obec(MyString name, int preProdCitizens, int prodCitizens,
		int poProdCitizens, double totalArea, double builtArea);
	Obec(MyString name, int preProdCitizens, int prodCitizens,
		int poProdCitizens, double totalArea, double builtArea,
		CountryUnit* upperCU);
	~Obec();
};

inline Obec::Obec(MyString name, int preProdCitizens,
				int prodCitizens, int poProdCitizens, 
				double totalArea, double builtArea) :
	CountryUnit::CountryUnit(name, preProdCitizens, 
							prodCitizens, poProdCitizens, 
							totalArea, builtArea,
							CountryUnitType::OBEC)
{
}

inline Obec::Obec(MyString name, int preProdCitizens, 
				int prodCitizens, int poProdCitizens, 
				double totalArea, double builtArea, 
				CountryUnit* upperCU) :
	CountryUnit::CountryUnit(name, preProdCitizens,
		prodCitizens, poProdCitizens,
		totalArea, builtArea,
		upperCU, CountryUnitType::OBEC)
{
}

inline Obec::~Obec()
{
}
