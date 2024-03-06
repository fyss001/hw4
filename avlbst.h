#ifndef AVLBST_H
#define AVLBST_H

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
* An explicit constructor to initialize the elements by calling the base class constructor
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
    //AVLTree();
    //~AVLTree();
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insert_fix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    void remove_fix(AVLNode<Key, Value>* n, int8_t diff);
    void rightRotate(AVLNode<Key, Value>* p);
    void leftRotate(AVLNode<Key, Value>* p);


};

template<class Key, class Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* p){
    if(static_cast<AVLNode<Key, Value>*>(this->root_)==p){
        this->root_=p->getLeft();
        p->setLeft(this->root_->getRight());
        if(this->root_->getRight()){
            this->root_->getRight()->setParent(p);
        }
        this->root_->setParent(nullptr);
        this->root_->setRight(p);
        p->setParent(static_cast<AVLNode<Key, Value>*>(this->root_));
        return;
    }
    
    AVLNode<Key, Value>* g=p->getParent();
    if(p==g->getLeft()){
        g->setLeft(p->getLeft());
        p->setParent(p->getLeft());
        p->setLeft(g->getLeft()->getRight());
        if(g->getLeft()->getRight()) g->getLeft()->getRight()->setParent(p);
        g->getLeft()->setParent(g);
        g->getLeft()->setRight(p);
    }else{
        g->setRight(p->getLeft());
        p->setParent(p->getLeft());
        p->setLeft(g->getRight()->getRight());
        if(g->getRight()->getRight()) g->getRight()->getRight()->setParent(p);
        g->getRight()->setParent(g);
        g->getRight()->setRight(p);
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* p){
    if(static_cast<AVLNode<Key, Value>*>(this->root_)==p){
        this->root_=p->getRight();
        p->setRight(this->root_->getLeft());
        if(this->root_->getLeft()) this->root_->getLeft()->setParent(p);
        this->root_->setParent(nullptr);
        this->root_->setLeft(p);
        p->setParent(static_cast<AVLNode<Key, Value>*>(this->root_));
        return;
    }
    AVLNode<Key, Value>* g=p->getParent();
    if(p==g->getRight()){
        g->setRight(p->getRight());
        p->setParent(p->getRight());
        p->setRight(g->getRight()->getLeft());
        if(g->getRight()->getLeft()) g->getRight()->getLeft()->setParent(p);
        g->getRight()->setParent(g);
        g->getRight()->setLeft(p);
        
    }else{
        g->setLeft(p->getRight());
        p->setParent(p->getRight());
        p->setRight(g->getLeft()->getLeft());
        if(g->getLeft()->getLeft()) g->getLeft()->getLeft()->setParent(p);
        g->getLeft()->setParent(g);
        g->getLeft()->setLeft(p);
    }
    return;
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(!this->root_){
        this->root_ = new AVLNode<Key, Value>(new_item.first,new_item.second,nullptr);
        return;
    }
    AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    bool inserted_at_left=1;
    while(temp){
        if(temp->getKey()==new_item.first){
            temp->setValue(new_item.second);
            return;
        }
        if(temp->getKey()>new_item.first){
            if(temp->getLeft()){
                temp=temp->getLeft();
            }else{
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first,new_item.second,temp);
                temp->setLeft(newNode);
                
                break;
            }
        }else{
            if(temp->getRight()){
                temp=temp->getRight();
            }else{
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first,new_item.second,temp);
                temp->setRight(newNode);
                inserted_at_left=0;
                break;
            }
        }
    }
    // temp now is the parent
    int8_t pbalance=temp->getBalance();
    if(pbalance!=0){
        temp->setBalance(0);
        return;
    }
    if(inserted_at_left){
        temp->setBalance(-1);
        insert_fix(temp,temp->getLeft());
    }else{
        temp->setBalance(1);
        insert_fix(temp, temp->getRight());
    }
    

    
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
    if(!p||!(p->getParent())) return;
    AVLNode<Key, Value>* g=p->getParent();
    if(p==g->getLeft()){
        g->setBalance((g->getBalance())-1);
        int8_t gbalance=g->getBalance();
        if(gbalance==0) return;
        if(gbalance==-1) insert_fix(g,p);
        if(gbalance==-2){
            if(n==p->getLeft()){
                //zig-zig
                rightRotate(g);
                g->setBalance(0);
                p->setBalance(0);
            }else{
                //zig-zag
                leftRotate(p);
                rightRotate(g);
                int8_t nbalance=n->getBalance();
                if(nbalance==0){
                    g->setBalance(0);
                    p->setBalance(0);
                }else if(nbalance==1){
                    g->setBalance(0);
                    p->setBalance(-1);
                    n->setBalance(0);
                }else if(nbalance==-1){
                    g->setBalance(1);
                    p->setBalance(0);
                    n->setBalance(0);
                }
                
            }
        }
    }else{
        g->setBalance((g->getBalance())+1);
        int8_t gbalance=g->getBalance();
        if(gbalance==0) return;
        if(gbalance==1) insert_fix(g,p);
        if(gbalance==2){
            if(n==p->getRight()){
                //zig-zig
                leftRotate(g);
                g->setBalance(0);
                p->setBalance(0);
            }else{
                //zig-zag
                rightRotate(p);
                leftRotate(g);
                int8_t nbalance=n->getBalance();
                if(nbalance==0){
                    g->setBalance(0);
                    p->setBalance(0);
                }else if(nbalance==-1){
                    g->setBalance(0);
                    p->setBalance(1);
                    n->setBalance(0);
                }else if(nbalance==1){
                    g->setBalance(-1);
                    p->setBalance(0);
                    n->setBalance(0);
                }
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
    AVLNode<Key, Value>* n=static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if(!n) return;
    if(n->getLeft() && n->getRight()){
        AVLNode<Key, Value>* pred=static_cast<AVLNode<Key, Value>*>(this->predecessor(n));
        nodeSwap(n,pred);
    }
    AVLNode<Key, Value>* p = n->getParent();
    int diff=0;
    if(p){
        if(n==p->getLeft()){
            diff=1;
            if(!n->getLeft() && !n->getRight()){
                p->setLeft(nullptr);
            }else{
                if(n->getLeft()){
                    p->setLeft(n->getLeft());
                    n->getLeft()->setParent(p);
                }else{
                    p->setLeft(n->getRight());
                    n->getRight()->setParent(p);
                }
            }
        }else{
            diff=-1;
            if(!n->getLeft() && !n->getRight()){
                p->setRight(nullptr);
            }else{
                if(n->getLeft()){
                    p->setRight(n->getLeft());
                    n->getLeft()->setParent(p);
                }else{
                    p->setRight(n->getRight());
                    n->getRight()->setParent(p);
                }
                
            }
        }
        
    }else{
        if(!n->getLeft() && !n->getRight()){
            this->root_=nullptr;
        }else{
            if(n->getLeft()){
                this->root_=n->getLeft();
                n->getLeft()->setParent(nullptr);
            }else{
                this->root_=n->getRight();
                n->getRight()->setParent(nullptr);
            }
        }
    }
    
    delete n;
    remove_fix(p, diff);

}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key, Value>* n, int8_t diff)
{
    if(!n) return;
    int ndiff;
    AVLNode<Key, Value>* p = n->getParent();
    if(p){
        if(n==p->getLeft()){
            ndiff=1;
        }else{
            ndiff=-1;
        }
    }
    int8_t nbalance=n->getBalance();
    if(diff==-1){
        if(nbalance+diff==-1){
            n->setBalance(-1);
            return;
        }
        if(nbalance+diff==0){
            n->setBalance(0);
            remove_fix(p, ndiff);
        }
        if(nbalance+diff==-2){
            AVLNode<Key, Value>* c = n->getLeft();
            int8_t cbalance=c->getBalance();
            if(cbalance==-1){
                //zig-zig
                rightRotate(n);
                n->setBalance(0);
                c->setBalance(0);
                remove_fix(p,ndiff);
            }
            if(cbalance==0){
                //zig-zig
                rightRotate(n);
                n->setBalance(-1);
                c->setBalance(1);
                return;
            }
            if(cbalance==1){
                AVLNode<Key, Value>* g = c->getRight();
                leftRotate(c);
                rightRotate(n);
                int8_t gbalance=g->getBalance();
                if(gbalance==1){
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                if(gbalance==0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                if(gbalance==-1){
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                remove_fix(p,ndiff);
            }
        }
    }else{
        if(nbalance+diff==1){
            n->setBalance(1);
            return;
        }
        if(nbalance+diff==0){
            n->setBalance(0);
            remove_fix(p, ndiff);
        }
        if(nbalance+diff==2){
            AVLNode<Key, Value>* c = n->getRight();
            int8_t cbalance=c->getBalance();
            if(cbalance==1){
                //zig-zig
                leftRotate(n);
                n->setBalance(0);
                c->setBalance(0);
                remove_fix(p,ndiff);
            }
            if(cbalance==0){
                //zig-zig
                leftRotate(n);
                n->setBalance(1);
                c->setBalance(-1);
                return;
            }
            if(cbalance==-1){
                AVLNode<Key, Value>* g = c->getLeft();
                rightRotate(c);
                leftRotate(n);
                int8_t gbalance=g->getBalance();
                if(gbalance==-1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                if(gbalance==0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                if(gbalance==1){
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                remove_fix(p,ndiff);
            }
        }
    }
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
