#pragma once

#include "table.h"
#include "../list/list.h"
#include "../tree/binary_tree.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Binarny vyhladavaci strom. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T>
	{
	public:
		typedef typename BinaryTreeNode<TableItem<K, T>*> BSTTreeNode;
	public:
		/// <summary> Konstruktor. </summary>
		BinarySearchTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BinarySearchTree, z ktoreho sa prevezmu vlastnosti. </param>
		BinarySearchTree(const BinarySearchTree<K, T>& other);

		/// <summary> Destruktor. </summary>
		~BinarySearchTree();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const;

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Tabulka, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		Table<K, T>& operator=(const Table<K, T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Binarny vyhladavaci strom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		virtual BinarySearchTree<K, T>& operator=(const BinarySearchTree<K, T>& other);

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
		/// <summary> Najde vrchol binarneho vyhladavacieho stromu s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Vrchol binarneho vyhladavacieho stromu s danym klucom. Ak sa kluc v tabulke nenachadza, vrati otca, ktoreho by mal mat vrchol s takym klucom. </returns>
		typename BSTTreeNode* findBSTNode(const K& key, bool & found) const;
	protected:
		/// <summary> Binarny strom s datami. </summary>
		BinaryTree<TableItem<K, T>*>* binaryTree_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

		/// <summary> Vlozi vrchol do stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vlozeny. </param>
		/// <returns> true, ak sa podarilo vrchol vlozit (teda v strome nie je vrchol s rovnakym klucom), false inak. </returns>
		bool tryToInsertNode(BSTTreeNode* node);

		/// <summary> Bezpecne vyjme zo stromu vrchol stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vyjmuty. </param>
		/// <remarks> Vrchol nebude zruseny, iba odstraneny zo stromu a ziadne vrcholy nebudu ukazovat na neho a ani on nebude ukazovat na ziadne ine vrcholy. </remarks>
		void extractNode(BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree():
		Table<K, T>(),
		binaryTree_(new BinaryTree<TableItem<K, T>*>()),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(const BinarySearchTree<K, T>& other):
		BinarySearchTree()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree()
	{
		clear();
		delete binaryTree_;
		binaryTree_ = nullptr;
	}

	template<typename K, typename T>
	inline Structure * BinarySearchTree<K, T>::clone() const
	{
		return new BinarySearchTree<K, T>(*this);
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size() const
	{
		return size_;
	}

	template<typename K, typename T>
	inline Table<K, T>& BinarySearchTree<K, T>::operator=(const Table<K, T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const BinarySearchTree<K, T>&>(other);
		}
		return *this;
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>& BinarySearchTree<K, T>::operator=(const BinarySearchTree<K, T>& other)
	{
		if (this != &other)
		{
			clear();
			/*for (TableItem<K, T>* item : *other.list_)
			{
				list_->add(new TableItem<K, T>(*item));
			}*/
			Tree<TableItem<K, T>*>::PreOrderTreeIterator IteratorCurr(other.binaryTree_->getRoot());
			Tree<TableItem<K, T>*>::PreOrderTreeIterator IteratorEnd(nullptr);

			while (IteratorCurr != IteratorEnd)
			{
				TableItem<K, T>* item = *IteratorCurr;
				++IteratorCurr;
				insert(item->getKey(), item->accessData());
			}
		}
		return *this;
	}

	template<typename K, typename T>
	inline T & BinarySearchTree<K, T>::operator[](const K key)
	{
		bool isThere = false;
		BSTTreeNode* node = findBSTNode(key, isThere);
		if (!isThere)
		{
			throw std::out_of_range("Not such key! BnrtSearch");
		}

		return node->accessData()->accessData();

	}

	template<typename K, typename T>
	inline const T BinarySearchTree<K, T>::operator[](const K key) const
	{
		bool isThere = false;
		BSTTreeNode* node = findBSTNode(key, isThere);
		if (!isThere)
		{
			throw std::out_of_range("Not such key! BnrtSearch");
		}

		return node->accessData()->accessData();

	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K & key, const T & data)
	{
		TableItem<K, T>* item = new TableItem<K, T>(key, data);
		BSTTreeNode* node = new BSTTreeNode (item);

		if (tryToInsertNode(node))
		{
			size_++;
		} 
		else
		{
			delete item;
			delete node;
			throw std::logic_error("Key is already there!");
		}
		
	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K & key)
	{
		//TODO 10: BinarySearchTree
		throw std::exception("BinarySearchTree<K, T>::remove: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K & key, T & data)
	{
		bool isThere = false;
		BSTTreeNode* node = findBSTNode(key, isThere);
		if (isThere)
		{
			data = node->accessData()->accessData();
		}

		return isThere;

	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K & key)
	{
		bool isThere = false;
		findBSTNode(key, isThere);
		return isThere;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear()
	{
		for (TableItem<K, T>* item : *binaryTree_) {
			delete item;
		}
		binaryTree_->clear();
		size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator() const
	{
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(binaryTree_->getRoot());
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator() const
	{
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(nullptr);
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K,T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(const K & key, bool & found) const
	{
		found = false;

		if (binaryTree_->getRoot() == nullptr)
		{
			return nullptr;
		}

		BSTTreeNode* currNode = dynamic_cast<BSTTreeNode*>(binaryTree_->getRoot());
		while (key != currNode->accessData()->getKey()) 
		{
			if (key < currNode->accessData()->getKey())
			{
				if (currNode->hasLeftSon())
				{
					currNode = currNode->getLeftSon();
				}
				else 
				{
					return currNode;
				}
			}
			else 
			{
				if (currNode->hasRightSon())
				{
					currNode = currNode->getRightSon();
				}
				else
				{
					return currNode;
				}
			}
		}

		found = true; 
		return currNode;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node)
	{
		if (binaryTree_->getRoot() == nullptr)
		{
			binaryTree_->replaceRoot(node);
			return true;
		}
		bool found = false;
		BSTTreeNode* parent = findBSTNode(node->accessData()->getKey(), found);
		if (found)
		{
			return false;
		}

			if (node->accessData()->getKey() < parent->accessData()->getKey())
			{
				parent->setLeftSon(node);
			}
			else
			{
				parent->setRightSon(node);
			}

		return true;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node)
	{
		//TODO 10: BinarySearchTree
		throw std::exception("BinarySearchTree<K, T>::extractNode: Not implemented yet.");
	}

}