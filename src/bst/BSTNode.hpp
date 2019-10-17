// Yunfan Chen
// A53287711
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /** Initialize the node, with no parent and no children */
    BSTNode(const Data& d) : data(d) {
      left = nullptr; 
      right = nullptr;
      parent = nullptr;
    }

    /** Find smallest element that is larger than this BSTNode */
    BSTNode<Data>* successor() { 
      BSTNode<Data>* cur = this;
      if(cur == nullptr){
        return cur;
      } //if this node is null, return nullptr
      if(cur->right!=nullptr){
        cur = cur->right; // first go right one step
        while(cur->left!=nullptr){
          cur = cur->left; // find the leftmost leaf
        }
        return cur;
      }
      // if doesn't have right child, look at his parent
      cur = cur->parent;
      while(cur!=nullptr){
        if(cur->left==this){ // parent is successor
          return cur; 
        }else{
          cur = cur->parent; // go up
          if (cur && cur->data > this->data) {
					  return cur;
				  }
        }
      }
      delete cur;
      return nullptr; // don't have successor node
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
