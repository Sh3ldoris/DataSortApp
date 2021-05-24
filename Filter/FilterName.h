#pragma once
#include "Filter.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Selector/Selector.h"
#include "../structures/table/table.h"

#include <string>

using namespace std;

class FilterName : public Filter
{
public:
	FilterName(string searchingName);
	~FilterName();
	bool isValueOk(CountryUnit& cu) override;
	void filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems) override;
	void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems) override;

private:
	string searchingName_;
	Selector<MyString>* selector_;
};

inline FilterName::FilterName(string searchingName):
	Filter::Filter(),
	selector_(new SelectorName()),
	searchingName_(searchingName)
{
}

inline FilterName::~FilterName()
{
	delete selector_;
	selector_ = nullptr;
}

inline bool FilterName::isValueOk(CountryUnit& cu)
{
	MyString compare(searchingName_);
	return selector_->getValue(cu) == compare;
}

inline void FilterName::filterTable(structures::Table<string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems)
{	
	CountryUnit* founded;
	if (baseTable.tryFind(searchingName_, founded)) 
	{
		if (Filter::isSatisfyingAnotherFilters(*founded))
		{
			foundItems.add(founded);
		}
	}
}

inline void FilterName::filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems)
{
	CountryUnit* founded;
	if (baseTable.tryFind(searchingName_, founded))
	{
		if (Filter::isSatisfyingAnotherFilters(*founded))
		{
			foundItems.insert(founded->getName().toString(), founded);
		}
	}
}

