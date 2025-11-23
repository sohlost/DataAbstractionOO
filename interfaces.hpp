#pragma once
#include <cstddef>

namespace ds {

struct IContainer {
  virtual ~IContainer() = default;
  virtual std::size_t size() const = 0;
  virtual bool empty() const = 0;
};

template <typename T>
struct IStack : IContainer {
  virtual ~IStack() = default;
  virtual void push(const T& x) = 0;
  virtual void pop() = 0;
  virtual const T& top() const = 0;
};

template <typename T>
struct IQueue : IContainer {
  virtual ~IQueue() = default;
  virtual void enqueue(const T& x) = 0;
  virtual void dequeue() = 0;
  virtual const T& front() const = 0;
};

template <typename T>
struct IDeque : IContainer {
  virtual ~IDeque() = 0;
  virtual void push_front(const T& x) = 0;
  virtual void push_back (const T& x) = 0;
  virtual void pop_front() = 0;
  virtual void pop_back () = 0;
  virtual const T& front() const = 0;
  virtual const T& back () const = 0;
};
template <typename T> inline IDeque<T>::~IDeque() = default;

template <typename T, typename Compare>
struct IPriorityQueue : IContainer {
  virtual ~IPriorityQueue() = default;
  virtual void push(const T& x) = 0;
  virtual void pop() = 0;
  virtual const T& top() const = 0;
};

} // namespace ds
