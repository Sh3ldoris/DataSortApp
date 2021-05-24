#pragma once
#include "Filter.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Selector/Selector.h"
#include "../structures/table/table.h"

#include <string>

class FilterUpperCU : public Filter
{
public:
	FilterUpperCU(MyString upperName);
	~FilterUpperCU();
	bool isValueOk(CountryUnit& cu) override;
	void filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems) override;
	void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems) override;

private:
	MyString upperCUName_;
	Selector<MyString>* selector_;
};

inline FilterUpperCU::FilterUpperCU(MyString upperName) :
	Filter::Filter(),
	selector_(new SelectorUpperCu()),
	upperCUName_(upperName)
{
}

inline FilterUpperCU::~FilterUpperCU()
{
	delete selector_;
	selector_ = nullptr;
}

inline bool FilterUpperCU::isValueOk(CountryUnit& cu)
{
	CountryUnit* upperCu = &cu;
	while (upperCu->getUpperCU() != nullptr)
	{
		if (selector_->getValue(*upperCu) == upperCUName_)
		{
			return true;
		}
		upperCu = upperCu->getUpperCU();
	}
	return false;
}

inline void FilterUpperCU::filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) == upperCUName_)
		{
			if (Filter::isSatisfyingAnotherFilters(*tableItem->accessData()))
			{
				foundItems.add(tableItem->accessData());
			}
		}
	}
}

inline void FilterUpperCU::filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems)
{
	for (structures::TableItem<string, CountryUnit*>* tableItem : baseTable)
	{
		if (selector_->getValue(*tableItem->accessData()) == upperCUName_)
		{
			if (Filter::isSatisfyingAnotherFilters(*tableItem->accessData()))
			{
				foundItems.insert(tableItem->getKey(), tableItem->accessData());
			}
		}
	}
}

