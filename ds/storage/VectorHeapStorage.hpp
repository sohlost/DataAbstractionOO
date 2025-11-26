#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace ds {

template <typename T, typename Compare>
class VectorHeapStorage {
  std::vector<T> a_;
  Compare cmp_;
public:
  using value_type = T;
  using const_iterator = typename std::vector<T>::const_iterator;
  using iterator = typename std::vector<T>::iterator;

  VectorHeapStorage();
  explicit VectorHeapStorage(Compare c);
  
  void push(const T& x);
  void pop();
  const T& top() const;
  std::size_t size() const;
  bool empty() const;

  // Iterator support for functional algorithms (Read-Only traversal)
  // Note: Iteration order is implementation-defined (underlying vector order), not sorted.
  const_iterator begin() const { return a_.begin(); }
  const_iterator end() const { return a_.end(); }
  
  // Mutable iterators if needed, but be careful not to break heap invariants!
  iterator begin() { return a_.begin(); }
  iterator end() { return a_.end(); }
};

} // namespace ds

#include "VectorHeapStorage.tpp"
