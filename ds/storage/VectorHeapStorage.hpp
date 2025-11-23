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
  VectorHeapStorage();
  explicit VectorHeapStorage(Compare c);
  void push(const T& x);
  void pop();
  const T& top() const;
  std::size_t size() const;
  bool empty() const;
};

} // namespace ds

#include "VectorHeapStorage.tpp"

