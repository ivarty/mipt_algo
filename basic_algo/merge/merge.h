#ifndef MERGE
#define MERGE
template <class T, class U, class V>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, V* out) {
  const T* left1 = first_begin;
  const U* left2 = second_begin;
  while (left1 < first_end && left2 < second_end) {
    if (*left1 < *left2) {
      *out = *left1;
      ++left1;
    } else {
      *out = *left2;
      ++left2;
    }

    ++out;
  }
  while (left1 < first_end) {
    *out = *left1;
    ++out;
    ++left1;
  }
  while (left2 < second_end) {
    *out = *left2;
    ++out;
    ++left2;
  }
}
#endif
