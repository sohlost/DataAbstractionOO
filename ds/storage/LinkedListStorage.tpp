namespace ds {

template <typename T>
LinkedListStorage<T>::~LinkedListStorage() { clear(); }

template <typename T>
void LinkedListStorage<T>::clear() {
  Node* p = head_;
  while (p) { Node* nx = p->next; delete p; p = nx; }
  head_ = tail_ = nullptr; n_ = 0;
}

template <typename T>
void LinkedListStorage<T>::push_front(const T& x) {
  Node* nd = new Node(x);
  nd->next = head_;
  if (head_) head_->prev = nd; else tail_ = nd;
  head_ = nd; ++n_;
}

template <typename T>
void LinkedListStorage<T>::push_back(const T& x) {
  Node* nd = new Node(x);
  nd->prev = tail_;
  if (tail_) tail_->next = nd; else head_ = nd;
  tail_ = nd; ++n_;
}

template <typename T>
void LinkedListStorage<T>::pop_front() {
  if (!n_) throw std::out_of_range("pop_front on empty");
  Node* old = head_; head_ = head_->next;
  if (head_) head_->prev = nullptr; else tail_ = nullptr;
  delete old; --n_;
}

template <typename T>
void LinkedListStorage<T>::pop_back() {
  if (!n_) throw std::out_of_range("pop_back on empty");
  Node* old = tail_; tail_ = tail_->prev;
  if (tail_) tail_->next = nullptr; else head_ = nullptr;
  delete old; --n_;
}

template <typename T>
const T& LinkedListStorage<T>::front() const {
  if (!n_) throw std::out_of_range("front on empty");
  return head_->val;
}

template <typename T>
const T& LinkedListStorage<T>::back() const {
  if (!n_) throw std::out_of_range("back on empty");
  return tail_->val;
}

template <typename T>
std::size_t LinkedListStorage<T>::size() const { return n_; }

template <typename T>
bool LinkedListStorage<T>::empty() const { return n_ == 0; }

} // namespace ds

