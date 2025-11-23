#include <iostream>
#include "containers.hpp"

int main() {
  using namespace ds;

  StackList<int> s; s.push(10); s.push(20);
  std::cout << "Stack top=" << s.top() << " size=" << s.size() << "\n";

  QueueList<int> q; q.enqueue(1); q.enqueue(2); q.dequeue();
  std::cout << "Queue front=" << q.front() << " size=" << q.size() << "\n";

  DequeList<int> d; d.push_front(5); d.push_back(6); d.pop_front();
  std::cout << "Deque back=" << d.back() << " size=" << d.size() << "\n";

  PriQueueList<int> pq; pq.push(7); pq.push(3); pq.push(9);
  std::cout << "PQ top=" << pq.top() << " size=" << pq.size() << "\n";
}
