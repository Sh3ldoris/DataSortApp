#pragma once
#include "Filter.h"
#include "../Utils.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Selector/Selector.h"
#include "../structures/table/table.h"

class FilterCUType : public Filter
{
public:
	FilterCUType(CountryUnitType type);
	~FilterCUType();
	bool isValueOk(CountryUnit& cu) override;
	void filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems) override;
	void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems) override;

private:
	CountryUnitType type_;
	Selector<CountryUnitType>* selector_;
};

inline FilterCUType::FilterCUType(CountryUnitType type) :
	Filter::Filter(),
	selector_(new SelectorType()),
	type_(type)
{
}

inline FilterCUType::~FilterCUType()
{
	delete selector_;
	selector_ = nullptr;
}

inline bool FilterCUType::isValueOk(CountryUnit& cu)
{
	return selector_->getValue(cu) == type_;
}

inline void FilterCUType::filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) == type_)
		{
			if (Filter::isSatisfyingAnotherFilters(*tableItem->accessData()))
			{
				foundItems.add(tableItem->accessData());
			}
		}
	}
}

inline void FilterCUType::filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) == type_)
		{
			if (Filter::isSatisfyingAnotherFilters(*tableItem->accessData()))
			{
				foundItems.insert(tableItem->getKey(),tableItem->accessData());
			}
		}
	}
}

