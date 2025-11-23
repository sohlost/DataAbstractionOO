#pragma once
#include "interfaces.hpp"
#include "storage.hpp"

namespace ds {

template <typename T>
class StackList final : public IStack<T> {
  LinkedListStorage<T> s_;
public:
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void push(const T& x) override { s_.push_back(x); }
  void pop() override { s_.pop_back(); }
  const T& top() const override { return s_.back(); }
};

template <typename T>
class QueueList final : public IQueue<T> {
  LinkedListStorage<T> s_;
public:
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void enqueue(const T& x) override { s_.push_back(x); }
  void dequeue() override { s_.pop_front(); }
  const T& front() const override { return s_.front(); }
};

template <typename T>
class DequeList final : public IDeque<T> {
  LinkedListStorage<T> s_;
public:
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void push_front(const T& x) override { s_.push_front(x); }
  void push_back (const T& x) override { s_.push_back(x); }
  void pop_front() override { s_.pop_front(); }
  void pop_back () override { s_.pop_back(); }
  const T& front() const override { return s_.front(); }
  const T& back () const override { return s_.back(); }
};

template <typename T, typename Compare = std::less<T>>
class PriQueueList final : public IPriorityQueue<T, Compare> {
  VectorHeapStorage<T, Compare> s_;
public:
  PriQueueList() = default;
  explicit PriQueueList(Compare c) : s_(c) {}
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void push(const T& x) override { s_.push(x); }
  void pop() override { s_.pop(); }
  const T& top() const override { return s_.top(); }
};

} // namespace ds
