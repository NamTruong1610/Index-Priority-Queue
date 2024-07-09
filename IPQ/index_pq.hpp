#ifndef INDEX_PRIORITY_QUEUE_HPP_
#define INDEX_PRIORITY_QUEUE_HPP_

#include <vector>
#include <algorithm>

template <typename T>
class IndexPriorityQueue {
 private:
  // vector to hold priorities.  
  // priorities.at(i) is the priority associated to index i
  // the heap will only contain indices, we look up priorities
  // in this vector as needed
  std::vector<T> priorities {};
  // priorityQueue stores indices: priorityQueue.at(i) is an index
  // priorityQueue functions as the heap and is heap ordered: 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i)) 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i) + 1) 
  std::vector<int> priorityQueue {};
  // indexToPosition.at(i) is the position in priorityQueue of index i
  // priorityQueue.at(indexToPosition.at(i)) = i
  // indexToPosition.at(priorityQueue.at(j)) = j
  std::vector<int> indexToPosition {};
  int size_ = 0;

 public:
  explicit IndexPriorityQueue(int);
  void push(const T&, int);
  void pop();
  void erase(int);
  bool contains(int) const;
  void changeKey(const T&, int);
  std::pair<T, int> top() const;
  bool empty() const;
  int size() const;

 private:
  // TODO: you may want to add your own member functions. swim? sink?
  void swim(int);
  void sink(int);
};

// Useful helper functions
int leftChild(int i) {
  return 2*i;
}

int rightChild(int i) {
  return 2*i + 1;
}

int parent(int i) {
  return i/2;
}

// IndexPriorityQueue member functions
template <typename T>
IndexPriorityQueue<T>::IndexPriorityQueue(int N) {
  priorities.resize(N);
  priorityQueue.resize(N + 1);
  indexToPosition.resize(N);
}

template <typename T>
bool IndexPriorityQueue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
int IndexPriorityQueue<T>::size() const {
  return size_;
}

template <typename T>
void IndexPriorityQueue<T>::push(const T& priority, int index) {
  if (contains(index) == true) {
    return;
  }
  size_++;
  priorities.at(index) = priority;
  priorityQueue.at(size_) = index;
  indexToPosition.at(index) = size_;
  swim(size_);
}

template <typename T>
void IndexPriorityQueue<T>::pop() {
  if (empty() == true) return;
  else{
    std::swap(priorityQueue.at(1), priorityQueue.at(size_));
    size_--;
    sink(1);
  }
}

template <typename T>
void IndexPriorityQueue<T>::erase(int index) {
  if (contains(index) == false) return;
  int position = indexToPosition.at(index);
  std::swap(priorityQueue.at(position), priorityQueue.at(size_));
  indexToPosition.at(priorityQueue.at(position)) = position;
  indexToPosition.at(priorityQueue.at(size_)) = size_;
  size_--;
  indexToPosition.at(index) = -1;  
  if (position <= size_) {
    swim(position);
    sink(position);
  }
}

template <typename T>
std::pair<T, int> IndexPriorityQueue<T>::top() const {
  return {priorities.at(priorityQueue.at(1)), priorityQueue.at(1)};
}

// if vertex i is not present, insert it with key
// otherwise change the associated key value of i to key
template <typename T>
void IndexPriorityQueue<T>::changeKey(const T& key, int index) {
  if (contains(index) == false) {
    push(key, index); 
    return;
  }
  priorities.at(index) = key;
  int pos = indexToPosition.at(index);
  swim(pos);
  sink(pos);
}

template <typename T>
bool IndexPriorityQueue<T>::contains(int index) const {
  if (index >= 0 && 
      static_cast<size_t>(index) < indexToPosition.size() && 
      indexToPosition.at(index) > 0 && 
      indexToPosition.at(index) <= size_){
    return true;
  }
  else return false;
}

template <typename T>
void IndexPriorityQueue<T>::swim(int index) {
  while (index > 1 && priorities.at(priorityQueue.at(index)) < priorities.at(priorityQueue.at(parent(index)))) {
    std::swap(priorityQueue.at(index), priorityQueue.at(parent(index)));
    indexToPosition.at(priorityQueue.at(index)) = index;
    indexToPosition.at(priorityQueue.at(parent(index))) = parent(index);
    index = parent(index);
  }
}

template <typename T>
void IndexPriorityQueue<T>::sink(int index) {
  while (leftChild(index) <= size_ || rightChild(index) <= size_) {
    int lIndex = leftChild(index);
    int rIndex = rightChild(index);
    int smallestChildIndex = lIndex;
    if (rightChild(index) <= size_ && priorities.at(priorityQueue.at(lIndex)) > priorities.at(priorityQueue.at(rIndex))) {
      smallestChildIndex = rIndex;
    }
    if (priorities.at(priorityQueue.at(index)) <= priorities.at(priorityQueue.at(smallestChildIndex))) {
      break;
    }
    std::swap(priorityQueue.at(index), priorityQueue.at(smallestChildIndex));
    indexToPosition.at(priorityQueue.at(index)) = index;
    indexToPosition.at(priorityQueue.at(smallestChildIndex)) = smallestChildIndex;
    index = smallestChildIndex;
  }
}






#endif      // INDEX_PRIORITY_QUEUE_HPP_