#ifndef UNIQPTR
#define UNIQPTR

template <typename T>
class UniquePtr {
 public:
  UniquePtr();
  explicit UniquePtr(T* ptr);
  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;
  UniquePtr(UniquePtr&& other) noexcept;
  UniquePtr& operator=(UniquePtr&& other) noexcept;
  T* Release();
  ~UniquePtr();
  void Reset(T* ptr = nullptr);
  void Swap(UniquePtr<T>& other);
  T* Get() const;
  T* operator->() const;
  T& operator*() const;
  explicit operator bool() const;

 private:
  T* uptr_;
};

template <class T>
UniquePtr<T>::UniquePtr() : uptr_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T* ptr) : uptr_(ptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept : uptr_(other.uptr_) {
  other.uptr_ = nullptr;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  delete uptr_;
  uptr_ = other.uptr_;
  other.uptr_ = nullptr;
  return *this;
}

template <class T>
T* UniquePtr<T>::Release() {
  auto tmp = uptr_;
  uptr_ = nullptr;
  return tmp;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
  delete uptr_;
}

template <class T>
void UniquePtr<T>::Reset(T* ptr) {
  delete uptr_;
  uptr_ = ptr;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) {
  std::swap(uptr_, other.uptr_);
}

template <class T>
T* UniquePtr<T>::Get() const {
  return uptr_;
}

template <class T>
T* UniquePtr<T>::operator->() const {
  return uptr_;
}

template <class T>
T& UniquePtr<T>::operator*() const {
  return *uptr_;
}

template <class T>
UniquePtr<T>::operator bool() const {
  return (Get() != nullptr);
}
#endif
