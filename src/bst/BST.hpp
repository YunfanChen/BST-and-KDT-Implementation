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

    /** TODO */
    virtual ~BST() { 
      deleteAll(root); 
    }

    /** TODO */
    virtual bool insert(const Data& item) { 
      BSTNode<Data>* node = new BSTNode<Data>(item);
      if(this->empty()){
        this->root = node;
        isize = isize + 1;
        node->parent = NULL;
        this->iheight = 0;
        return true;
      }
      BSTNode<Data>* cur = this->root;
      while(cur!=nullptr){
        if(item < cur->data){
          if(cur->left==nullptr){
            cur->left = node;
            isize = isize + 1;
            node->parent = cur;
            this->iheight++;
            return true;
          }else{
            cur = cur->left;
          }
        }else if(cur->data < item){
          if(cur->right==nullptr){
            cur->right = node;
            isize = isize + 1;
            node->parent = cur;
            this->iheight++;
            return true;
          }else{
            cur = cur->right;
          }
        }else{
          break;
        }
      }
      return false; 
    }

    /** TODO */
    virtual iterator find(const Data& item) const { 
      if(this->empty()){
        return iterator(root);
      }
      BSTNode<Data>* cur = root;
      while(cur!=nullptr){
        if(item < cur->data){
          cur = cur->left;
        }else if(cur->data < item){
          cur = cur->right;
        }else{
          return iterator(cur);
        }
      }
      return 0; 
    }

    /** TODO */
    unsigned int size() const { 
      return this->isize; 
    }

    /** TODO */
    int height() const { 
      if(root==nullptr) return -1;
      return this->iheight; 
    }

    /** TODO */
    bool empty() const { 
      if(this->isize==0) return true;
      return false; 
    }

    /** TODO */
    iterator begin() const { 
      return BST::iterator(first(root)); 
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { 
      return typename BST<Data>::iterator(0); 
    }

    /** TODO */
    vector<Data> inorder() const {
      vector<Data> rtn;
      if(root==nullptr) return rtn;
      inorderHelper(rtn,root);
      return rtn;
    }


  private:
    static void inorderHelper(vector<Data> list, BSTNode<Data>* root) {
      if(root==nullptr) return list;
      inorderHelper(list,root->left);
      list.push_back(root->data);
      inorderHelper(list,root->right);
      return list;
    }
    
    /** TODO */
    static BSTNode<Data>* first(BSTNode<Data>* root) { 
      BSTNode<Data>* rtn = root;
      while(rtn->left!=nullptr) rtn = rtn->left;
      return rtn; 
    }

    /** TODO */
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
