#ifndef BINSEARCH
#define BINSEARCH
template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  if (end < begin) {
    return false;
  }
  if (!(begin < end) && !(end < begin)) {
    return false;
  }
  --end;
  while (1 < end - begin) {
    const T* middle = begin + (end - begin) / 2;
    if (value < *middle) {
      end = middle;
    } else if (*middle < value) {
      begin = middle;
    } else {
      return true;
    }
  }
  return (!(*begin < value) && !(value < *begin)) || (!(value < *end) && !(*end < value));
}

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  const T* middle;
  if (!(*begin < value)) {
    return begin;
  }
  while (begin < end - 1) {
    middle = begin + (end - begin) / 2;
    if (*middle < value) {
      begin = middle;
    } else {
      end = middle;
    }
  }
  return end;
}

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  const T* middle;
  if (value < *begin) {
    return begin;
  }
  while (begin < end - 1) {
    middle = begin + (end - begin) / 2;
    if (value < *middle) {
      end = middle;
    } else {
      begin = middle;
    }
  }
  return end;
}
#endif
