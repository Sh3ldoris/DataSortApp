#include "App.h"
#include "structures/heap_monitor.h"
#include <iostream>

#include <Windows.h>


using namespace structures;
using namespace std;

int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	setlocale(LC_ALL, "slovak");

	initHeapMonitor();

	App ap;
	ap.run();
	return 0;
}