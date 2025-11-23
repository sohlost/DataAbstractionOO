namespace ds {

template <typename T, typename Compare>
VectorHeapStorage<T, Compare>::VectorHeapStorage() : a_(), cmp_(Compare{}) {}

template <typename T, typename Compare>
VectorHeapStorage<T, Compare>::VectorHeapStorage(Compare c) : a_(), cmp_(c) {}

template <typename T, typename Compare>
void VectorHeapStorage<T, Compare>::push(const T& x) {
  a_.push_back(x);
  std::push_heap(a_.begin(), a_.end(), cmp_);
}

template <typename T, typename Compare>
void VectorHeapStorage<T, Compare>::pop() {
  if (a_.empty()) throw std::out_of_range("pop on empty");
  std::pop_heap(a_.begin(), a_.end(), cmp_);
  a_.pop_back();
}

template <typename T, typename Compare>
const T& VectorHeapStorage<T, Compare>::top() const {
  if (a_.empty()) throw std::out_of_range("top on empty");
  return a_.front();
}

template <typename T, typename Compare>
std::size_t VectorHeapStorage<T, Compare>::size() const { return a_.size(); }

template <typename T, typename Compare>
bool VectorHeapStorage<T, Compare>::empty() const { return a_.empty(); }

} // namespace ds

