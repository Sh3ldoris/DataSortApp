#pragma once
#include "../CountryUnit/CountryUnit.h"
#include "../MyString.h"
#include "../Utils.h"

#include <string>

using namespace std;

template<typename T>
class Selector
{
public:
	virtual ~Selector() {};
	virtual T getValue(CountryUnit& cu) = 0;
};

class SelectorName : public Selector<MyString>
{
public:
	SelectorName() {};
	~SelectorName() {};
	MyString getValue(CountryUnit& cu) override {
		return cu.getName();
	};
};

class SelectorBuiltArea : public Selector<double>
{
public:
	SelectorBuiltArea() {};
	~SelectorBuiltArea() {};
	double getValue(CountryUnit& cu) override {
		return cu.getBuiltArea();
	};
};

class SelectorTotalArea : public Selector<double>
{
public:
	SelectorTotalArea() {};
	~SelectorTotalArea() {};
	double getValue(CountryUnit& cu) override {
		return cu.getTotalArea();
	};
};

class SelectorPoProdCitizens : public Selector<int>
{
public:
	SelectorPoProdCitizens() {};
	~SelectorPoProdCitizens() {};
	int getValue(CountryUnit& cu) override {
		return cu.getPoProdCitizens();
	};
};

class SelectorPreProdCitizens : public Selector<int>
{
public:
	SelectorPreProdCitizens() {};
	~SelectorPreProdCitizens() {};
	int getValue(CountryUnit& cu) override {
		return cu.getPreProdCitizens();
	};
};

class SelectorProdCitizens : public Selector<int>
{
public:
	SelectorProdCitizens() {};
	~SelectorProdCitizens() {};
	int getValue(CountryUnit& cu) override {
		return cu.getProdCitizens();
	};
};

class SelectorTotalCitizens : public Selector<int>
{
public:
	SelectorTotalCitizens() {};
	~SelectorTotalCitizens() {};
	int getValue(CountryUnit& cu) override {
		return cu.getProdCitizens() + cu.getPreProdCitizens() + cu.getPoProdCitizens();
	};
};

class SelectorBuiltPercentage : public Selector<double>
{
public:
	SelectorBuiltPercentage() {};
	~SelectorBuiltPercentage() {};
	double getValue(CountryUnit& cu) override {
		return 100 * (cu.getBuiltArea() / cu.getTotalArea());
	};
};

class SelectorUpperCu : public Selector<MyString>
{
public:
	SelectorUpperCu() {};
	~SelectorUpperCu() {};
	MyString getValue(CountryUnit& cu) override {
		return cu.getUpperCU()->getName();
	};
};

class SelectorType : public Selector<CountryUnitType>
{
public:
	SelectorType() {};
	~SelectorType() {};
	CountryUnitType getValue(CountryUnit& cu) override {
		return cu.getType();
	};
};
