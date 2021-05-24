#pragma once
#include "CountryUnit/CountryUnit.h"
#include "Selector/Selector.h"
#include "structures/table/sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"

#include <string>

template<typename T>
class Sort
{
public:
	static void sort(structures::UnsortedSequenceTable<std::string, CountryUnit*>& table, Selector<T>* selector, bool dsc)
	{
		bool change;

		for (int i = 1; i < table.size() - 1; i++)
		{
			int act = i;
			do
			{
				change = false;
				int father = (act - 1) / 2;
				if (dsc)
				{
					if (act > 0 && selector->getValue(*table.getItemAtIndex(act).accessData()) < selector->getValue(*table.getItemAtIndex(father).accessData()))
					{
						table.swap(act, father);
						act = father;
						change = true;
					}
				}
				else 
				{
					if (act > 0 && selector->getValue(*table.getItemAtIndex(act).accessData()) > selector->getValue(*table.getItemAtIndex(father).accessData()))
					{
						table.swap(act, father);
						act = father;
						change = true;
					}
				}
			} while (change);
		}
		for (int i = table.size() - 1; i > 1; i--)
		{
			table.swap(0, i);
			int act = 0;
			do
			{
				change = false;
				int left = act * 2 + 1;
				int right = act * 2 + 2;
				int max;
				if (left < i && right < i)
				{
					if (dsc)
					{
						max = selector->getValue(*table.getItemAtIndex(left).accessData()) < selector->getValue(*table.getItemAtIndex(right).accessData()) ? left : right;
					}
					else
					{
						max = selector->getValue(*table.getItemAtIndex(left).accessData()) > selector->getValue(*table.getItemAtIndex(right).accessData()) ? left : right;
					}
					
				}
				else
				{
					max = left < i ? left : right;
				}

				if (dsc)
				{
					if (max < i && selector->getValue(*table.getItemAtIndex(max).accessData()) < selector->getValue(*table.getItemAtIndex(act).accessData()))
					{
						table.swap(max, act);
						act = max;
						change = true;
					}
				} 
				else
				{
					if (max < i && selector->getValue(*table.getItemAtIndex(max).accessData()) > selector->getValue(*table.getItemAtIndex(act).accessData()))
					{
						table.swap(max, act);
						act = max;
						change = true;
					}
				}
			} while (change);
		}
	};
		/*{
		helpSort(0, table.size() - 1, table, selector, dsc);
	};*/

//private:
//	static void helpSort(int min, int max, structures::UnsortedSequenceTable<std::string, CountryUnit*>& table, Selector<T>* selector, bool dsc)
//	{
//		T pivot = selector->getValue(*table.getItemAtIndex((int)(min + max) / 2).accessData());
//		int left = min;
//		int right = max;
//
//		do
//		{
//			if (dsc)
//			{
//				while (selector->getValue(*table.getItemAtIndex(left).accessData()) > pivot)
//				{
//					left++;
//				}
//				while (selector->getValue(*table.getItemAtIndex(right).accessData()) < pivot)
//				{
//					right--;
//				}
//			} 
//			else
//			{
//				while (selector->getValue(*table.getItemAtIndex(left).accessData()) < pivot)
//				{
//					left++;
//				}
//				while (selector->getValue(*table.getItemAtIndex(right).accessData()) > pivot)
//				{
//					right--;
//				}
//			}
//			if (left <= right)
//			{
//				table.swap(left, right);
//				left++;
//				right--;
//			}
//		} while (left <= right);
//
//		if (min < right)
//		{
//			helpSort(min, right, table, selector, dsc);
//		}
//		if (left < max)
//		{
//			helpSort(left, max, table, selector, dsc);
//		}
//	};
};
