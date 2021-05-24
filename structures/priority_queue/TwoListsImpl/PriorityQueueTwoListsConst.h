#pragma once
#include "../priority_queue_two_lists.h"
#include <iostream>

namespace structures
{
	template<typename T>
	class PriorityQueueTwoListsConst : public PriorityQueueTwoLists<T>
	{
	public:
		PriorityQueueTwoListsConst(int capacity);
		T pop() override;
	};

	template<typename T>
	inline PriorityQueueTwoListsConst<T>::PriorityQueueTwoListsConst(int capacity)
	{
		this->shortList_->trySetCapacity(capacity > 0 ? capacity : 1);
	}

	template<typename T>
	inline T PriorityQueueTwoListsConst<T>::pop()
	{
		T data = this->shortList_->pop();
		if (this->longList_->size() == 0)
		{
			return data;
		}

		if (this->shortList_->isEmpty() && !this->longList_->isEmpty())
		{
			LinkedList<PriorityQueueItem<T>*>* newList = new LinkedList<PriorityQueueItem<T>*>();
			while (this->longList_->size() != 0)
			{
				PriorityQueueItem<T>* removed = this->longList_->removeAt(this->longList_->size() - 1);
				PriorityQueueItem<T>* item = this->shortList_->pushAndRemove(removed->getPriority(), removed->accessData());
				delete removed;
				if (item != nullptr)
				{
					newList->add(item);
				}
			}
			delete this->longList_;
			this->longList_ = newList;
		}
		return data;
	}
}

