#pragma once
#include "../interfaces/IStack.hpp"
#include "../storage/LinkedListStorage.hpp"
#include "../concepts.hpp"

namespace ds {

template <typename T, typename Storage = LinkedListStorage<T>>
requires StackStorage<Storage, T>
class Stack final : public IStack<T> {
  Storage s_;
public:
  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void push(const T& x) override { s_.push_back(x); }
  void pop() override { s_.pop_back(); }
  const T& top() const override { return s_.back(); }
};

} // namespace ds

