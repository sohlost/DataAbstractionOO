#pragma once
#include <cstddef>

namespace ds {

struct IContainer {
  virtual ~IContainer() = default;
  virtual std::size_t size() const = 0;
  virtual bool empty() const = 0;
};

} // namespace ds

