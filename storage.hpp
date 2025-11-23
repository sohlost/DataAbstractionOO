#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace ds {

template <typename T>
class LinkedListStorage {
  struct Node {
    T val;
    Node* prev{nullptr};
    Node* next{nullptr};
    explicit Node(const T& v) : val(v) {}
  };
  Node* head_{nullptr};
  Node* tail_{nullptr};
  std::size_t n_{0};

public:
  LinkedListStorage() = default;
  ~LinkedListStorage() { clear(); }
  LinkedListStorage(const LinkedListStorage&) = delete;
  LinkedListStorage& operator=(const LinkedListStorage&) = delete;

  void clear() {
    Node* p = head_;
    while (p) { Node* nx = p->next; delete p; p = nx; }
    head_ = tail_ = nullptr; n_ = 0;
  }
  void push_front(const T& x) {
    Node* nd = new Node(x);
    nd->next = head_;
    if (head_) head_->prev = nd; else tail_ = nd;
    head_ = nd; ++n_;
  }
  void push_back(const T& x) {
    Node* nd = new Node(x);
    nd->prev = tail_;
    if (tail_) tail_->next = nd; else head_ = nd;
    tail_ = nd; ++n_;
  }
  void pop_front() {
    if (!n_) throw std::out_of_range("pop_front on empty");
    Node* old = head_; head_ = head_->next;
    if (head_) head_->prev = nullptr; else tail_ = nullptr;
    delete old; --n_;
  }
  void pop_back() {
    if (!n_) throw std::out_of_range("pop_back on empty");
    Node* old = tail_; tail_ = tail_->prev;
    if (tail_) tail_->next = nullptr; else head_ = nullptr;
    delete old; --n_;
  }
  const T& front() const {
    if (!n_) throw std::out_of_range("front on empty");
    return head_->val;
  }
  const T& back() const {
    if (!n_) throw std::out_of_range("back on empty");
    return tail_->val;
  }
  std::size_t size() const { return n_; }
  bool empty() const { return n_ == 0; }
};

template <typename T, typename Compare>
class VectorHeapStorage {
  std::vector<T> a_;
  Compare cmp_;
public:
  VectorHeapStorage() : a_(), cmp_(Compare{}) {}
  explicit VectorHeapStorage(Compare c) : a_(), cmp_(c) {}
  void push(const T& x) {
    a_.push_back(x);
    std::push_heap(a_.begin(), a_.end(), cmp_);
  }
  void pop() {
    if (a_.empty()) throw std::out_of_range("pop on empty");
    std::pop_heap(a_.begin(), a_.end(), cmp_);
    a_.pop_back();
  }
  const T& top() const {
    if (a_.empty()) throw std::out_of_range("top on empty");
    return a_.front();
  }
  std::size_t size() const { return a_.size(); }
  bool empty() const { return a_.empty(); }
};

} // namespace ds
