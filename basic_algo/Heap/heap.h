#ifndef HEAP
#define HEAP

template <class T>
void Swap(T* a, T* b) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}
template <class T>
void SiftUpHeap(T* begin, T* end, T* i) {
  if (i - begin < 1) {
    return;
  }
  T* parent = begin + (i - begin + 1) / 2 - 1;
  if (begin < i && *parent < *i) {
    Swap(i, parent);
    SiftUpHeap(begin, end, parent);
  }
}

template <class T>
void PushHeap(T* begin, T* end) {
  if (end - begin < 2) {
    return;
  }
  SiftUpHeap(begin, end - 1, end - 1);
}

template <class T>
void SiftDownHeap(T* begin, T* end, T* i) {
  if (i < begin) {
    return;
  }
  T* largest = i;
  if ((begin + (i - begin + 1) * 2 - 1) < (end + 1) && (*largest < *(begin + (i - begin + 1) * 2 - 1))) {
    largest = begin + (i - begin + 1) * 2 - 1;
  }
  if ((begin + (i - begin + 1) * 2 < end + 1) && (*largest < *(begin + (i - begin + 1) * 2))) {
    largest = begin + (i - begin + 1) * 2;
  }
  if (largest < i || i < largest) {
    Swap(largest, i);
    SiftDownHeap(begin, end, largest);
  }
}
template <class T>
void PopHeap(T* begin, T* end) {
  Swap(begin, end - 1);
  --end;
  SiftDownHeap(begin, end - 1, begin);
}
#endif
