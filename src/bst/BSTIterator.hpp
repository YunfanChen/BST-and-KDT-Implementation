// Yunfan Chen
// A53287711
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /** Constructor that initialize the current BSTNode
     *  in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->data; }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** Equality test operator. 
     *  Two iterators are equal with each other if they contain the same BSTNode pointer. 
     */
    bool operator==(BSTIterator<Data> const& other) const { 
      if(this->curr==other.curr){
        return true;
      }else{
        return false; 
      } 
    }

    /** Inequality test operator. */
    bool operator!=(BSTIterator<Data> const& other) const { 
      if(this->curr==other.curr){
        return false;
      }else{
        return true; 
      } 
    }
};

#endif  // BSTITERATOR_HPP
