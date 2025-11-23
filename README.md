# Data Abstraction & Object Orientation Assignment  

This project implements *Stacks, Queues, Deques, and Priority Queues* using C++ templates, following the plan from Tutorial 17–24 Sept.  

---

## 1. The Top Level (Toolchains)  
- *Compiler*: g++ (C++17 standard)  
- *Build system*: Simple g++ CLI invocation (can be extended to CMake for modular builds).  
- *Front-end*: The user interacts via main.cpp, which demonstrates container operations by printing to the console.  
- *Libraries used*: Standard C++ library (STL) for std::vector, std::algorithm (push_heap, pop_heap). No external dependencies.  

---

## 2. The Base (Foundation Classes & Boilerplate)  
- **Interfaces (interfaces.hpp):  
  - IContainer (size/empty)  
  - IStack<T>  
  - IQueue<T>  
  - IDeque<T>  
  - IPriorityQueue<T, Compare>  

- **Storage engines (storage.hpp):  
  - LinkedListStorage<T>: custom doubly linked list for front/back ops.  
  - VectorHeapStorage<T, Compare>: wrapper over std::vector with heap functions.  

- **Concrete containers (containers.hpp):  
  - StackList<T>, QueueList<T>, DequeList<T> → LinkedListStorage<T>  
  - PriQueueList<T, Compare> → VectorHeapStorage<T, Compare>  

This separation ensures *abstraction* (interfaces), *encapsulation* (storage internals hidden), and *flexibility* (containers can swap underlying engines if needed).  

---

## 3. The Manufacturing (Development & Testing)  
- *IDE / Editor*: VS Code with C++ extension (though any C++ IDE can be used).  
- *Development process*:  
  1. Defined abstract interfaces first (behavior contract).  
  2. Implemented independent storage engines.  
  3. Built concrete containers by composition (interface + storage).  
  4. Wrote main.cpp demo for quick testing.  

- *Testing process*:  
  - Verified correctness of push/pop/size/empty for each container type.  
  - Checked exception safety (e.g., popping from empty container).  
  - Confirmed heap property for PriQueueList.  

- *Cycle*: Iterative refinement → compile → run demo → debug.  

---

## 4. The Team  
- *Team Members*:  
  - [Shashwat Patni]  
  - [Soham Dambalkar]  
  - [Jainil Alpesh Shah]  

- *Roles*:  
  - [Shashwat Patni] – Interface design (interfaces.hpp)  
  - [Soham Dambalkar] – Storage engine implementation (storage.hpp)  
  - [Jainil Alpesh Shah] – Concrete containers (containers.hpp)  

- *Division of labour*: Planned as modular ownership of files with integration checks during testing.  

---

## Interdependence vs Independence  
- *Independence*:  
  - Interfaces abstract away the underlying storage.  
  - Storage engines are usable independently of specific behaviors.  

- *Interdependence*:  
  - Concrete containers depend on both the interface (for behavior contract) and the storage engine (for implementation).  
  - Example: StackList<T> implements IStack<T> while internally using LinkedListStorage<T>.  

This separation demonstrates *data abstraction* (users only see the interface) and *object orientation* (composition, encapsulation, extensibility).