#pragma once

#include "../Utils.h"
#include "../MyString.h"
#include "../structures/heap_monitor.h"

using namespace std;
class CountryUnit
{
public:
	virtual ~CountryUnit();
	virtual MyString getName();
	virtual CountryUnit* getUpperCU();
	virtual int getPreProdCitizens();
	virtual int getProdCitizens();
	virtual int getPoProdCitizens();
	virtual double getTotalArea();
	virtual double getBuiltArea();
	virtual CountryUnitType getType();

	virtual void setUpperCU(CountryUnit* upperCu);

	virtual void addToPreProdCitizens(int value);
	virtual void addToProdCitizens(int value);
	virtual void addToPoProdCitizens(int value);
	virtual void addToTotalArea(double value);
	virtual void addToBuiltArea(double value);

protected:
	CountryUnit(MyString name, int preProdCitizens, int prodCitizens,
		int poProdCitizens, double totalArea, double builtArea,
		CountryUnitType type);
	CountryUnit(MyString name, int preProdCitizens, int prodCitizens,
		int poProdCitizens, double totalArea, double builtArea,
		CountryUnit* upperCu, CountryUnitType type);
	CountryUnit();

private:
	MyString name_;
	CountryUnit* upperCU_ = nullptr;
	int preProdCitizens_;
	int prodCitizens_;
	int poProdCitizens_;
	double totalArea_;
	double builtArea_;
	CountryUnitType type_;

};

inline CountryUnit::CountryUnit(MyString name, int preProdCitizens,
								int prodCitizens, int poProdCitizens, 
								double totalArea, double builtArea,
								CountryUnitType type) :
	name_(name),
	preProdCitizens_(preProdCitizens),
	prodCitizens_(prodCitizens),
	poProdCitizens_(poProdCitizens),
	totalArea_(totalArea),
	builtArea_(builtArea),
	type_(type)
{

}

inline CountryUnit::CountryUnit(MyString name, int preProdCitizens, 
					int prodCitizens, int poProdCitizens, 
					double totalArea, double builtArea, 
					CountryUnit* upperCu, CountryUnitType type) :
	name_(name),
	preProdCitizens_(preProdCitizens),
	prodCitizens_(prodCitizens),
	poProdCitizens_(poProdCitizens),
	totalArea_(totalArea),
	builtArea_(builtArea),
	upperCU_(upperCu),
	type_(type)
{
}

inline CountryUnit::CountryUnit()
{
}

inline CountryUnit::~CountryUnit()
{
}

inline MyString CountryUnit::getName()
{
	return name_;
}

inline CountryUnit* CountryUnit::getUpperCU()
{
	return upperCU_;
}

inline int CountryUnit::getPreProdCitizens()
{
	return preProdCitizens_;
}

inline int CountryUnit::getProdCitizens()
{
	return prodCitizens_;
}

inline int CountryUnit::getPoProdCitizens()
{
	return poProdCitizens_;
}

inline double CountryUnit::getTotalArea()
{
	return totalArea_;
}

inline double CountryUnit::getBuiltArea()
{
	return builtArea_;
}

inline CountryUnitType CountryUnit::getType()
{
	return type_;
}

inline void CountryUnit::setUpperCU(CountryUnit* upperCU)
{
	upperCU_ = upperCU;
}

inline void CountryUnit::addToPreProdCitizens(int value)
{
	preProdCitizens_ += value;
}

inline void CountryUnit::addToProdCitizens(int value)
{
	prodCitizens_ += value;
}

inline void CountryUnit::addToPoProdCitizens(int value)
{
	poProdCitizens_ += value;
}

inline void CountryUnit::addToTotalArea(double value)
{
	totalArea_ += value;
}

inline void CountryUnit::addToBuiltArea(double value)
{
	builtArea_ += value;
}
