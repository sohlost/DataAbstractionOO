#include <iostream>
#include "ds/containers/Stack.hpp"
#include "ds/containers/Queue.hpp"
#include "ds/containers/Deque.hpp"
#include "ds/containers/PriorityQueue.hpp"

int main() {
  using namespace ds;

  // Use the new generic classes. Default storage is LinkedListStorage.
  Stack<int> s; s.push(10); s.push(20);
  std::cout << "Stack top=" << s.top() << " size=" << s.size() << "\n";

  Queue<int> q; q.enqueue(1); q.enqueue(2); q.dequeue();
  std::cout << "Queue front=" << q.front() << " size=" << q.size() << "\n";

  Deque<int> d; d.push_front(5); d.push_back(6); d.pop_front();
  std::cout << "Deque back=" << d.back() << " size=" << d.size() << "\n";

  PriorityQueue<int> pq; pq.push(7); pq.push(3); pq.push(9);
  std::cout << "PQ top=" << pq.top() << " size=" << pq.size() << "\n";
}
