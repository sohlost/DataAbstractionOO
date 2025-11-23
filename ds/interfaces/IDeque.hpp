#pragma once
#include "IContainer.hpp"

namespace ds {

template <typename T>
struct IDeque : IContainer {
  virtual ~IDeque() = default;
  virtual void push_front(const T& x) = 0;
  virtual void push_back (const T& x) = 0;
  virtual void pop_front() = 0;
  virtual void pop_back () = 0;
  virtual const T& front() const = 0;
  virtual const T& back () const = 0;
};

} // namespace ds

