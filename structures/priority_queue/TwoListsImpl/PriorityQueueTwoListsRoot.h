#pragma once
#include "../priority_queue_two_lists.h"

namespace structures
{
	template<typename T>
	class PriorityQueueTwoListsRoot : public PriorityQueueTwoLists<T>
	{
	public:
		void push(const int priority, const T& data) override;
	};

	template<typename T>
	inline void PriorityQueueTwoListsRoot<T>::push(const int priority, const T& data)
	{
	}
}
