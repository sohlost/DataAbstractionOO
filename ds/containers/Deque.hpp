#pragma once
#include "../interfaces/IDeque.hpp"
#include "../storage/LinkedListStorage.hpp"
#include "../concepts.hpp"

namespace ds {

template <typename T, typename Storage = LinkedListStorage<T>>
requires SequenceStorage<Storage, T>
class Deque final : public IDeque<T> {
  Storage s_;
public:
  using value_type = T;

  std::size_t size() const override { return s_.size(); }
  bool empty() const override { return s_.empty(); }
  void push_front(const T& x) override { s_.push_front(x); }
  void push_back (const T& x) override { s_.push_back(x); }
  void pop_front() override { s_.pop_front(); }
  void pop_back () override { s_.pop_back(); }
  const T& front() const override { return s_.front(); }
  const T& back () const override { return s_.back(); }

  // Functional support: expose read-only iterators
  auto begin() const { return s_.begin(); }
  auto end() const { return s_.end(); }
};

} // namespace ds
