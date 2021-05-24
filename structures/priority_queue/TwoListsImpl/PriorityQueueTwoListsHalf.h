#pragma once
#include "../priority_queue_two_lists.h"

namespace structures
{
	template<typename T>
	class PriorityQueueTwoListsHalf : public PriorityQueueTwoLists<T>
	{
	public:
		T pop() override;
	};
	
	template<typename T>
	inline T PriorityQueueTwoListsHalf<T>::pop()
	{
		T data = this->shortList_->pop();
		if (this->longList_->size() == 0)
		{
			return data;
		}

		if (this->shortList_->isEmpty() && !this->longList_->isEmpty())
		{

			int newCapacity = (int)(this->shortList_->size() + this->longList_->size()) / 2;
			this->shortList_->trySetCapacity(newCapacity > 0 ? newCapacity : 1);

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
