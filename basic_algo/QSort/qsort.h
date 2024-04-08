#ifndef SORT
#define SORT
template <class T>
void Swap(T* a, T* b) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}

template <typename T>
void Sort(T* begin, T* end) {
  if (!(begin < end)) {
    return;
  }
  --end;
  T* i = begin;
  T* j = end;
  T* p = begin;
  T* q = end;
  T pivot = *end;
  for (T* idx = begin; idx < end; idx++) {
    while (*i++ < pivot) {
    }
    --i;
    while (pivot < *--j) {
      if (!(j < begin) && !(begin < j)) {
        break;
      }
    }
    if (!(i < j)) {
      break;
    }
    Swap(i, j);
    if (!(*i < pivot) && !(pivot < *i)) {
      p++;
      Swap(i, p - 1);
    }
    if (!(*j < pivot) && !(pivot < *j)) {
      q--;
      Swap(j, q);
    }
  }
  Swap(i, end);
  j = i - 1;
  i++;
  for (T* k = begin; p < k; k++) {
    Swap(j, k);
    j--;
  }
  for (T* k = end - 1; !(k < q); k--) {
    Swap(i, k);
    i++;
  }
  Sort(begin, j + 1);
  Sort(i, end + 1);
}
#endif
