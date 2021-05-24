#pragma once
#include "../CountryUnit/CountryUnit.h"
#include "../Selector/Selector.h"
#include "../structures/heap_monitor.h"
#include "../structures/table/table.h"
#include "../structures/list/array_list.h"

#include <string>
#include <iostream>

class Filter
{
public:
	virtual ~Filter();
	virtual bool isValueOk(CountryUnit& cu) = 0;
	virtual void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::List<CountryUnit*>& foundItems) = 0;
	virtual void filterTable(structures::Table<std::string, CountryUnit*>& baseTable, structures::Table<std::string, CountryUnit*>& foundItems) = 0;
	virtual void addFilter(Filter* fil);

protected:
	Filter();
	bool isSatisfyingAnotherFilters(CountryUnit& cu);
	
protected:
	structures::ArrayList<Filter*>* anotherFilters;
};

inline Filter::~Filter()
{
	for (Filter* fil : *anotherFilters) 
	{
		delete fil;
		fil = nullptr;
	}
	delete anotherFilters;
}

inline void Filter::addFilter(Filter* fil)
{
	anotherFilters->add(fil);
}

inline Filter::Filter():
	anotherFilters(new structures::ArrayList<Filter*>())
{
}

inline bool Filter::isSatisfyingAnotherFilters(CountryUnit& cu)
{
	for (Filter* of : *Filter::anotherFilters)
	{
		if (!of->isValueOk(cu))
		{
			return false;
		}
	}
	return true;
}
