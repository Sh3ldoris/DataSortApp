#pragma once

#include "k_way_tree.h"
#include "tree.h"
#include <queue>

namespace structures
{
	/// <summary> Vrchol binarneho stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class BinaryTreeNode : public KWayTreeNode<T,2>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		BinaryTreeNode(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol binarneho stromu, z ktoreho sa prevezmu vlastnosti. </param>
		/// <remarks> Vytvori sa ako plytka kopia vrcholu other. </remarks>
		BinaryTreeNode(const BinaryTreeNode<T>& other);

		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		TreeNode<T>* shallowCopy() override;

		/// <summary> Getter otca. </summary>
		/// <returns> Otec. </returns>
		BinaryTreeNode<T>* getParent() const;

		/// <summary> Getter laveho syna. </summary>
		/// <returns> Lavy syn. </returns>
		BinaryTreeNode<T>* getLeftSon() const;

		/// <summary> Getter praveho syna. </summary>
		/// <returns> Pravy syn. </returns>
		BinaryTreeNode<T>* getRightSon() const;

		/// <summary> Setter laveho syna. </summary>
		/// <param name = "leftSon"> Novy lavy syn. </returns>
		/// <returns> Nahradeny lavy syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		void setLeftSon(BinaryTreeNode<T>* leftSon);

		/// <summary> Setter praveho syna. </summary>
		/// <param name = "rightSon"> Novy pravy syn. </returns>
		/// <returns> Nahradeny pravy vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		void setRightSon(BinaryTreeNode<T>* rightSon);

		/// <summary> Zameni laveho syna. </summary>
		/// <param name = "leftSon"> Novy lavy syn. </returns>
		/// <returns> Nahradeny lavy syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		BinaryTreeNode<T>* changeLeftSon(BinaryTreeNode<T>* leftSon);

		/// <summary> Zameni praveho syna. </summary>
		/// <param name = "rightSon"> Novy pravy syn. </returns>
		/// <returns> Nahradeny pravy vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		BinaryTreeNode<T>* changeRightSon(BinaryTreeNode<T>* rightSon);

		/// <summary> Zisti, ci je lavym synom svojho otca. </summary>
		/// <returns> true, ak je lavym synom svojho otca, false ak nema otca alebo nie je jeho lavym synom. </returns>
		bool isLeftSon() const;

		/// <summary> Zisti, ci je pravym synom svojho otca. </summary>
		/// <returns> true, ak je pravym synom svojho otca, false ak nema otca alebo nie je jeho pravym synom. </returns>
		bool isRightSon() const;

		/// <summary> Zisti, ci ma laveho syna. </summary>
		/// <returns> true, ma laveho syna, false inak. </returns>
		bool hasLeftSon() const;

		/// <summary> Zisti, ci ma praveho syna. </summary>
		/// <returns> true, ma praveho syna, false inak. </returns>
		bool hasRightSon() const;

	private:
		static const int LEFT_SON = 0;
		static const int RIGHT_SON = 1;
	};

	/// <summary> Binary strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T>
	class BinaryTree : public KWayTree<T,2>
	{
	public:
		/// <summary> Konstruktor. </summary>
		BinaryTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Binarny strom, z ktoreho sa prevezmu vlastnosti. </param>
		BinaryTree(const BinaryTree<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vytvori a vrati instanciu vrcholu binarneho stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu binarneho stromu. </returns>
		TreeNode<T>* createTreeNodeInstance() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	public:
		class InOrderTreeIterator : public Tree<T>::TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			InOrderTreeIterator(TreeNode<T>* const startNode);
			Iterator<T>& operator++() override;
		private:
			/// <summary> Zostavi do path_ prehliadku binarneho stromu v poradi inorder. </summary>
			/// <param name = "path"> Cesta stromom, ktoru zostavuje. </param>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* const current);
			void goToNext();
		private:
			bool isPeekReady = false; //Pomocna premenna znacujuca kedy sa ma zaradit otec na vypis
		};
	};

	template<typename T>
	inline BinaryTreeNode<T>::BinaryTreeNode(T data):
		KWayTreeNode<T, 2>(data)
	{
	}

	template<typename T>
	inline BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& other):
		KWayTreeNode<T, 2>(other)
	{
	}

	template<typename T>
	inline TreeNode<T>* BinaryTreeNode<T>::shallowCopy()
	{
		return new BinaryTreeNode<T>(*this);
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getParent() const
	{
		return dynamic_cast<BinaryTreeNode<T>*>(TreeNode<T>::parent_);
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getLeftSon() const
	{
		return dynamic_cast<BinaryTreeNode<T>*>(this->getSon(LEFT_SON));
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getRightSon() const
	{
		return dynamic_cast<BinaryTreeNode<T>*>(this->getSon(RIGHT_SON));
	}

	template<typename T>
	inline void BinaryTreeNode<T>::setLeftSon(BinaryTreeNode<T>* leftSon)
	{
		replaceSon(leftSon, LEFT_SON);
	}

	template<typename T>
	inline void BinaryTreeNode<T>::setRightSon(BinaryTreeNode<T>* rightSon)
	{
		replaceSon(rightSon, RIGHT_SON);
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::changeLeftSon(BinaryTreeNode<T>* leftSon)
	{
		return dynamic_cast<BinaryTreeNode<T>*>(replaceSon(leftSon, LEFT_SON));
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::changeRightSon(BinaryTreeNode<T>* rightSon)
	{
		return dynamic_cast<BinaryTreeNode<T>*>(replaceSon(rightSon, RIGHT_SON));
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isLeftSon() const
	{
		return TreeNode<T>::parent_ != nullptr && getParent()->getLeftSon() == nullptr;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isRightSon() const
	{
		return TreeNode<T>::parent_ != nullptr && getParent()->getRightSon() == nullptr;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::hasLeftSon() const
	{
		return getLeftSon() != nullptr;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::hasRightSon() const
	{
		return getRightSon() != nullptr;
	}

	template<typename T>
	inline BinaryTree<T>::BinaryTree():
		KWayTree<T, 2>()
	{
	}

	template<typename T>
	inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& other):
		KWayTree<T, 2>(other)
	{
	}

	template<typename T>
	inline Structure * BinaryTree<T>::clone() const
	{
		return new BinaryTree<T>(*this);
	}

	template<typename T>
	inline TreeNode<T>* BinaryTree<T>::createTreeNodeInstance()
	{
		T data = T();
		return new BinaryTreeNode<T>(data);
	}

	template<typename T>
	inline Iterator<T>* BinaryTree<T>::getBeginIterator() const
	{
		return new InOrderTreeIterator(Tree<T>::root_);
	}

	template<typename T>
	inline Iterator<T>* BinaryTree<T>::getEndIterator() const
	{
		return new InOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline BinaryTree<T>::InOrderTreeIterator::InOrderTreeIterator(TreeNode<T>* const startNode):
		TreeIterator()
	{
		/*populatePath(startNode);*/
		if (startNode != nullptr) {
			TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(startNode, 0));
			goToNext();
		}
	}

	template<typename T>
	inline Iterator<T>& BinaryTree<T>::InOrderTreeIterator::operator++()
	{
		goToNext();
		return *this;
	}

	template<typename T>
	inline void BinaryTree<T>::InOrderTreeIterator::populatePath(TreeNode<T>* const current)
	{
		if (current != nullptr)
		{
			BinaryTreeNode<T>* curBinTreeNode = dynamic_cast<BinaryTreeNode<T>*>(current);
			populatePath(curBinTreeNode->getLeftSon());
			TreeIterator::path_->push(current);
			populatePath(curBinTreeNode->getRightSon());
		}
	}

	template<typename T>
	inline void BinaryTree<T>::InOrderTreeIterator::goToNext()
	{
		if (TreeIterator::sstack->size() == 0)
		{
			return;
		}

		if (TreeIterator::sstack->peek()->getIndex() == -1)
		{
			delete TreeIterator::sstack->pop();

			if (TreeIterator::sstack->size() == 0)
			{
				return;
			} 
			TreeIterator::sstack->peek()->getIndex()++;

			while (TreeIterator::sstack->peek()->getIndex() == 2)
			{
				delete TreeIterator::sstack->pop();
				if (TreeIterator::sstack->size() == 0)
				{
					return;
				}
				TreeIterator::sstack->peek()->getIndex()++;
			}

			int in = TreeIterator::sstack->peek()->getIndex();
			isPeekReady = in == 1;
		}

		int top = TreeIterator::sstack->peek()->accessData()->degree();
		int indeex = TreeIterator::sstack->peek()->getIndex();
		 
		if (indeex < top)
		{
			if (isPeekReady)
			{
				isPeekReady = false;
				return;
			}
			Ramec<TreeNode<T>*>* ram = TreeIterator::sstack->peek();
			TreeNode<T>* item = ram->accessData()->getSon(ram->getIndex());
			if (item != nullptr)
			{
				TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(item, 0));
			}
			else if (item == nullptr && ram->getIndex() == 0 && ram->accessData()->getSon(1) != nullptr)
			{
				TreeIterator::sstack->peek()->getIndex()++;
				return;
			}
			else
			{
				TreeIterator::sstack->peek()->getIndex()++;
			}
			return goToNext();
		}
		else
		{
			TreeIterator::sstack->peek()->getIndex() = -1;
		}
	}

}

