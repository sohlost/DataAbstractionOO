#pragma once
#include "IContainer.hpp"

namespace ds {

template <typename T>
struct IStack : IContainer {
  virtual ~IStack() = default;
  virtual void push(const T& x) = 0;
  virtual void pop() = 0;
  virtual const T& top() const = 0;
};

} // namespace ds

