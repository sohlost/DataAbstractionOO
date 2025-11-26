#pragma once
#include "../interfaces/IPriorityQueue.hpp"
#include "../storage/VectorHeapStorage.hpp"
#include "../concepts.hpp"
#include <functional>

namespace ds {

template <typename T, typename Compare = std::less<T>, typename Storage = VectorHeapStorage<T, Compare>>
requires PriorityQueueStorage<Storage, T>
class PriorityQueue final : public IPriorityQueue<T, Compare> {
  Storage s_;
public:
  using value_type = T;

  PriorityQueue() = default;
  explicit PriorityQueue(Compare c) : s_(c) {}
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void push(const T& x) override { s_.push(x); }
  void pop() override { s_.pop(); }
  const T& top() const override { return s_.top(); }

  // Functional support: expose read-only iterators
  // Note: Order is implementation-dependent (heap layout), not necessarily sorted
  auto begin() const { return s_.begin(); }
  auto end() const { return s_.end(); }
};

} // namespace ds
