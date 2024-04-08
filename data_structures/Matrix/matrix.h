#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <stdexcept>

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t i, size_t j);
  const T& operator()(size_t i, size_t j) const;
  T& At(size_t i, size_t j);
  const T& At(size_t i, size_t j) const;
  Matrix& operator+=(const Matrix& lhs);
  Matrix& operator-=(const Matrix& lhs);
  Matrix& operator*=(const Matrix<T, M, M>& lhs);
  Matrix& operator*=(T value);
  Matrix& operator/=(T value);
  Matrix operator*(T value);
  Matrix operator/(T value);
};

template <class T, size_t N, size_t M>
size_t Matrix<T, N, M>::RowsNumber() const {
  return N;
}

template <class T, size_t N, size_t M>
size_t Matrix<T, N, M>::ColumnsNumber() const {
  return M;
}

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> lhs) {
  Matrix<T, M, N> trans;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      trans.matrix[j][i] = lhs.matrix[i][j];
    }
  }
  return trans;
}

template <class T, size_t N, size_t M>
T& Matrix<T, N, M>::operator()(size_t i, size_t j) {
  return matrix[i][j];
}

template <class T, size_t N, size_t M>
const T& Matrix<T, N, M>::operator()(size_t i, size_t j) const {
  return matrix[i][j];
}

template <class T, size_t N, size_t M>
T& Matrix<T, N, M>::At(size_t i, size_t j) {
  if (i < 0 || i >= N || j < 0 || j >= M) {
    throw MatrixOutOfRange{};
  }
  return matrix[i][j];
}

template <class T, size_t N, size_t M>
const T& Matrix<T, N, M>::At(size_t i, size_t j) const {
  if (i < 0 || i >= N || j < 0 || j >= M) {
    throw MatrixOutOfRange{};
  }
  return matrix[i][j];
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator+=(const Matrix<T, N, M>& lhs) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] += lhs.matrix[i][j];
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator-=(const Matrix<T, N, M>& lhs) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] -= lhs.matrix[i][j];
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(const Matrix<T, M, M>& lhs) {
  Matrix<T, N, M> m;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      m(i, j) = 0;
      for (size_t k = 0; k < M; ++k) {
        m(i, j) += matrix[i][k] * lhs(k, j);
      }
    }
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] = m(i, j);
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& rhs, const Matrix<T, N, M>& lhs) {
  Matrix mat = rhs;
  return mat += lhs;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& rhs, const Matrix<T, N, M>& lhs) {
  Matrix mat = rhs;
  return mat -= lhs;
}

template <class T, size_t N, size_t M, size_t P>
Matrix<T, N, P> operator*(const Matrix<T, N, M>& rhs, const Matrix<T, M, P>& lhs) {
  Matrix<T, N, P> mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < P; ++j) {
      mat(i, j) = 0;
      for (size_t r = 0; r < M; ++r) {
        mat(i, j) += rhs(i, r) * lhs(r, j);
      }
    }
  }
  return mat;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(T value) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] *= value;
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator/=(T value) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix[i][j] /= value;
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator*(T value) {
  Matrix<T, N, M> mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mat(i, j) = matrix[i][j] * value;
    }
  }
  return mat;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator/(T value) {
  Matrix<T, N, M> mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mat(i, j) = matrix[i][j] / value;
    }
  }
  return mat;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(int64_t value, const Matrix<T, N, M>& lhs) {
  Matrix<T, N, M> mat;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mat(i, j) = lhs(i, j) * value;
    }
  }
  return mat;
}

template <class T, size_t N, size_t M>
bool operator==(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (lhs(i, j) != rhs(i, j)) {
        return false;
      }
    }
  }
  return true;
}

template <class T, size_t N, size_t M>
bool operator!=(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
  return !(lhs == rhs);
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& lhs) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      in >> lhs(i, j);
    }
  }
  return in;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& lhs) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      out << lhs(i, j);
      if (M > j + 1) {
        out << " ";
      }
    }
    out << "\n";
  }
  return out;
}

#endif
