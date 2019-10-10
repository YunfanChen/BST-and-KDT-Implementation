// Yunfan Chen
// A53287711
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;


template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:

    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** Default destructor. 
     *  Delete every node in this BST. 
     */
    virtual ~BST() { 
      deleteAll(root); 
    }

    /** Given a reference to a Data item, insert a copy of it in this BST. 
     *  Return true if the item was successfully added to this BST, 
     *  false if an item equal to this one was already in this BST.  
     *  Duplicate insertion is not allowed.
     */
    virtual bool insert(const Data& item) { 
      BSTNode<Data>* node = new BSTNode<Data>(item); 
      if(this->empty()){ // means this BST is empty, we should add a root in it.
        this->root = node;
        isize = isize + 1; // BST's size add 1
        node->parent = nullptr; // root's parent is null
        this->iheight = 0; // when BST only have root, its height is 0
        return true;
      }
      BSTNode<Data>* cur = this->root; 
      // BST is not empty, we should find a position to insert the node
      while(cur!=nullptr){
        if(item < cur->data){ // in left subtree
          if(cur->left==nullptr){ 
            // don't have left node anymore, then this is the position we want
            cur->left = node; 
            isize = isize + 1; // BST's size add 1
            node->parent = cur; // set parent
            iheight = calHeight(root)-1;
            return true;
          }else{
            cur = cur->left; // find the next left child
          }
        }else if(cur->data < item){ // in right subtree
          if(cur->right==nullptr){
            // don't have right node anymore, then this is the position we want
            cur->right = node;
            isize = isize + 1;
            node->parent = cur;
            iheight = calHeight(root)-1;
            return true;
          }else{
            cur = cur->right; // find the next right child
          }
        }else{
          break;
        }
      }
      return false; 
    }

    /** Find a Data item in the BST. Return an iterator pointing to the given item, 
     *  or pointing past the last node in the BST (i.e an iterator containing nullptr) if not found.
     */
    virtual iterator find(const Data& item) const { 
      if(this->empty()){
        // BST is empty, then we cannot find the node.
        return iterator(root);
      }
      BSTNode<Data>* cur = root;
      while(cur!=nullptr){
        if(item < cur->data){
          // in left subtree
          cur = cur->left;
        }else if(cur->data < item){
          // in right subtree
          cur = cur->right;
        }else{
          // this is the node we want
          return iterator(cur);
        }
      }
      return nullptr; 
    }

    /** Return the number of items currently in the BST.*/
    unsigned int size() const { 
      if(root==nullptr) return 0;
      return this->isize; 
    }

    /** Return the height of the BST.*/
    int height() const { 
      if(root==nullptr) return -1;
      return this->iheight; 
    }

    /** Return true if the BST is empty, else false.*/
    bool empty() const { 
      if(this->isize==0) return true;
      return false; 
    }

    /** Return an iterator pointing to the first item in the BST (the smallest element in current BST). */
    iterator begin() const { 
      return BST::iterator(first(root)); 
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { 
      return typename BST<Data>::iterator(0); 
    }

    /** Perform an inorder traversal of this BST to collect the data of each node in ascending order to a vector. */
    vector<Data> inorder() const {
      vector<Data> rtn;
      if(root==nullptr) return rtn; // if this tree is empty, return null.
      stack<BST<Data>>s;
      BSTNode<Data>* cur = root;
      while(cur!=nullptr || !s.empty()){
        if(cur!=nullptr){
          s.push(cur);
          cur = cur->left;
        }else
            {
                cur = s.top();
                rtn.push_back(p->data);
                cur = cur->right;
                s.pop();
            }
      }
      return rtn;
    }

    /** My helper function, which can add node to the vector inorderly. */
    // static void inorderHelper(BSTNode<Data>* root) {
    //   if(root==nullptr) return; 
    //   inorderHelper(root->left);
    //   BST<Data>::rtn.push_back(root->data); // add Data to vector's tail
    //   inorderHelper(root->right);
    // }

  private:
    /** Calculate the current height of BST. */
    static int calHeight(BSTNode<Data>* root) {
      if(root==nullptr) return 0;
      int leftH = calHeight(root->left);
      int rightH = calHeight(root->right);
      return leftH>rightH?leftH+1:rightH+1;
    }

    /** Help to find the smallest element in current BST */
    static BSTNode<Data>* first(BSTNode<Data>* root) { 
      BSTNode<Data>* rtn = root;
      if(root==nullptr) return rtn;
      while(rtn->left!=nullptr) rtn = rtn->left;
      return rtn; 
    }

    /** Delete all the node in this BST */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if(n==nullptr) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }
};

#endif  // BST_HPP
