#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  List() : first(nullptr), last(nullptr), size_(0){ }
  ~List(){
    clear();
  }
  List(const List &other): first(nullptr), last(nullptr), size_(0){
    copy_all(other);
  }

  List &operator=(const List &rhs){
    if(this != &rhs){
      clear();
      copy_all(rhs);
    }
    return *this;
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

private:
  int size_;
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;

    Node(const T&d, Node* p = nullptr, Node* n = nullptr) : 
      next(n), prev(p), datum(d) {}
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator(): list_ptr(nullptr), node_ptr(nullptr){}


    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.



    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    T& operator*() const;
    Iterator operator++(int);
    Iterator& operator++();
    bool operator==(Iterator rhs) const;
    bool operator!=(Iterator rhs) const;
    friend class List;
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here


    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np);

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const;

  // return an Iterator pointing to "past the end"
  Iterator end() const;

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i);

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum);

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.



  //EFFECTS:  returns true if the list is empty
template<typename T>
bool List<T>::empty() const{
  return size_ == 0;
}

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
template<typename T>
int List<T>::size() const{
  return size_;
}

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
template<typename T>
T & List<T>:: front() {
  assert(!empty());
  return first->datum;
}

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
template<typename T>
T & List<T>:: back(){
  assert(!empty());
  return last->datum;
}

  //EFFECTS:  inserts datum into the front of the list
template<typename T>
void List<T>:: push_front(const T &datum){
  Node* addedNode = new Node(datum, nullptr, first);


  if(empty()){
    first = addedNode;
    last = addedNode;
  } else {
    first->prev = addedNode;
    first = addedNode;
  }
  size_++;

}

//EFFECTS:  inserts datum into the back of the list
template<typename T>
void List<T>::push_back(const T &datum){
  Node* addedNode = new Node(datum, last, nullptr);
  if(empty()){
  first = addedNode;
  last = addedNode;
  } else {
    last->next = addedNode;
    last = addedNode;
  }

  size_++;
}

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
template<typename T>
void List<T>::pop_front(){
  assert(!empty());
  Node* temporary = first;
  if(size_ == 1){
    first = nullptr;
    last = nullptr;
  } else {
    first = first->next;
    first->prev = nullptr;
  }

  delete temporary;
  size_--;
}

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
template<typename T>
void List<T>::pop_back(){
  assert(!empty());
  Node* temporary = last;
  if(size_ == 1){
    first = nullptr;
    last = nullptr;
  } else {
    last = last->prev;
    last->next = nullptr;
  }

  delete temporary;
  size_--;
}

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
template<typename T>
void List<T>::clear(){
  while(!empty()){
    pop_front();
  }
}


  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.



  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  template<typename T>
  void List<T>::copy_all(const List<T> &other){
    for(Node* current = other.first; current != nullptr; current = current-> next){
      push_back(current->datum);
    }
  }


template<typename T>
List<T>::Iterator::Iterator(const List *lp, Node *np) :
  list_ptr(lp), node_ptr(np){}
//implementng iterators?
template<typename T>
//    T& operator*() const;

T & List<T>::Iterator::operator*() const {
  assert(node_ptr);
  return node_ptr->datum;
}

template<typename T>
    //Iterator& operator++(int);

typename List<T>::Iterator List<T>::Iterator::operator++(int){
  Iterator temporary = *this;
  operator++();
  return temporary;
}

template<typename T>
    //Iterator& operator++();
typename List<T>::Iterator & List<T>::Iterator::operator++(){
  assert(node_ptr);
  node_ptr = node_ptr->next;
  return *this;
}

template<typename T>
    //bool operator==(Iterator rhs) const;

bool List<T>::Iterator::operator==(Iterator rhs) const{
  return list_ptr == rhs.list_ptr && node_ptr == rhs.node_ptr;
}

template<typename T>
    //bool operator!=(Iterator rhs) const;

bool List<T>::Iterator::operator!=(Iterator rhs) const{
  return !(*this == rhs);
}

  // return an Iterator pointing to the first element
template<typename T>
//  Iterator begin() const;
//bool List<T>::begin() const {
List<T>::Iterator List<T>::begin() const{
  //List<T>::Iterator List<T>::begin() const
  return Iterator(this, first);
}

  // return an Iterator pointing to "past the end"
template<typename T>
List<T>::Iterator List<T>::end() const{
  return Iterator(this, nullptr);
}
//Iterator end() const;

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
template<typename T>
List<T>::Iterator List<T>::erase(Iterator i){ 
  assert(i.node_ptr);
  Node* node = i.node_ptr;
  Node* nextNode = node->next;

  if(node == first){
    pop_front();
  } else if(node == last){
    pop_back();
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    size_--;
  }

  return Iterator(this, nextNode);
//  Iterator erase(Iterator i);
}
  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
template<typename T>
List<T>::Iterator List<T>::insert(Iterator i, const T &datum){
  if(i.node_ptr == first){
    push_front(datum);
    return begin();
  }
  if(i.node_ptr == nullptr){
    push_back(datum);
    return Iterator(this, last);
  }

  Node* current = i.node_ptr;
  Node* newNode = new Node(datum, current->prev, current);

  current->prev->next = newNode;
  current->prev = newNode;

  size_++;
  return Iterator(this, newNode);

}  

//Iterator insert(Iterator i, const T &datum);

#endif // Do not remove this. Write all your code above this line.
