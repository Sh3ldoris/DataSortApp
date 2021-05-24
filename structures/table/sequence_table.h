#pragma once

#include "table.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures 
{

	/// <summary> Sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SequenceTable : public Table<K, T>
	{
	public:
		/// <summary> Destruktor. </sumary>
		~SequenceTable();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Tabulka, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		Table<K, T>& operator=(const Table<K, T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Sekvencna tabulka, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		SequenceTable<K, T>& operator=(const SequenceTable<K, T>& other);

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>  
		T& operator[](const K key) override;

		/// <summary> Vrati hodnotou data s daynm klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Hodnota dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do zoznamu. </exception>  
		const T operator[](const K key) const override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>  
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>  
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() const override;
	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky tabulky. </param>
		/// <remarks> 
		/// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu. 
		/// List dealokuje tento objekt.
		/// </remarks>
		SequenceTable(List<TableItem<K, T>*>* list);

		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		virtual TableItem<K, T>* findTableItem(const K& key) const;
	protected:
		List<TableItem<K, T>*>* list_;
	};

	template<typename K, typename T>
	inline SequenceTable<K, T>::~SequenceTable()
	{
		clear();
		delete list_;
		list_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t SequenceTable<K, T>::size() const
	{
		return list_->size();
	}

	template<typename K, typename T>
	inline Table<K, T>& SequenceTable<K, T>::operator=(const Table<K, T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const SequenceTable<K, T>&>(other);
		}
		return *this;
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>& SequenceTable<K, T>::operator=(const SequenceTable<K, T>& other)
	{
		if (this != &other)
		{
			clear();
			for (TableItem<K, T>* item : *other.list_)
			{
				list_->add(new TableItem<K, T>(*item));
			}
		}
		return *this;
	}

	template<typename K, typename T>
	inline T & SequenceTable<K, T>::operator[](const K key)
	{
		TableItem<K, T>* item = findTableItem(key);
		if (item == nullptr)
		{
			throw std::logic_error("No such key!");
		}
		return item->accessData();
	}

	template<typename K, typename T>
	inline const T SequenceTable<K, T>::operator[](const K key) const
	{
		TableItem<K, T>* item = findTableItem(key);
		if (item == nullptr)
		{
			throw std::logic_error("No such key!");
		}
		return item->accessData();
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::insert(const K & key, const T & data)
	{
		/*if (containsKey(key))
		{
			throw std::logic_error("Item is in table already");
		} */
		list_->add(new TableItem<K, T>(key, data));
	}

	template<typename K, typename T>
	inline T SequenceTable<K, T>::remove(const K & key)
	{
		TableItem<K, T>* deleted = findTableItem(key);
		if (deleted == nullptr)
		{
			throw std::logic_error("Item with given key is not in table");
		}
		T data = deleted->accessData();
		list_->tryRemove(deleted);
		delete deleted;
		return data;
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::tryFind(const K & key, T & data)
	{
		TableItem<K, T>* item = findTableItem(key);
		if (item == nullptr)
		{
			return false;
		}
		data = item->accessData();
		return true;
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::containsKey(const K & key)
	{
		return findTableItem(key) != nullptr;
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::clear()
	{
		for (TableItem<K, T>* item : *list_) {
			delete item;
		}

		list_->clear();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getBeginIterator() const
	{
		return list_->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getEndIterator() const
	{
		return list_->getEndIterator();
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>::SequenceTable(List<TableItem<K, T>*>* list) :
		Table<K, T>(),
		list_(list)
	{
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SequenceTable<K, T>::findTableItem(const K & key) const
	{
		for (TableItem<K, T>* item : *list_) {
			if (key == item->getKey())
			{
				return item;
			}
		}
		return nullptr;
	}

}