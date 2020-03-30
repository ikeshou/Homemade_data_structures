# Homemade_data_structures
standard (non-)template library implemented in C from scratch
![fig1](https://user-images.githubusercontent.com/11537598/77941869-c839b300-72f5-11ea-9fbd-3895e86ef4ed.png)

<br>

## Covered data structures and algorithms in each directory

### 1. Array directory
- Comparison sort such as bubble sort, insertion sort, selection sort, merge sort, quick sort
- Linear sort such as counting sort, radix sort
- Algorithms derived from sorting algorithms such as nth_smallest, count_inversion
- Search algorithms such as binary search, lower_bound, upper_bound

### 2. Vector directory
- Elastic array implementation (pseudo std::vector)

### 3. Heap directory
- Max heap
- Max priority queue (pseudo std::priority_queue)

### 4. LinkedList directory
- Singly linked list, stack
- Circular linked list, queue
- Doubly linked list, deque
- Circular doubly linked list, deque (pseudo std::list)

### 5. RingBuffer directory
- Deque implementation using ring buffer (pseudo std::deque)

### 6. Hash directory
- Hash table implementation using doubly linked list (pseudo std::unordered_map)
- Set implementation using doubly linked list (pseudo std::unordered_set)

### 7. BinaryTree directory
- Binary search tree and randomized binary search tree implementaion
- Red black tree implementation (pseudo std::map)