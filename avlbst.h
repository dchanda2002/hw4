#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void insert_fix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node);
		void remove_fix(AVLNode<Key, Value>* node, int8_t diff);
		void rotateLeft(AVLNode<Key, Value>* node);
		void rotateRight(AVLNode<Key, Value>* node);
		AVLNode<Key, Value>* AVLcast(Node<Key, Value>* node);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
		Key key = new_item.first;
		Value value = new_item.second;

		//If the AVL Tree is empty, create a root node
		if(AVLcast(this->root_) == NULL){
			AVLNode<Key, Value>* newValue = new AVLNode<Key, Value>(key, value, NULL);
			this->root_ = newValue;
			return;
		}

		//If the key is already in the AVL Tree, change it
		AVLNode<Key, Value>* curr = AVLcast(this->internalFind(key));
		if(curr != NULL){
			curr->setValue(value);
			return;
		}

		//Otherwise, start at the root and traverse until you get 
		//to the right spot (a leaf node). Then, insert.
		curr = AVLcast(this->root_);
		AVLNode<Key, Value>* next = NULL;
		while(curr != NULL){
			if(key < curr->getKey()){
				next = curr->getLeft();
				if(next == NULL){
					AVLNode<Key, Value>* newValue = new AVLNode<Key, Value>(key, value, curr);
					curr->setLeft(newValue);
					curr = newValue;
					break;
				}
			} else {
				next = curr->getRight();
				if(next == NULL){
					AVLNode<Key, Value>* newValue = new AVLNode<Key, Value>(key, value, curr);
					curr->setRight(newValue);
					curr = newValue;
					break;
				}
			}
			curr = next;
		}	

		//Balance the subtree (parent and child)
		//and decide whether or not insert_fix()
		//needs to be called
		AVLNode<Key, Value>* parentNode = curr->getParent();
		int8_t parentBalance = parentNode->getBalance();
		
		if(parentBalance != 0){
			parentNode->setBalance(0);
		} else {
			if(parentNode->getLeft() == curr){
				parentNode->setBalance(-1);
			} else {
				parentNode->setBalance(1);
			}

			//call insert_fix to rotate the tree if necessary.
			insert_fix(parentNode, curr);
		}

}

/* 
* Helper function for insert() function, used to fix the 
* balance of the tree and perfrom necessary rotations
* after an insert
*/
template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node){
	
		//do nothing if either parent or granparent are NULL
		if(parent == NULL){
			return;
		}

		AVLNode<Key, Value>* grandparent = parent->getParent(); 
		if(grandparent == NULL){
			return;
		}

		//Perform different operations depending on whether parent
		//is a left or right child of grandparent
		if(grandparent->getLeft() == parent){
			grandparent->updateBalance(-1);
			int8_t gpBal = grandparent->getBalance();
			if(gpBal == 0){ //do nothing if grandparent is balanced
				return;
			} else if (gpBal == -1){ //recursively call insert_fix one level up
				insert_fix(grandparent, parent);
			} else if (gpBal == -2){ //need to perform rotations; unbalanced.
				if(parent->getLeft() == node){
					rotateRight(grandparent);
					parent->setBalance(0);
					grandparent->setBalance(0);
				} else {
					rotateLeft(parent);
					rotateRight(grandparent);
					int8_t nodeBal = node->getBalance();
					if(nodeBal == -1){
						parent->setBalance(0);
						grandparent->setBalance(1);
					} else if (nodeBal == 1){
						parent->setBalance(-1);
						grandparent->setBalance(0);
					} else {
						parent->setBalance(0);
						grandparent->setBalance(0);
					}
					node->setBalance(0);
				}
			}
		} else { //similar analogous logic applies if parent is a right child
			grandparent->updateBalance(1);
			int8_t gpBal = grandparent->getBalance();
			if(gpBal == 0){
				return;
			} else if (gpBal == 1){
				insert_fix(grandparent, parent);
			} else if (gpBal == 2){
				if(parent->getRight() == node){
					rotateLeft(grandparent);
					parent->setBalance(0);
					grandparent->setBalance(0);
				} else {
					rotateRight(parent);
					rotateLeft(grandparent);
					int8_t nodeBal = node->getBalance();
					if(nodeBal == 1){
						parent->setBalance(0);
						grandparent->setBalance(-1);
					} else if (nodeBal == -1){
						parent->setBalance(1);
						grandparent->setBalance(0);
					} else {
						parent->setBalance(0);
						grandparent->setBalance(0);
					}
					node->setBalance(0);
				}
			}
		}

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO

		//If an item with the key is not in the AVLtree, do nothing.
		AVLNode<Key, Value>* removal_item = AVLcast(this->internalFind(key));
		if(removal_item == NULL){
			return;
		}

		//store the pointers to other nodes.
		AVLNode<Key, Value>* left_child = removal_item->getLeft();
		AVLNode<Key, Value>* right_child = removal_item->getRight();
		AVLNode<Key, Value>* parent = removal_item->getParent();

		//Handle the case when there are two children. Swap with
		//the predecessor and then update the temporary pointers 
		//made.
		if(left_child != NULL && right_child != NULL){
			AVLNode<Key, Value>* pred = AVLcast(this->predecessor(removal_item));
			if(pred == NULL){
				return;
			}
			nodeSwap(removal_item, pred);
			left_child = removal_item->getLeft();
			right_child = removal_item->getRight();
			parent = removal_item->getParent();
		}

		//store diff for the call to remove_fix later.
		int8_t diff = 0;
		if(parent != NULL){
			if(parent->getLeft() == removal_item){
				diff = 1;
			} else {
				diff = -1;
			}
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
				this->root_ = NULL;
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

		//call remove_fix to fix balances and rotate if necessary.
		remove_fix(parent, diff);

}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key, Value>* node, int8_t diff){
	
	//do nothing if the node is NULL
	if(node == NULL){
		return;
	}

	//calculate ndiff (next difference) if the parent is not NULL
	AVLNode<Key, Value>* p = node->getParent();
	int8_t ndiff = 0;
	if(p != NULL){
		if(p->getLeft() == node){	
			ndiff = 1;
		} else {
			ndiff = -1;
		}
	}

	//Decide what to do depending on what nodeBalance + diff is
	//diff is multiplied by numbers so that both the right child
	//and left child cases are handled at once.
	int8_t nodeBalance = node->getBalance();
	if(nodeBalance + diff == diff * 2){ //imbalance. Eiher zig-zig or zig-zag
		AVLNode<Key, Value>* child = NULL;
		if(diff < 0){
			child = node->getLeft();
		} else {
			child = node->getRight();
		}

		int8_t childBal = child->getBalance();
		if(childBal == diff * 1){ //zig-zig
			if(diff < 0){
				rotateRight(node);
			} else {
				rotateLeft(node);
			}
			node->setBalance(0);
			child->setBalance(0);
			remove_fix(p, ndiff);
			//Recurses.
		} else if (childBal == 0){ //zig-zig
			if(diff < 0){
				rotateRight(node);
			} else {
				rotateLeft(node);
			}
			node->setBalance(diff * 1);
			child->setBalance(diff* -1);
			//Done.
		} else { //zig-zag
			AVLNode<Key, Value>* g = NULL;
			if(diff < 0){
				g = child->getRight();
				rotateLeft(child);
				rotateRight(node);
			} else {
				g = child->getLeft();
				rotateRight(child);
				rotateLeft(node);
			}
			int8_t gnBalance = g->getBalance();
			if(gnBalance == diff * -1){
				node->setBalance(0);
				child->setBalance(diff * 1);
			} else if (gnBalance == 0){
				node->setBalance(0);
				child->setBalance(0);
			} else {
				node->setBalance(diff * -1);
				child->setBalance(0);
			}
			g->setBalance(0);
			remove_fix(p, ndiff);
			//Recurses.
		}	
	} else if(nodeBalance + diff == diff * 1){ //just update balance.
		node->setBalance(diff * 1);
	} else { //if nodeBalance + diff = 0
		node->setBalance(0);
		remove_fix(p, ndiff);
		//Recurses.
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node){
	
	//do nothing if node or rightChild is NULL.
	if(node == NULL){
		return;
	}
	AVLNode<Key, Value>* rightChild = node->getRight();
	if(rightChild == NULL){
		return;
	}

	AVLNode<Key, Value>* b = rightChild->getLeft();
	AVLNode<Key, Value>* newParent = node->getParent();

	//Change all of the necessary pointers between b, newParent,
	//rightChild, and node.
	node->setRight(b);
	if(b != NULL){
		b->setParent(node);
	}
	rightChild->setLeft(node);

	rightChild->setParent(newParent);
	if(newParent == NULL){
		this->root_ = rightChild;
	} else {
		if(newParent->getRight() == node){
			newParent->setRight(rightChild);
		} else {
			newParent->setLeft(rightChild);
		}
	}
	node->setParent(rightChild);

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node){
	
	//do nothing if node or leftChild is NULL.
	if(node == NULL){
		return;
	}
	AVLNode<Key, Value>* leftChild = node->getLeft();
	if(leftChild == NULL){
		return;
	}

	AVLNode<Key, Value>* c = leftChild->getRight();
	AVLNode<Key, Value>* newParent = node->getParent();

	//Change all of the necessary pointers between c, newParent,
	//leftChild, and node.
	node->setLeft(c);
	if(c != NULL){
		c->setParent(node);
	}
	leftChild->setRight(node);

	leftChild->setParent(newParent);
	if(newParent == NULL){
		this->root_ = leftChild;
	} else {
		if(newParent->getRight() == node){
			newParent->setRight(leftChild);
		} else {
			newParent->setLeft(leftChild);
		}
	}
	node->setParent(leftChild);
	
}

template <class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::AVLcast(Node<Key, Value>* node){
	return static_cast<AVLNode<Key, Value>*>(node);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
