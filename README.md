# Functional Data Structures & Algorithms - API Demos

This project implements a **Functional Programming Framework** on top of C++ Data Structures. 
The core deliverable is the **Developer API** which allows immutable transformations (`map`, `filter`, `reduce`) on standard containers.

We provide multiple demo files to showcase different aspects of the API.

---

## 🚀 Quick Start (Pipeline Simulator)

To interact with the "Shell-like" pipeline simulator (a proof-of-concept for the API), run:

```bash
./run_demo.sh
```
*(This compiles everything and launches the `cli_pipeline` tool)*

**Sample Pipeline Commands to Try:**
```bash
# 1. Basic Filter & Map
manual 1 2 3 4 5 | filter > 2 | map * 10 | show

# 2. Complex Analysis (Sort & Inversions)
manual 10 50 5 1 20 | sort desc | show | inversions

# 3. Data Aggregation (Sum)
manual 1 2 3 4 5 | sum

# 4. Chained Operations
manual 5 10 15 20 | filter > 5 | map + 1 | sort asc | show
```

---

## 💻 Developer API Demos (Code Examples)

The true power of the library is demonstrated in the following C++ examples. You can compile and run each to see the output.

### 1. Complex Data Pipeline (Assignment Use-Case)
**File:** `assignment_usecase.cpp`
**Demonstrates:** 
*   Loading files, tokenizing words, filtering by keyword, counting frequencies, and sorting.
*   Uses `flatMap` -> `filter` -> `map` -> `reduce` -> `sort` pipeline.
*   **Note:** Run with arguments: `./assignment_usecase keywords.txt data_directory`

### 2. Core Functional Transformations
**File:** `demo_containers_functional.cpp`
**Demonstrates:** 
*   Transforming a **Stack** (LIFO) using `filter` and `map` *without* popping elements.
*   Calculating the sum of a **Priority Queue** using `reduce`.
*   **Code Highlight:**
    ```cpp
    auto result = ds::map(
        ds::filter(myStack, isEven), // Returns new list, Stack stays intact
        square
    );
    ```

### 3. Generic Algorithms
**File:** `demo_generic.cpp`
**Demonstrates:** 
*   Using our `ds::map` and `ds::filter` on **Standard Library** containers like `std::vector` and `std::list`.
*   Shows the library's interoperability with standard C++.

---

## 🛠 Build & Run

You can build all demos using the Makefile:

```bash
make all
```

Then run specific demos:
```bash
./assignment_usecase <keywords_file> <data_dir> # (assignment_usecase.cpp)
./demo_functional                               # (demo_containers_functional.cpp)
./demo_generic                                  # (demo_generic.cpp)
```

---

## 👥 Team
- [Shashwat Patni]
- [Soham Dambalkar]
- [Jainil Alpesh Shah]
