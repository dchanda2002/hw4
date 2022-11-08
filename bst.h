#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		static void successor(Node <Key, Value>*& current);
		int calculateHeightIfBalanced(Node<Key, Value>* root_node) const;
		void clearHelper(Node<Key, Value>* curr);
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) :
	current_(ptr)
{
    // TODO
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() :
	current_(NULL)
{
    // TODO
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		Node<Key, Value>* thisNode = this->current_;
		Node<Key, Value>* rhsNode = rhs.current_;

		//if both are NULL return true. If only one is NULL, return
		//false before it reaches the next few lines and causes
		//an error.
		if(thisNode == NULL || rhsNode == NULL){
			if(thisNode == NULL && rhsNode == NULL){
				return true;
			}
			return false;
		}
		
		if(thisNode->getKey() == rhsNode->getKey() && thisNode->getValue() == rhsNode->getValue()){
			return true;
		}
		return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		return !(*this == rhs);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		successor(current_);
		return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() :
	root_(NULL)
{
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
		Key key = keyValuePair.first;
		Value value = keyValuePair.second;

		//If the bst is empty, create a root node
		if(root_ == NULL){
			Node<Key, Value>* newValue = new Node<Key, Value>(key, value, NULL);
			root_ = newValue;
			return;
		}

		//If the key is already in the BST, change it
		Node<Key, Value>* curr = internalFind(key);
		if(curr != NULL){
			curr->setValue(value);
			return;
		}

		//Otherwise, start at the root and traverse until you get 
		//to the right spot (a leaf node). Then, insert.
		curr = root_;
		Node<Key, Value>* next = NULL;
		while(curr != NULL){
			if(key < curr->getKey()){
				next = curr->getLeft();
				if(next == NULL){
					Node<Key, Value>* newValue = new Node<Key, Value>(key, value, curr);
					curr->setLeft(newValue);
				}
			} else {
				next = curr->getRight();
				if(next == NULL){
					Node<Key, Value>* newValue = new Node<Key, Value>(key, value, curr);
					curr->setRight(newValue);
				}
			}
			curr = next;
		}	
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

		//If an item with the key is not in the bst, do nothing.
		Node<Key, Value>* removal_item = internalFind(key);
		if(removal_item == NULL){
			return;
		}

		//store the pointers to other nodes.
		Node<Key, Value>* left_child = removal_item->getLeft();
		Node<Key, Value>* right_child = removal_item->getRight();
		Node<Key, Value>* parent = removal_item->getParent();

		//Handle the case when there are two children. Swap with
		//the predecessor and then update the temporary pointers 
		//made.
		if(left_child != NULL && right_child != NULL){
			Node<Key, Value>* pred = predecessor(removal_item);
			if(pred == NULL){
				return;
			}
			nodeSwap(removal_item, pred);
			left_child = removal_item->getLeft();
			right_child = removal_item->getRight();
			parent = removal_item->getParent();
		}

		//Now, handle the case where it has one or no children.
		//This includes the case where swapping with the predecessor
		//has generated one of these two cases. 

		//If one child, then swap with the item to be removed and
		//update all pointers as necessary so that the bst completely
		//excludes the removed item. Then, delete that node.
		if(left_child != NULL){
			nodeSwap(removal_item, left_child);
			left_child->setLeft(removal_item->getLeft());
			left_child->setRight(removal_item->getRight());
			if(left_child->getLeft() != NULL){
				left_child->getLeft()->setParent(left_child);
			}
			if(left_child->getRight() != NULL){
				left_child->getRight()->setParent(left_child);
			}
			delete removal_item;
		} else if (right_child != NULL){
			nodeSwap(removal_item, right_child);
			right_child->setLeft(removal_item->getLeft());
			right_child->setRight(removal_item->getRight());
			if(right_child->getLeft() != NULL){
				right_child->getLeft()->setParent(right_child);
			}
			if(right_child->getRight() != NULL){
				right_child->getRight()->setParent(right_child);
			}
			delete removal_item;
		} else {

			//If a leaf node has NULL as a parent, it is the root. 
			//Update the tree such that it becomes empty.
			if(parent == NULL){
				delete removal_item;
				root_ = NULL;
				return;
			}

			//If it is a leaf node, update the parent node's left
			//or right node so that they point to NULL where the leaf
			//node once was.
			if(removal_item == parent->getLeft()){
				parent->setLeft(NULL);
			} else {
				parent->setRight(NULL);
			}
			delete removal_item;
		}
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

		//If there is a left subtree, find the rightmost node
		//on that subtree and return it.
		if(current->getLeft() != NULL){
			current = current->getLeft();
			while(current->getRight() != NULL){
				current = current->getRight();
			}
			return current;
		}

		Node<Key, Value>* parent = current->getParent();

		/* If there is not a left subtree, go up until one of the following
		* is true:
		* 
		* The parent of the node being observed is NULL (hence it
		* cannot be the predecessor)
		*
		* OR
		*
		* The node is to the right of its parent, in which case that
		* parent is the predecessor.
		*/
		while(!(parent == NULL || parent->getRight() == current)){
			current = current->getParent();
			parent = parent->getParent();
		}
		return parent;

}

/*
*	successor() method to find the succeeding node easily. It is written
* differently (updating the current node by reference) since the
* iterator class uses it.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::successor(Node<Key, Value>*& current)
{
    // TODO

		Node<Key, Value>* temp = current;

		//If there is a right subtree, find the leftmost node
		//on that subtree and return it.
		if(temp->getRight() != NULL){
			temp = temp->getRight();
			while(temp->getLeft() != NULL){
				temp = temp->getLeft();
			}
			current = temp;
			return;
		}

		Node<Key, Value>* parent = temp->getParent();

		/* If there is not a right subtree, go up until one of the following
		* is true:
		* 
		* The parent of the node being observed is NULL (hence it
		* cannot be the successor)
		*
		* OR
		*
		* The node is to the left of its parent, in which case that
		* parent is the successor.
		*/
		while(!(parent == NULL || parent->getLeft() == temp)){
			temp = temp->getParent();
			parent = parent->getParent();
		}
		current = parent;
		return;

}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO

		//If the bst is empty, do nothing.
		if(root_ == NULL){
			return;
		}
		
		//Otherwise, call the helper function on the root node
		//and then set the root equal to NULL once complete.
		clearHelper(root_);
		root_ = NULL;

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* curr){

	//If it is a leaf node, remove that Node pointer.
	if(curr->getLeft() == NULL && curr->getRight() == NULL){
		delete curr;
		return;
	}

	//If it has a left value, call clearHelper() on it.
	if(curr->getLeft() != NULL){
		clearHelper(curr->getLeft());
	}

	//If it has a right value, call clearHelper() on it.
	if(curr->getRight() != NULL){
		clearHelper(curr->getRight());
	}

	//At each level, once its left and right subtrees are empty,
	//you can delete that Node pointer.
	delete curr;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

		Node<Key, Value>* smallest = root_;

		//If the bst is empty, return NULL.
		if(smallest == NULL){
			return NULL;
		}

		//Find the leftmost value in the bst and return it.
		while(smallest->getLeft() != NULL){
			smallest = smallest->getLeft();
		}
		return smallest;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		Node<Key, Value>* current = root_;

		//If the bst is empty, return NULL.
		if(current == NULL){
			return NULL;
		}

		//Traverse the list using bst properties until you get the
		//item with the key and return it. If you never get to it
		//you're at a leaf node, return NULL.
		while(current->getKey() != key){
			if(key < current->getKey()){
				current = current->getLeft();
			} else {
				current = current->getRight();
			}
			if(current == NULL){
				return NULL;
			}
		}
		return current;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO

		//If the helper function returns -1, it means the tree wasn't
		//balanced. Otherwise, it was.
		if(calculateHeightIfBalanced(root_) == -1){
			return false;
		}
		return true;
}

/*
* Helper function for isBalanced()
*/
template<typename Key, typename Value>
int BinarySearchTree<Key,Value>::calculateHeightIfBalanced(Node<Key, Value>* root_node) const{

		// Base case, if its empty
		if(root_node == NULL){
			return 0;
		} 

		// if at least one tree is not balanced immediately return -1.
		// if the current tree is not balanced, return -1.
		// if they are balanced, return their respective heights.

		int leftHeight = calculateHeightIfBalanced(root_node->getLeft());
		int rightHeight = calculateHeightIfBalanced(root_node->getRight());
		if(leftHeight >= 0 && rightHeight >= 0){
			if (abs(leftHeight - rightHeight) <= 1){
				if(leftHeight > rightHeight){
					return leftHeight + 1;
				} 
				return rightHeight + 1;
			}
		} 
		return -1;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
