#pragma once
#include "../Utils.h"
#include "Level.h"
#include "../structures/heap_monitor.h"
#include "../Filter/Filter.h"
#include "../Filter/Factory/FilterFactory.h"
#include "../structures/table/table.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/list/array_list.h"
#include "../CountryUnit/CountryUnit.h"
#include "../Repository/Repository.h"
#include "../Selector/Selector.h"

#include <iostream>
#include <string>

using namespace std;
using namespace structures;

class Level1: public Level
{
public:
	Level1();
	~Level1();
	void doLevel() override;
private:
	void printSubTaskSelection();
	void printResults();
	void printNotFound();
	bool initializeSubTask(int subtask);
	void addAnotherFilters();

private:
	Table<string, CountryUnit*>* baseTable_;
	List<CountryUnit*>* filteredItems_;

private:
	int subtask = -1;
	Repository repo;
	Filter* filter_;
};

inline Level1::Level1():
	baseTable_(new SortedSequenceTable<string, CountryUnit*>()),
	filteredItems_(new ArrayList<CountryUnit*>()),
	filter_(nullptr)
{
	system("cls");
	cout << "Nacitava udaje...\n";
	repo.getAllObce(*baseTable_);
	system("cls");
}

inline Level1::~Level1()
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

inline void Level1::doLevel()
{
	printSubTaskSelection();
	if (filter_ != nullptr)
	{
		system("cls");
		addAnotherFilters();
		filter_->filterTable(*baseTable_, *filteredItems_);
	}

	if (filteredItems_->size() == 0)
	{
		printNotFound();
	} 
	else
	{
		printResults();
	}
}

inline void Level1::printSubTaskSelection()
{
	cout << "**** Vypisanie obci podla filtra ****\n";
	cout << "Vyberte filter, podla ktoreho sa maju obce vypisat:\n";
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
	while (!initializeSubTask(subtask))
	{
		Utils::onceAgainSelection(subtask);
	}
}

inline void Level1::printResults()
{
	SelectorName sName;
	SelectorUpperCu sUpperCu;
	SelectorTotalCitizens sTotalC;
	SelectorPreProdCitizens sPreProdC;
	SelectorProdCitizens sProdC;
	SelectorPoProdCitizens sPoProdC;
	SelectorBuiltPercentage sBuiltPercentage;
	SelectorTotalArea sTotalArea;
	SelectorBuiltArea sBuiltArea;

	cout << "Najdene udaje: \n\n";
	for (int i = 0; i < filteredItems_->size(); i++)
	{
		cout << "****************\n";
		cout << sName.getValue(*(*filteredItems_)[i]) << endl;
		cout << "****************\n";
		cout << "-> príslušnos: ";
		CountryUnit* unit = (*filteredItems_)[i];
		while (unit->getUpperCU() != nullptr)
		{
			cout << sUpperCu.getValue(*unit) << ", ";
			unit = unit->getUpperCU();
		}
		cout << "Slovensko" << endl;
		cout << "-> poèet obyv.: " << sTotalC.getValue(*(*filteredItems_)[i]) << endl;
		cout << "-> poèet preprod obyv: " << sPreProdC.getValue(*(*filteredItems_)[i]) << endl;
		cout << "-> poèet prod obyv: " << sProdC.getValue(*(*filteredItems_)[i]) << endl;
		cout << "-> poèet poprod obyv: " << sPoProdC.getValue(*(*filteredItems_)[i]) << endl;
		printf("-> zastavanos: %.2f %% \n", sBuiltPercentage.getValue(*(*filteredItems_)[i]));
		printf("-> celk. výmera: %.0f m^2\n", sTotalArea.getValue(*(*filteredItems_)[i]));
		printf("-> zastavaná plocha: %.0f m^2\n", sBuiltArea.getValue(*(*filteredItems_)[i]));
		cout << "-------------------------------\n\n";
	}
}

inline void Level1::printNotFound()
{
	cout << "\n**************************************************\n";
	cout << " :’( Nenašli sa žiadne údaje pre zadaný vstup :’( \n";
	cout << "**************************************************\n";
}

inline bool Level1::initializeSubTask(int subtask)
{
	switch (subtask)
	{
	case 1:
		system("cls");
		filter_ = FilterFactory::createFilterName();
		return true;
	case 2:
		system("cls");
		filter_ = FilterFactory::createFilterTotalCitizens();
		return true;
	case 3:
		system("cls");
		filter_ = FilterFactory::createFilterBuiltArea();
		return true;
	default:
		break;
		return false;
	}
	return false;
}

inline void Level1::addAnotherFilters()
{
	if (filter_ != nullptr)
	{
		Filter* anotherFilter = FilterFactory::createFilterType();
		if (anotherFilter != nullptr)
		{
			filter_->addFilter(anotherFilter);
		}

		anotherFilter = FilterFactory::createFilterUpperCu();
		if (anotherFilter != nullptr)
		{
			filter_->addFilter(anotherFilter);
		}
	}
}
