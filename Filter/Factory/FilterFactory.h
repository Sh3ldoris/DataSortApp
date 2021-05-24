#pragma once
#include "../Filter.h"
#include "../../structures/heap_monitor.h"
#include "../FilterName.h"
#include "../FilterTotalCitizens.h"
#include "../FilterBuiltArea.h"
#include "../FilterCUType.h"
#include "../FilterUpperCU.h"
#include "../../Utils.h"

#include <string>
#include <iostream>

using namespace std;

class FilterFactory
{
public:
	static Filter* createFilterName()
	{
		cout << "**** Vypis podla nazvu ****\n";
		cout << "Zadajte hladany nazov: \n";
		string rawInput;
		
		getline(cin >> ws, rawInput);

		system("cls");
		return new FilterName(rawInput);
	}

	static Filter* createFilterTotalCitizens()
	{
		cout << "**** Vypis podla poctu obyvatelov ****\n";
		cout << "Zadajte minimalny pocet: ";
		int min;
		cin >> min;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			min = -1;
		}
		while (min < 0)
		{
			Utils::onceAgainSelection(min);
		}

		cout << "Zadajte maximalny pocet: ";
		int max;
		cin >> max;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			max = -1;
		}
		while (max < 0)
		{
			Utils::onceAgainSelection(max);
		}

		system("cls");
		return new FilterTotalCitizens(min, max);
	}

	static Filter* createFilterBuiltArea()
	{
		cout << "**** Vypis podla velkosti zastavanej plochy****\n";
		cout << "Zadajte minimalny pocet: ";
		double min;
		cin >> min;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			min = -1;
		}
		while (min < 0)
		{
			Utils::onceAgainSelection(min);
		}

		cout << "Zadajte maximalny pocet: ";
		double max;
		cin >> max;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			max = -1;
		}
		while (max < 0)
		{
			Utils::onceAgainSelection(max);
		}

		system("cls");
		return new FilterBuiltpercentage(min, max);
	}

	static Filter* createFilterType()
	{
		if (!Utils::yesNoSelection("Chcete zadaù typ hæadanej UJ?"))
		{
			system("cls");
			return nullptr;
		}

		system("cls");

		cout << "**** Filter pre typ hæadanej UJ ****\n";
		cout << "Zadajte hladany typ UJ: \n";
		cout << "\t1 - obec\n";
		cout << "\t2 - okres\n";
		cout << "\t3 - kraj\n";
		cout << "\t4 - vöetky typy\n";
		cout << "Vas vyber: ";

		int selection;
		CountryUnitType cuType;

		cin >> selection;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			selection = -1;
		}
		while (!initializeCUType(selection, cuType))
		{
			Utils::onceAgainSelection(selection);
		}
		if (selection == 4)
		{
			return nullptr;
		} 
		else
		{
			return new FilterCUType(cuType);
		}
	}

	static Filter* createFilterUpperCu()
	{
		if (!Utils::yesNoSelection("Chcete zadaù n·zov vyööej UJ?"))
		{
			system("cls");
			return nullptr;
		}

		system("cls");

		cout << "**** Filter pre n·zov vyööej UJ ****\n";
		cout << "Zadajte hladany nazov: \n";
		string rawInput;

		getline(cin >> ws, rawInput);

		system("cls");
		return new FilterUpperCU(rawInput);
	}

private:
	static bool initializeCUType(int selection, CountryUnitType& cuT) {
		switch (selection)
		{
		case 1:
			system("cls");
			cuT = CountryUnitType::OBEC;
			return true;
		case 2:
			system("cls");
			cuT = CountryUnitType::OKRES;
			return true;
		case 3:
			system("cls");
			cuT = CountryUnitType::KRAJ;
			return true;
		case 4:
			system("cls");
			return true;
		default:
			return false;
		}
		return false;
	}

};
