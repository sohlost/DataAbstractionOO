#pragma once
#include "../interfaces/IQueue.hpp"
#include "../storage/LinkedListStorage.hpp"
#include "../concepts.hpp"

namespace ds {

template <typename T, typename Storage = LinkedListStorage<T>>
requires QueueStorage<Storage, T>
class Queue final : public IQueue<T> {
  Storage s_;
public:
  using value_type = T;
  
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void enqueue(const T& x) override { s_.push_back(x); }
  void dequeue() override { s_.pop_front(); }
  const T& front() const override { return s_.front(); }

  // Functional support: expose read-only iterators
  auto begin() const { return s_.begin(); }
  auto end() const { return s_.end(); }
};

} // namespace ds
