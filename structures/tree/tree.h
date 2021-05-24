#pragma once
#include "../heap_monitor.h"
#include "../structure.h"
#include "../structure_iterator.h"
#include "../stack/implicit_stack.h"
#include <queue>
#include <stack>
#include <stdexcept>

namespace structures
{
	template<typename T>
	class Ramec : public DataItem<T>
	{
	public:
		Ramec(T data, int index);
		~Ramec();
		int& getIndex();
		const int getIndex() const;
	private:
		int sonIndex;
	};

	/// <summary> Vrchol stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class TreeNode : public DataItem<T>
	{
	public:
		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		virtual TreeNode<T>* shallowCopy() = 0;

		/// <summary> Vytvori a vrati hlboku kopiu vrchola (teda skopiruje data a skopiruje celu stromovu strukturu). </summary>
		/// <returns> Hlboka kopia vrchola. </returns>
		virtual TreeNode<T>* deepCopy();

		/// <summary> Test, ci je koren. </summary>
		/// <returns> true, ak je koren, false inak. </returns>
		bool isRoot();
    
		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		virtual bool isLeaf() = 0;
  
		/// <summary> Spristupni rodica vrcholu. </summary>
		/// <returns> Rodic vrcholu. </returns>
		TreeNode<T>* getParent() const;

		/// <summary> Nastavi rodica na nullptr. </summary>
		void resetParent();
    
		/// <summary> Zmeni rodica vrcholu. </summary>
		/// <param name = "parent"> Novy rodic vrcholu. </param>
		void setParent(TreeNode<T>* parent);

		/// <summary> Spristupni brata vrcholu podla jeho pozicie u spolocneho rodica. </summary>
		/// <param name = "brothersOrder"> Poradie brata u rodica. </param>
		/// <exception cref=""> Vyhodena, ak je korenom. </exception>  
		/// <returns> Brat vrcholu. </returns>
		virtual TreeNode<T>* getBrother(int brothersOrder);
    
		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		virtual TreeNode<T>* getSon(int order) const = 0;
    
		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks> 
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov. 
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. 
		/// </remarks>
		virtual void insertSon(TreeNode<T>* son, int order) = 0;
    
		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		virtual TreeNode<T>* replaceSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks> 
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov. 
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. 
		/// </remarks>
		virtual TreeNode<T>* removeSon(int order) = 0;
    
		/// <summary> Vrati stupen vrcholu. </summary>
		/// <returns> Stupen vrcholu. </returns>
		virtual int degree() = 0;   

		/// <summary> Vrati pocet vrcholov v podstrome. </summary>
		/// <returns> Pocet vrcholov v podstrome. </returns>
		virtual size_t sizeOfSubtree();
	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		TreeNode(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol stromu, z ktoreho sa prevezmu vlastnosti. </param>
		TreeNode(const TreeNode<T>& other);
    
		/// <summary> Odkaz na rodica. </summary>
		TreeNode<T>* parent_;  
	};

	/// <summary> Strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T> 
	class Tree : public Structure, public Iterable<T>
	{
	public:
		/// <summary> Destruktor. </summary>
		~Tree();
  
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const = 0;
    
		/// <summary> Zisti, ci je struktura prazdna. </summary>
		/// <returns> true, ak je struktura prazdna, false inak. </returns>
		bool isEmpty() const override; 

		/// <summary> Vrati pocet vrcholov v strome. </summary>
		/// <returns> Pocet vrcholov v strome. </returns>
		virtual size_t size() const;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (strom), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento strom nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je strom. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Strom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento strom nachadza po priradeni. </returns>
		virtual Tree<T>& operator=(const Tree<T>& other);
		
		/// <summary> Vymaze strom. </summary>
		virtual void clear();
    
		/// <summary> Spristupni koren stromu. </summary>
		/// <returns> Koren stromu. </returns>
		TreeNode<T>* getRoot();
    
		/// <summary> Nahradi koren stromu. </summary>
		/// <param name = "newRoot">  Novy koren stromu. </param>
		/// <returns> Povodny koren stromu. </returns>
		virtual TreeNode<T>* replaceRoot(TreeNode<T>* newRoot);

		/// <summary> Vytvori a vrati instanciu vrcholu stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu stromu. </returns>
		/// <remarks> 
		/// Kazdy strom spravuje vrcholy ineho typu, mali by vsak byt jednotne v celom strome. 
		/// Tato tovarenska metoda by mala byt pretazena v kazdom potomkovi stromu tak, aby vracala vrcholy, ktore ten strom ocakava.
		/// Instance vrcholov by mali byt vytvarane vyhradne pomocou tejto metody.
		/// </remarks>
		virtual TreeNode<T>* createTreeNodeInstance() = 0;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	protected:
		/// <summary> Konstruktor. </summary>
		Tree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Stromu, z ktoreho sa prevezmu vlastnosti. </param>
		Tree(const Tree<T>& other);
    
		/// <summary> Koren stromu. </summary>
		TreeNode<T>* root_;

	protected:
		/// <summary> Iterator pre Tree. </summary>
		class TreeIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			TreeIterator();

			/// <summary> Destruktor. </summary>
			~TreeIterator();

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
		protected:
			/// <summary> Prehliadka stromu. </summary>
			std::queue<TreeNode<T>*>* path_;
			ImplicitStack<Ramec<TreeNode<T>*>*>* sstack;
		};

	public:
		class PreOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PreOrderTreeIterator(TreeNode<T>* const startNode);

			Iterator<T>& operator++() override;
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi preorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* const current);
			void goToNext();
		};

		class PostOrderTreeIterator: public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PostOrderTreeIterator(TreeNode<T>* const startNode);

			Iterator<T>& operator++() override;
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi postorder. </summary>
			/// <param name = "path"> Cesta stromom, ktoru zostavuje. </param>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* const current);
			void goToNext();
		};

		class LevelOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			LevelOrderTreeIterator(TreeNode<T>* const startNode);

			Iterator<T>& operator++() override;
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi levelorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* const current);
			void goToNext();
		private:
			int currentLevel;
			int startLevel;
			bool isEnd;
		};
	};

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::deepCopy()
	{
		TreeNode<T>* result = shallowCopy();

		for (int i = 0; i < degree(); i++) {
			TreeNode<T>* son = getSon(i);
			if (son != nullptr)
			{
				result->replaceSon(son->deepCopy(), i);
			}
		}

		return result;
	}

	template<typename T>
	inline bool TreeNode<T>::isRoot()
	{
		return parent_ == nullptr;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getParent() const
	{
		return parent_;
	}

	template<typename T>
	inline void TreeNode<T>::resetParent()
	{
		parent_ = nullptr;
	}

	template<typename T>
	inline void TreeNode<T>::setParent(TreeNode<T>* parent)
	{
		parent_ = parent;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getBrother(int brothersOrder)
	{
		if (isRoot())
		{
			throw std::logic_error("Node is root!");
		}
		else 
		{
			return parent_->getSon(brothersOrder);
		}
	}

	template<typename T>
	inline size_t TreeNode<T>::sizeOfSubtree()
	{
		size_t result = 1;

		for (int i = 0; i < degree(); i++) {
			TreeNode<T>* son = getSon(i);
			if (son != nullptr)
			{
				result += son->sizeOfSubtree();
			}
		}

		return result;
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(T data):
		DataItem<T>(data),
		parent_(nullptr)
	{
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(const TreeNode<T>& other):
		DataItem<T>(other),
		parent_(other.parent_)
	{
	}
  
	template<typename T>
	inline Tree<T>::~Tree()
	{
		clear();
	}

	template<typename T>
	inline bool Tree<T>::isEmpty() const
	{
		return root_ == nullptr;
	}

	template<typename T>
	inline size_t Tree<T>::size() const
	{
		return root_ == nullptr ? 0 : root_->sizeOfSubtree();
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getBeginIterator() const
	{
		return new PreOrderTreeIterator(root_);
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getEndIterator() const
	{
		return new PreOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline Tree<T>::Tree():
		Structure(),
		Iterable<T>(),
		root_(nullptr)    
	{
	}

	template<typename T>
	inline Tree<T>::Tree(const Tree<T>& other):
		Tree<T>()
	{
		*this = other;
	}

	template<typename T>
	inline Structure & Tree<T>::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Tree<T>&>(other);
		}
		return *this;
	}
  
	template<typename T>
	inline Tree<T>& Tree<T>::operator=(const Tree<T>& other)
	{
		if (this != &other)
		{
			clear();
			if (other.root_ != nullptr)
			{
				root_ = other.root_->deepCopy();
			}
		}
		return *this;
	}

	template<typename T>
	inline void Tree<T>::clear()
	{
		delete root_;
		root_ = nullptr;
	}
  
	template<typename T>
	inline TreeNode<T>* Tree<T>::getRoot()
	{
		return root_;
	}
  
	template<typename T>             
	inline TreeNode<T>* Tree<T>::replaceRoot(TreeNode<T>* newRoot)
	{
		TreeNode<T>* pom = root_;
		root_ = newRoot;
		return pom;
	}

	template<typename T>
	inline Tree<T>::TreeIterator::TreeIterator():
		Iterator<T>(),
		path_(new std::queue<TreeNode<T>*>()),
		sstack(new ImplicitStack<Ramec<TreeNode<T>*>*>())
	{
	}

	template<typename T>
	inline Tree<T>::TreeIterator::~TreeIterator()
	{
		delete path_;
		while (sstack->size() != 0)
		{
			delete sstack->pop();
		}
		delete sstack;
		path_ = nullptr;
		sstack = nullptr;
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator=(const Iterator<T>& other)
	{
		*path_ = *dynamic_cast<const TreeIterator&>(other).path_;
		const ImplicitStack<Ramec<TreeNode<T>*>*>* stack2 = dynamic_cast<const TreeIterator&>(other).sstack;
		while (sstack->size() != 0)
		{
			delete sstack->pop();
		}
		sstack->operator=(*stack2);
		return *this;
	}

	template<typename T>
	inline bool Tree<T>::TreeIterator::operator!=(const Iterator<T>& other)
	{
		//return *path_ != *dynamic_cast<const TreeIterator&>(other).path_;

		const ImplicitStack<Ramec<TreeNode<T>*>*>* stack2 = dynamic_cast<const TreeIterator&>(other).sstack;
		return sstack->operator!=(*stack2); //Doimplementovane v ostatnych podstrukturach
	}

	template<typename T>
	inline const T Tree<T>::TreeIterator::operator*()
	{
		//return path_->front()->accessData();
		return sstack->peek()->accessData()->accessData();
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator++()
	{
		path_->pop();
		return *this;
	}

	template<typename T>
	inline Tree<T>::PreOrderTreeIterator::PreOrderTreeIterator(TreeNode<T>* const startNode):
		TreeIterator()
	{
		/*populatePath(startNode);*/
		if (startNode != nullptr) {
			TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(startNode, 0));
		}
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::PreOrderTreeIterator::operator++()
	{
		goToNext();
		return *this;
	}

	template<typename T>
	inline void Tree<T>::PreOrderTreeIterator::populatePath(TreeNode<T>* const current)
	{
		if (current != nullptr)
		{
			TreeIterator::path_->push(current);

			for (int i = 0; i < current->degree(); i++)
			{
				populatePath(current->getSon(i));
			}
		}
	}

	template<typename T>
	inline void Tree<T>::PreOrderTreeIterator::goToNext()
	{
		if (TreeIterator::sstack->size() == 0)
		{
			return;
		}

		int top = TreeIterator::sstack->peek()->accessData()->degree();
		int indeex = TreeIterator::sstack->peek()->getIndex();
		if (indeex < top)
		{
			Ramec<TreeNode<T>*>* ram = TreeIterator::sstack->peek();
			TreeNode<T>* item = ram->accessData()->getSon(ram->getIndex());
			if (item != nullptr)
			{
				ram->getIndex()++;
				TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(item, 0));
			}
			else
			{
				ram->getIndex()++;
				return goToNext();
			}
		}
		else
		{
			Ramec<TreeNode<T>*>* ram = TreeIterator::sstack->pop();
			delete ram;

			if (TreeIterator::sstack->size() == 0)
			{
				return;
			}

			return goToNext();
		}
	}

	template<typename T>
	inline Tree<T>::PostOrderTreeIterator::PostOrderTreeIterator(TreeNode<T>* const startNode) :
		TreeIterator()
	{
		/*populatePath(startNode);*/
		if (startNode != nullptr) {
			TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(startNode, 0));
			goToNext();
		}
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::PostOrderTreeIterator::operator++()
	{
		goToNext();
		return *this;
	}

	template<typename T>
	inline void Tree<T>::PostOrderTreeIterator::populatePath(TreeNode<T>* const current)
	{
		if (current != nullptr)
		{
			for (int i = 0; i < current->degree(); i++)
			{
				populatePath(current->getSon(i));
			}
			TreeIterator::path_->push(current);
		}
	}

	template<typename T>
	inline void Tree<T>::PostOrderTreeIterator::goToNext()
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
		}

		int top = TreeIterator::sstack->peek()->accessData()->degree();
		int indeex = TreeIterator::sstack->peek()->getIndex();
		if (indeex < top)
		{
			Ramec<TreeNode<T>*>* ram = TreeIterator::sstack->peek();
			TreeNode<T>* item = ram->accessData()->getSon(ram->getIndex());
			if (item != nullptr)
			{
				TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(item, 0));
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

	template<typename T>
	inline Tree<T>::LevelOrderTreeIterator::LevelOrderTreeIterator(TreeNode<T>* const startNode) :
		TreeIterator(),
		startLevel(0),
		currentLevel(0),
		isEnd(false)
	{
		//populatePath(startNode);
		if (startNode != nullptr) {
			TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(startNode, 0));
		}
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::LevelOrderTreeIterator::operator++()
	{
		if (currentLevel != 0)
		{
			delete TreeIterator::sstack->pop();
			startLevel--;
		}

		goToNext();
		return *this;
	}

	template<typename T>
	inline void Tree<T>::LevelOrderTreeIterator::populatePath(TreeNode<T>* const current)
	{
		if (current != nullptr)
		{
			TreeIterator::path_->push(current);
			for (int i = 0; i < current->degree(); i++)
			{
				TreeNode<T>* son = current->getSon(i);
				if (son != nullptr)
				{
					TreeIterator::path_->push(son);
				}
			}

			for (int i = 0; i < current->degree(); i++)
			{
				TreeNode<T>* son = current->getSon(i);
				if (son != nullptr)
				{
					for (int i = 0; i < son->degree(); i++)
					{
						TreeNode<T>* son2 = son->getSon(i);
						if (son2 != nullptr)
						{
							populatePath(son2);
						}
					}
				}
			}
		}
	}

	template<typename T>
	inline void Tree<T>::LevelOrderTreeIterator::goToNext()
	{ 
		if (TreeIterator::sstack->size() == 0)
		{
			return;
		}

		if (TreeIterator::sstack->size() == 1 && TreeIterator::sstack->peek()->getIndex() == 0)
		{
			currentLevel++;
		}
		else if (TreeIterator::sstack->size() == 1 && TreeIterator::sstack->peek()->getIndex() >= TreeIterator::sstack->peek()->accessData()->degree())
		{
			if (isEnd)
			{
				delete TreeIterator::sstack->pop();
				return;
			}
			currentLevel++;
			TreeIterator::sstack->peek()->getIndex() = 0;
			isEnd = false;
		}

		int top = TreeIterator::sstack->peek()->accessData()->degree();
		int indeex = TreeIterator::sstack->peek()->getIndex();
		if (indeex < top)
		{
			Ramec<TreeNode<T>*>* ram = TreeIterator::sstack->peek();
			TreeNode<T>* item = ram->accessData()->getSon(ram->getIndex());
			ram->getIndex()++;
			if (item != nullptr)
			{
				TreeIterator::sstack->push(new Ramec<TreeNode<T>*>(item, 0));
				startLevel++;
				if (startLevel != currentLevel)
				{					
					return goToNext();
				}
			}
			else
			{
				if (ram->getIndex() == ram->accessData()->degree())
				{
					isEnd = true;
				}
				return goToNext();
			}
		} 
		else
		{
			delete TreeIterator::sstack->pop();
			startLevel--;
			return goToNext();
		}

	}

	template<typename T>
	inline Ramec<T>::Ramec(T data, int index) :
		DataItem<T>(data),
		sonIndex(index)
	{
	}

	template<typename T>
	inline Ramec<T>::~Ramec()
	{
	}
	template<typename T>
	inline int& Ramec<T>::getIndex()
	{
		return sonIndex;
	}
	template<typename T>
	inline const int Ramec<T>::getIndex() const
	{
		return sonIndex;
	}
}

