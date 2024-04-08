#include "cstring.h"

size_t Strlen(const char* str) {
  size_t i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}

int Strcmp(const char* first, const char* second) {
  size_t len1 = Strlen(first);
  size_t len2 = Strlen(second);
  size_t max = len1;
  if (len1 < len2) {
    max = len2;
  }
  for (size_t i = 0; i < max; ++i) {
    if (first[i] != second[i]) {
      if (first[i] < second[i]) {
        return -1;
      }
      if (second[i] < first[i]) {
        return 1;
      }
    }
  }
  return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t len = Strlen(first);
  size_t min = len;
  if (count < len) {
    min = count;
  }
  for (size_t i = 0; i < min; ++i) {
    if (first[i] != second[i]) {
      if (first[i] < second[i]) {
        return -1;
      }
      if (second[i] < first[i]) {
        return 1;
      }
    }
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  size_t len = Strlen(src);
  for (size_t i = 0; i < len + 1; ++i) {
    dest[i] = src[i];
  }
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t len = Strlen(src);
  if (count < len) {
    for (size_t i = 0; i < count; ++i) {
      dest[i] = src[i];
    }
  } else {
    for (size_t i = 0; i < len; ++i) {
      dest[i] = src[i];
    }
    for (size_t i = len; i < count; ++i) {
      dest[i] = '\0';
    }
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);
  for (size_t i = 0; i < src_len + 1; ++i) {
    dest[dest_len + i] = src[i];
  }
  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);
  if (src_len <= count) {
    return Strcat(dest, src);
  }
  for (size_t i = 0; i < count; ++i) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + count] = '\0';
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  size_t len = Strlen(str);
  for (size_t i = 0; i < len + 1; ++i) {
    if (str[i] == symbol) {
      return str + i;
    }
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  size_t len = Strlen(str);
  for (size_t i = len + 1; i > 0; --i) {
    if (str[i - 1] == symbol) {
      return str + i - 1;
    }
  }
  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  size_t count = 0;
  size_t dest_len = Strlen(dest);
  for (size_t i = 0; i < dest_len; ++i) {
    if (Strchr(src, dest[i]) != nullptr) {
      ++count;
    } else {
      return count;
    }
  }
  return count;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t count = 0;
  size_t dest_len = Strlen(dest);
  for (size_t i = 0; i < dest_len; ++i) {
    if (Strchr(src, dest[i]) == nullptr) {
      ++count;
    } else {
      return count;
    }
  }
  return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t dest_len = Strlen(dest);
  for (size_t i = 0; i < dest_len; ++i) {
    if (Strchr(breakset, dest[i]) != nullptr) {
      return dest + i;
    }
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  size_t str_len = Strlen(str);
  size_t pattern_len = Strlen(pattern);
  if (pattern_len > str_len) {
    return nullptr;
  }
  for (size_t i = 0; i < str_len - pattern_len + 1; ++i) {
    size_t j = 0;
    while (j < pattern_len && str[i + j] == pattern[j]) {
      ++j;
    }
    if (j == pattern_len) {
      return str + i;
    }
  }
  return nullptr;
}
