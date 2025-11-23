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
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void enqueue(const T& x) override { s_.push_back(x); }
  void dequeue() override { s_.pop_front(); }
  const T& front() const override { return s_.front(); }
};

} // namespace ds

