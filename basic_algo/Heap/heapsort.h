#ifndef HEAP
#define HEAP

template <class T>
void Swap(T* a, T* b) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}

template <class T>
void SiftDown(T* begin, T* end, T* i) {
  if (i < begin) {
    return;
  }
  T* largest = i;
  if ((begin + (i - begin) * 2 + 1) < end && (*largest < *(begin + (i - begin) * 2 + 1))) {
    largest = begin + (i - begin) * 2 + 1;
  }
  if ((begin + (i - begin) * 2 + 2 < end) && (*largest < *(begin + (i - begin) * 2 + 2))) {
    largest = begin + (i - begin) * 2 + 2;
  }
  if (largest != i) {
    Swap(largest, i);
    SiftDown(begin, end, largest);
  }
}

template <class T>
void MakeHeap(T* begin, T* end) {
  int size = end - begin;
  int i = size / 2;
  while (i > 0) {
    --i;
    SiftDown(begin, end, begin + i);
  }
}

template <class T>
void SortHeap(T* begin, T* end) {
  int size = end - begin;
  for (int i = size - 1; i > 0; --i) {
    Swap(begin, begin + i);
    --size;
    SiftDown(begin, begin + size, begin);
  }
}

#endif
