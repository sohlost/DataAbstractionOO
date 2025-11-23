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
  LinkedListStorage() = default;
  ~LinkedListStorage();
  LinkedListStorage(const LinkedListStorage&) = delete;
  LinkedListStorage& operator=(const LinkedListStorage&) = delete;

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

