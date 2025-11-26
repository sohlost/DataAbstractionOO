#pragma once
#include <cstddef>
#include <stdexcept>

namespace ds {

template <typename T>
class LinkedListStorage {
  struct Node {
    T val;
    Node* prev{nullptr};
    Node* next{nullptr};
    explicit Node(const T& v) : val(v) {}
  };
  Node* head_{nullptr};
  Node* tail_{nullptr};
  std::size_t n_{0};

public:
  using value_type = T;

  LinkedListStorage() = default;
  ~LinkedListStorage();
  
  // Rule of 5: Enable Copy and Move
  LinkedListStorage(const LinkedListStorage& other);
  LinkedListStorage(LinkedListStorage&& other) noexcept;
  LinkedListStorage& operator=(const LinkedListStorage& other);
  LinkedListStorage& operator=(LinkedListStorage&& other) noexcept;

  // Iterator Support
  class Iterator {
      Node* curr_;
  public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      Iterator(Node* n = nullptr) : curr_(n) {}
      
      T& operator*() const { return curr_->val; }
      T* operator->() const { return &curr_->val; }
      
      Iterator& operator++() { 
          if(curr_) curr_ = curr_->next; 
          return *this; 
      }
      
      Iterator operator++(int) { 
          Iterator tmp = *this; 
          ++(*this); 
          return tmp; 
      }
      
      bool operator==(const Iterator& other) const { return curr_ == other.curr_; }
      bool operator!=(const Iterator& other) const { return curr_ != other.curr_; }
  };

  Iterator begin() const { return Iterator(head_); }
  Iterator end() const { return Iterator(nullptr); }

  void clear();
  void push_front(const T& x);
  void push_back(const T& x);
  void pop_front();
  void pop_back();
  const T& front() const;
  const T& back() const;
  std::size_t size() const;
  bool empty() const;
};

} // namespace ds

#include "LinkedListStorage.tpp"

