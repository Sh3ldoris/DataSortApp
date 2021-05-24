#pragma once
#include "Filter.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Selector/Selector.h"
#include "../structures/table/table.h"

#include <string>

using namespace std;

class FilterBuiltpercentage : public Filter
{
public:
	FilterBuiltpercentage(double minValue, double maxValue);
	~FilterBuiltpercentage();
	bool isValueOk(CountryUnit& cu) override;
	void filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems) override;
	void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems) override;

private:
	double minValue_, maxValue_;
	Selector<double>* selector_;
};

inline FilterBuiltpercentage::FilterBuiltpercentage(double minValue, double maxValue) :
	Filter::Filter(),
	selector_(new SelectorBuiltPercentage()),
	minValue_(minValue),
	maxValue_(maxValue)
{
}

inline FilterBuiltpercentage::~FilterBuiltpercentage()
{
	delete selector_;
	selector_ = nullptr;
}

inline bool FilterBuiltpercentage::isValueOk(CountryUnit& cu)
{
	return selector_->getValue(cu) > minValue_ && selector_->getValue(cu) < maxValue_;
}

inline void FilterBuiltpercentage::filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) >= minValue_ && selector_->getValue(*tableItem->accessData()) <= maxValue_)
		{
			foundItems.add(tableItem->accessData());
		}
	}
}

inline void FilterBuiltpercentage::filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) >= minValue_ && selector_->getValue(*tableItem->accessData()) <= maxValue_)
		{
			foundItems.insert(tableItem->getKey(), tableItem->accessData());
		}
	}
}

