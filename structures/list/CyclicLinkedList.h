#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class CycledLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		CycledLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		CycledLinkedListItem(const CycledLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~CycledLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		CycledLinkedListItem<T>* getNext();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(CycledLinkedListItem<T>* next);

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		CycledLinkedListItem<T>* getPrevious();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setPrevious(CycledLinkedListItem<T>* previous);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		CycledLinkedListItem<T>* next_;
		CycledLinkedListItem<T>* previous_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class CyclicedLikedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		CyclicedLikedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		CyclicedLikedList(const CyclicedLikedList<T>& other);

		/// <summary> Destruktor. </summary>
		~CyclicedLikedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		CyclicedLikedList<T>& operator=(const CyclicedLikedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		CycledLinkedListItem<T>* first_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		CycledLinkedListItem<T>* getItemAtIndex(int index) const;
		CycledLinkedListItem<T>* getLast();
	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class CycledLinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			CycledLinkedListIterator(const CyclicedLikedList<T>* cycledList, const int position);

			/// <summary> Destruktor. </summary>
			~CycledLinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Iterovany zoznam. </summary>
			const CyclicedLikedList<T>* list_;
			/// <summary> Aktualny item v iteratore. </summary>
			CycledLinkedListItem<T>* current_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline CycledLinkedListItem<T>::CycledLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		previous_(nullptr)
	{
	}

	template<typename T>
	inline CycledLinkedListItem<T>::CycledLinkedListItem(const CycledLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		previous_(other.previous_)
	{
	}

	template<typename T>
	inline CycledLinkedListItem<T>::~CycledLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}

	template<typename T>
	inline CycledLinkedListItem<T>* CycledLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline void CycledLinkedListItem<T>::setNext(CycledLinkedListItem<T>* next)
	{
		next_ = next;
		next_->previous_ = this;
	}

	template<typename T>
	inline CycledLinkedListItem<T>* CycledLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}

	template<typename T>
	inline void CycledLinkedListItem<T>::setPrevious(CycledLinkedListItem<T>* previous)
	{
		previous_ = previous;
		previous_->next_ = this;
	}

	template<typename T>
	inline CyclicedLikedList<T>::CyclicedLikedList() :
		List<T>::List(),
		size_(0),
		first_(nullptr)
	{
	}

	template<typename T>
	inline CyclicedLikedList<T>::CyclicedLikedList(const CyclicedLikedList<T>& other) :
		CyclicedLikedList()
	{
		*this = other;
	}

	template<typename T>
	inline CyclicedLikedList<T>::~CyclicedLikedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* CyclicedLikedList<T>::clone() const
	{
		return new CyclicedLikedList<T>(*this);
	}

	template<typename T>
	inline size_t CyclicedLikedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& CyclicedLikedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const CyclicedLikedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline CyclicedLikedList<T>& CyclicedLikedList<T>::operator=(const CyclicedLikedList<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		clear();

		for (T item : other)
		{
			add(item);
		}
		return *this;
	}

	template<typename T>
	inline T& CyclicedLikedList<T>::operator[](const int index)
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T CyclicedLikedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void CyclicedLikedList<T>::add(const T& data)
	{
		CycledLinkedListItem<T>* newItem = new CycledLinkedListItem<T>(data);
		if (size_ == 0)
		{
			newItem->setNext(newItem);
			first_ = newItem;
		}
		else {
			newItem->setPrevious(getLast());
			newItem->setNext(first_);
		}

		size_++;
	}

	template<typename T>
	inline void CyclicedLikedList<T>::insert(const T& data, const int index)
	{
		if (index == size_)
		{
			add(data);
		}
		else
		{
			DSRoutines::rangeCheckExcept(index, size_, "Index out of range!");
			CycledLinkedListItem<T>* newItem = new CycledLinkedListItem<T>(data);

			if (index == 0)
			{
				newItem->setPrevious(getLast());
				newItem->setNext(first_);
				first_ = newItem;
			}
			else
			{
				CycledLinkedListItem<T>* onIndex = getItemAtIndex(index);

				newItem->setPrevious(onIndex->getPrevious());
				newItem->setNext(onIndex);
			}

			size_++;
		}
	}

	template<typename T>
	inline bool CyclicedLikedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);

		if (index != -1)
		{
			removeAt(index);
			return true;
		}

		return false;
	}

	template<typename T>
	inline T CyclicedLikedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Index out of range!");
		CycledLinkedListItem<T>* removed;

		if (index == 0)
		{
			removed = first_;
			if (size_ > 0)
			{
				first_->getNext()->setPrevious(getLast());
				first_ = first_->getNext();
			}
		}
		else if(index == (size_ - 1))
		{
			removed = getLast();
			getLast()->getPrevious()->setNext(first_);
		}
		else 
		{
			removed = getItemAtIndex(index);
			removed->getNext()->setPrevious(removed->getPrevious());
		}

		T result = removed->accessData();
		delete removed;
		size_--;
		return result;
	}

	template<typename T>
	inline int CyclicedLikedList<T>::getIndexOf(const T& data)
	{
		CycledLinkedListItem<T>* item = first_;
		int i = 0;
		while (item != nullptr)
		{
			if (data == item->accessData())
			{
				return i;
			}
			i++;
			item = item->getNext();
		}
		return -1;
	}

	template<typename T>
	inline void CyclicedLikedList<T>::clear()
	{
		CycledLinkedListItem<T>* item = first_;
		for (int i = 0; i < size_; i++)
		{
			CycledLinkedListItem<T>* deleted = item;
			item = item->getNext();
			delete deleted;
		}
		first_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* CyclicedLikedList<T>::getBeginIterator() const
	{
		return new CycledLinkedListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* CyclicedLikedList<T>::getEndIterator() const
	{
		return new CycledLinkedListIterator(this, size_);
	}

	template<typename T>
	inline CycledLinkedListItem<T>* CyclicedLikedList<T>::getLast()
	{
		return first_ ? first_->getPrevious() : nullptr;
	}

	template<typename T>
	inline CycledLinkedListItem<T>* CyclicedLikedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");

		if (index == size_ - 1)
		{
			return first_->getPrevious();
		}

		CycledLinkedListItem<T>* item = first_;
		for (int i = 0; i < index; i++)
		{
			item = item->getNext();
		}

		return item;
	}

	template<typename T>
	inline CyclicedLikedList<T>::CycledLinkedListIterator::CycledLinkedListIterator(const CyclicedLikedList<T>* cycledList, const int position) :
		list_(cycledList),
		current_(position == cycledList->size() ? nullptr : cycledList->getItemAtIndex(position)),
		position_(position)
	{
	}

	template<typename T>
	inline CyclicedLikedList<T>::CycledLinkedListIterator::~CycledLinkedListIterator()
	{
		list_ = nullptr;
		current_ = nullptr;
		position_ = 0;
	}

	template<typename T>
	inline Iterator<T>& CyclicedLikedList<T>::CycledLinkedListIterator::operator=(const Iterator<T>& other)
	{
		const CycledLinkedListIterator& iter = dynamic_cast<const CycledLinkedListIterator&>(other);
		list_ = iter.list_;
		current_ = iter.current_;
		position_ = iter.position_;

		return *this;
	}

	template<typename T>
	inline bool CyclicedLikedList<T>::CycledLinkedListIterator::operator!=(const Iterator<T>& other)
	{
		const CycledLinkedListIterator& iter = dynamic_cast<const CycledLinkedListIterator&>(other);
		return list_ != iter.list_ ||
			current_ != iter.current_ ||
			position_ != iter.position_;
	}

	template<typename T>
	inline const T CyclicedLikedList<T>::CycledLinkedListIterator::operator*()
	{
		return current_->accessData();
	}

	template<typename T>
	inline Iterator<T>& CyclicedLikedList<T>::CycledLinkedListIterator::operator++()
	{
		if (position_ < list_->size() - 1)
		{
			current_ = current_->getNext();
		}
		else
		{
			current_ = nullptr;
		}

		position_++;
		return *this;
	}
}