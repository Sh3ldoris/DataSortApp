#pragma once
#include "../structures/heap_monitor.h"
#include "../structures/table/table.h"
#include "../structures/list/array_list.h"
#include "../CountryUnit/Obec.h"
#include "../CountryUnit/Kraj.h"
#include "../CountryUnit/Okres.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace structures;
using namespace std;
class Repository
{
public:
	Repository();
	~Repository();
	void getAllObce(Table<string, CountryUnit*>& tableToFill);
};


inline Repository::Repository() 
{
}

inline Repository::~Repository()
{
}

inline void Repository::getAllObce(Table<string, CountryUnit*>& tableToFill)
{
	ifstream fin;
	ifstream fin2;

	fin.open("data/1 Obce SR.csv");
	fin2.open("data/2 Územné èlenenie SR.csv");

	string line, line2, word, word2, name;
	vector<int> numbers{};
	vector<string> cUnitNames{};
	int isName = 0, index = 0, rangeValue = 0;

	ArrayList<CountryUnit*>* okresy = new ArrayList< CountryUnit*>();
	ArrayList<CountryUnit*>* kraje = new ArrayList< CountryUnit*>();

	while (fin.good() && fin2.good()) {

		//Load Okres a Kraj
		cUnitNames.clear();

		getline(fin2, line2);
		stringstream s2(line2);

		//Load one line from Uzemne clenenie
		while (getline(s2, word2, ';')) 
		{
			cUnitNames.push_back(word2);
		}

		name.clear();
		numbers.clear();

		isName = 1;
		getline(fin, line);
		stringstream s(line);

		//Load one line from towns info
		while (getline(s, word, ';'))
		{
			if (isName == 1)
			{
				name = word;
				isName = -1;
				string st = "sdsd";
			}
			else
			{
				int num = stoi(word);
				numbers.push_back(num);
			}
		}

		if (numbers.size() > 4 && cUnitNames.size() > 1)
		{
			string krajName = cUnitNames[2];
			CountryUnit* kraj_ = nullptr;
			for (CountryUnit* kraj : *kraje)
			{
				if (kraj->getName() == krajName)
				{
					kraj_ = kraj;
				}
			}

			if (kraj_ == nullptr)
			{
				kraj_ = new Kraj(krajName);
				kraje->add(kraj_);
			}

			string okresName = cUnitNames[1];
			CountryUnit* okres_ = nullptr;
			for (CountryUnit* okres : *okresy)
			{
				if (okres->getName() == okresName)
				{
					okres_ = okres;
				}
			}

			if (okres_ == nullptr)
			{
				okres_ = new Okres(okresName);
				okresy->add(okres_);
			}

			if (okres_->getUpperCU() == nullptr)
			{
				okres_->setUpperCU(kraj_);
			}

			kraj_->addToPreProdCitizens(numbers[0]);
			kraj_->addToProdCitizens(numbers[1]);
			kraj_->addToPoProdCitizens(numbers[2]);
			kraj_->addToTotalArea(numbers[3]);
			kraj_->addToBuiltArea(numbers[4]);

			okres_->addToPreProdCitizens(numbers[0]);
			okres_->addToProdCitizens(numbers[1]);
			okres_->addToPoProdCitizens(numbers[2]);
			okres_->addToTotalArea(numbers[3]);
			okres_->addToBuiltArea(numbers[4]);

			tableToFill.insert(name, new Obec(name, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], okres_));
		}
    }

	for (CountryUnit* okres : *okresy)
	{
		tableToFill.insert(okres->getName().toString(), okres);
	}

	for (CountryUnit* kraj : *kraje)
	{
		tableToFill.insert(kraj->getName().toString(), kraj);
	}

	delete kraje;
	kraje = nullptr;
	delete okresy;
	okresy = nullptr;
}
