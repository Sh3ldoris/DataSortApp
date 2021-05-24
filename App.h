#pragma once
#include "Utils.h"
#include "structures/heap_monitor.h"
#include "Level/Level.h"
#include "Level/Level1.h"
#include "Level/Level2.h"
#include <iostream>

using namespace std;

class App
{
public:
	App();
	~App();
	void run();

private:
	void printLevelSelection();
	bool initializeLevel(int testSelection);

private:
	Level* level;
	int levelSelection = -1;
};

inline App::App() :
	level(nullptr)
{
}

inline App::~App()
{
	delete level;
	level = nullptr;
}

inline void App::run()
{
	printLevelSelection();
	system("cls");
	level->doLevel();
}

inline void App::printLevelSelection()
{
	cout << "Vyberte uroven aplikacie, ktora sa ma spustit:\n";
	cout << "\t1 - 3. uroven\n";
	cout << "\t2 - 4. uroven\n";
	cout << "Vas vyber: ";
	cin >> levelSelection;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		levelSelection = -1;
	}
	while (!initializeLevel(levelSelection))
	{
		Utils::onceAgainSelection(levelSelection);
	}
}

inline bool App::initializeLevel(int testSelection)
{
	switch (testSelection)
	{
	case 1:
	{
		level = new Level1();
		break;
	}
	case 2:
	{
		level = new Level2();
		break;
	}
	default:
		return false;
	}

	return true;
}



