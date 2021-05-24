#pragma once

#include <iostream>
#include <string>

enum CountryUnitType { OBEC, OKRES, KRAJ };

using namespace std;
class Utils
{
public:
	static void onceAgainSelection(int& varToSelect) 
	{
		cout << "\nSkuste to este raz: ";
		cin >> varToSelect;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			varToSelect = -1;
		}
	};

	static void onceAgainSelection(double& varToSelect)
	{
		cout << "\nSkuste to este raz: ";
		cin >> varToSelect;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			varToSelect = -1;
		}
	};

	static void onceAgainSelection(std::string& rawInput) {
		cout << "\nSkuste to este raz: ";
		cin >> rawInput;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			rawInput.clear();
			rawInput = "";
		}
	};

	static int getValueCode(char c) 
	{
		const char* codeTable = " ,-aáäbcèdïeéfghchiíjklå¾mnòoóôpqràsštuúvwxyızAÁÄBCÈDÏEÉFGHCHIÍJKLÅ¼MNÒOÓÔPQRÀSŠTUÚVWXYİZ";
		int i = 0;
		while (codeTable[i] != '\0')
		{
			if (codeTable[i++] == c)
			{
				return i;
			}
		} 
	}

	static bool yesNoSelection(string message) {
		cout << message << endl;
		cout << "\t1 - áno\n";
		cout << "\t2 - nie\n";
		cout << "Vas vyber: ";
		int selection;

		cin >> selection;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			selection = -1;
		}
		while (selection != 1 && selection != 2)
		{
			Utils::onceAgainSelection(selection);
		}
		return selection == 1;
	}
private:

};

