#pragma once
#include "../Utils.h"
#include "Level.h"
#include "../structures/heap_monitor.h"
#include "../Filter/Filter.h"
#include "../Filter/Factory/FilterFactory.h"
#include "../structures/table/table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/list/array_list.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Repository/Repository.h"
#include "../Selector/Selector.h"
#include "../Sort.h"

#include <iostream>
#include <string>

using namespace std;
using namespace structures;

class Level2 : public Level
{
public:
	Level2();
	~Level2();
	void doLevel() override;
private:
	void printSubTaskSelection();
	void printResults();
	bool initializeSubTask(int subtask);
	void addAnotherFilters();

private:
	UnsortedSequenceTable<string, CountryUnit*>* baseTable_;
	UnsortedSequenceTable<string, CountryUnit*>* filteredItems_;

private:
	int subtask = -1;
	bool descending_ = false;
	Repository repo;
	Filter* filter_;
};

inline Level2::Level2() :
	baseTable_(new UnsortedSequenceTable<string, CountryUnit*>()),
	filteredItems_(new UnsortedSequenceTable<string, CountryUnit*>()),
	filter_(nullptr)
{
	system("cls");
	cout << "Nacitava udaje...\n";
	repo.getAllObce(*baseTable_);
	system("cls");
}

inline Level2::~Level2()
{
	for (TableItem<string, CountryUnit*>* tableItem : *baseTable_)
	{
		delete tableItem->accessData();
	}
	delete baseTable_;
	baseTable_ = nullptr;

		filteredItems_->clear();
		delete filteredItems_;
		filteredItems_ = nullptr;

	delete filter_;
	filter_ = nullptr;
}

inline void Level2::doLevel()
{
	addAnotherFilters();
	if (filter_ != nullptr)
	{
		filter_->filterTable(*baseTable_, *filteredItems_);
	} 
	else
	{
		for (TableItem<string, CountryUnit*>* tableItem : *baseTable_)
		{
			filteredItems_->insert(tableItem->getKey(),tableItem->accessData());
		}
	}
	printSubTaskSelection();
	system("cls");
	descending_ = Utils::yesNoSelection("Zoradiù zostupne?");
	initializeSubTask(subtask);
	printResults();
}

inline void Level2::printSubTaskSelection()
{
	cout << "**** Zoradenie obci podla atributu ****\n";
	cout << "Vyberte atribut, podla ktoreho sa maju obce zoradit:\n";
	cout << "\t1 - a) podla nazvu\n";
	cout << "\t2 - b) podla p. obyvatelov\n";
	cout << "\t3 - c) podla zastavanosti\n";
	cout << "Vas vyber: ";
	cin >> subtask;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		subtask = -1;
	}
	while (subtask < 1 || subtask > 3)
	{
		Utils::onceAgainSelection(subtask);
	}
}

inline void Level2::printResults()
{
	SelectorName sName;
	SelectorTotalCitizens sTotalC;
	SelectorBuiltPercentage sBuiltPercentage;

	cout << "Sortovanie: \n\n";
	for (TableItem<string, CountryUnit*>* item : *filteredItems_)
	{
		cout << sName.getValue(*item->accessData());
		switch (subtask)
		{
		case 1:
			cout << endl;
			break;
		case 2:
			cout << " -> poËet obyv.: " << sTotalC.getValue(*item->accessData()) << endl;
			break;
		case 3:
			printf(" -> zastavanosù: %.2f %% \n", sBuiltPercentage.getValue(*item->accessData()));
			break;
		default:
			break;
		}
	}
}

inline bool Level2::initializeSubTask(int subtask)
{
	switch (subtask)
	{
	case 1:
	{
		system("cls");
		Selector<MyString>* s = new SelectorName();
		Sort<MyString>::sort(*filteredItems_, s, descending_);
		delete s;
		return true;
	}
	case 2:
	{
		system("cls");
		Selector<int>* s = new SelectorTotalCitizens();
		Sort<int>::sort(*filteredItems_, s, descending_);
		delete s;
		return true;
	}
	case 3:
	{
		system("cls");
		Selector<double>* s = new SelectorBuiltPercentage();
		Sort<double>::sort(*filteredItems_, s, descending_);
		delete s;
		return true;
	}
	default:
		break;
		return false;
	}
	return false;
}

inline void Level2::addAnotherFilters()
{
		filter_ = FilterFactory::createFilterType();

		Filter* anotherFilter = FilterFactory::createFilterUpperCu();
		if (anotherFilter != nullptr)
		{
			if (filter_ != nullptr)
			{
				filter_->addFilter(anotherFilter);
			}
			else
			{
				filter_ = anotherFilter;
			}
		}
}