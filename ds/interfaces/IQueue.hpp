#pragma once
#include "IContainer.hpp"

namespace ds {

template <typename T>
struct IQueue : IContainer {
  virtual ~IQueue() = default;
  virtual void enqueue(const T& x) = 0;
  virtual void dequeue() = 0;
  virtual const T& front() const = 0;
};

} // namespace ds

