#pragma once
#include "Filter.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Selector/Selector.h"
#include "../structures/table/table.h"

#include <string>

using namespace std;

class FilterTotalCitizens : public Filter
{
public:
	FilterTotalCitizens(int minValue, int maxValue);
	~FilterTotalCitizens();
	bool isValueOk(CountryUnit& cu) override;
	void filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems) override;
	void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems) override;

private:
	int minValue_, maxValue_;
	Selector<int>* selector_;
};

inline FilterTotalCitizens::FilterTotalCitizens(int minValue, int maxValue):
	Filter::Filter(),
	selector_(new SelectorTotalCitizens()),
	minValue_(minValue),
	maxValue_(maxValue)
{
}

inline FilterTotalCitizens::~FilterTotalCitizens()
{
	delete selector_;
	selector_ = nullptr;
}

inline bool FilterTotalCitizens::isValueOk(CountryUnit& cu)
{
	return selector_->getValue(cu) > minValue_ && selector_->getValue(cu) < maxValue_;
}

inline void FilterTotalCitizens::filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) >= minValue_ && selector_->getValue(*tableItem->accessData()) <= maxValue_)
		{
			foundItems.add(tableItem->accessData());
		}
	}
}

inline void FilterTotalCitizens::filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) >= minValue_ && selector_->getValue(*tableItem->accessData()) <= maxValue_)
		{
			foundItems.insert(tableItem->getKey(), tableItem->accessData());
		}
	}
}

