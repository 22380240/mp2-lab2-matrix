// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <exception>
#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор -
// шаблонный вектор на динамической памяти
template <typename T> class TDynamicVector {
protected:
  size_t sz;
  T *pMem;

public:
  TDynamicVector(size_t size = 1) : sz(size) {
    if (sz == 0) {
      throw std::out_of_range("Vector size should be greater than zero");
    }
    if (sz > MAX_VECTOR_SIZE) {
      throw std::out_of_range("Vector size is too big");
    }
    pMem = new T[sz](); // {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T *arr, size_t s) : sz(s) {
    if (sz > MAX_VECTOR_SIZE) {
      throw std::out_of_range("Vector size is too big");
    }
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector &v) : sz(v.sz) {
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector &&v) noexcept {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector() { delete[] pMem; }
  TDynamicVector &operator=(const TDynamicVector &v) {
    if (*this == v) {
      return *this;
    }

    TDynamicVector tmp(v);

    swap(*this, tmp);

    return *this;
  }
  TDynamicVector &operator=(TDynamicVector &&v) noexcept {
    swap(*this, v);

    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T &operator[](size_t ind) {
    if (ind >= sz) {
      throw std::invalid_argument("ind is too big");
    }

    return pMem[ind];
  }
  const T &operator[](size_t ind) const {
    if (ind >= sz) {
      throw std::invalid_argument("ind is too big");
    }

    return pMem[ind];
  }
  // индексация с контролем
  T &at(size_t ind) {
    if (ind >= sz) {
      throw std::invalid_argument("ind is too big");
    }

    return pMem[ind];
  }
  const T &at(size_t ind) const {
    if (ind >= sz) {
      throw std::invalid_argument("ind is too big");
    }

    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector &v) const noexcept {
    if (sz != v.sz) {
      return false;
    }

    for (size_t i = 0; i < sz; i++) {
      if (this->at(i) != v.at(i)) {
        return false;
      }
    }

    return true;
  }
  bool operator!=(const TDynamicVector &v) const noexcept {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val) {
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + val;
    }
    return res;
  }
  TDynamicVector operator-(T val) {
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - val;
    }
    return res;
  }
  TDynamicVector operator*(T val) {
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] * val;
    }
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector &v) {
    if (sz != v.sz) {
      throw std::invalid_argument("v has wrong size");
    }
    TDynamicVector<T> res(sz);

    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + v.at(i);
    }
    return res;
  }
  TDynamicVector operator-(const TDynamicVector &v) {
    if (sz != v.sz) {
      throw std::invalid_argument("v has wrong size");
    }
    TDynamicVector<T> res(sz);

    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - v.at(i);
    }
    return res;
  }
  T operator*(const TDynamicVector &v) {
    if (sz != v.sz) {
      throw std::invalid_argument("v has wrong size");
    }
    T res = 0;

    for (size_t i = 0; i < sz; i++) {
      res += pMem[i] * v.at(i);
    }
    return res;
  }

  friend void swap(TDynamicVector &lhs, TDynamicVector &rhs) noexcept {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream &operator>>(std::istream &istr, TDynamicVector &v) {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend std::ostream &operator<<(std::ostream &ostr, const TDynamicVector &v) {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};

// Динамическая матрица -
// шаблонная матрица на динамической памяти
template <typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
    if (sz > MAX_MATRIX_SIZE) {
      throw std::out_of_range("Vector size is too big");
    }
    for (size_t i = 0; i < sz; i++) {
      pMem[i] = TDynamicVector<T>(sz);
    }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix &m) const noexcept {
    if (sz != m.sz) {
      return false;
    }

    for (size_t i = 0; i < sz; i++) {
      if (this->at(i) != m.at(i)) {
        return false;
      }
    }

    return true;
  }

  bool operator!=(const TDynamicMatrix &m) const noexcept {
    return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T &val) {
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] * val;
    }

    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T> &v) {
    if (sz != v.sz) {
      throw std::invalid_argument("v's size is wrong");
    }
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i] = pMem[i][j] * v[j];
      }
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix &m) {
    if (sz != m.sz) {
      throw std::invalid_argument("m's size is wrong");
    }
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = pMem[i][j] + m.pMem[j][i];
      }
    }
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix &m) {
    if (sz != m.sz) {
      throw std::invalid_argument("m's size is wrong");
    }
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = pMem[i][j] - m.pMem[j][i];
      }
    }
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix &m) {
    if (sz != m.sz) {
      throw std::invalid_argument("m's size is wrong");
    }
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = pMem[i][j] * m.pMem[j][i];
      }
    }
    return res;
  }

  // ввод/вывод
  friend std::istream &operator>>(std::istream &istr, TDynamicMatrix &v) {
    return istr;
  }
  friend std::ostream &operator<<(std::ostream &ostr, const TDynamicMatrix &v) {
    return ostr;
  }
};

#endif
