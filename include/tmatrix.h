// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz == 0) throw std::out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE) throw std::out_of_range("Vector size should be lesser than 100.000.000");
      pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(const T* arr, size_t s) : sz(s)
  {
      if (arr == nullptr) throw std::invalid_argument("TDynamicVector ctor requires non-nullptr arg");
      if (sz == 0) throw std::out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE) throw std::out_of_range("Vector size should be lesser than 100.000.000");
      pMem = new T[sz]();
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz]();
      std::copy(v.pMem, v.pMem + sz, pMem); 
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz]();
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw std::out_of_range("Invalid index");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw std::out_of_range("Invalid index");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; ++i) {
          if (pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(const T& val) const
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < res.sz; ++i) {
          res.pMem[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(const T& val) const
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < res.sz; ++i) {
          res.pMem[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(const T& val) const
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < res.sz; ++i) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const
  {
      if (sz != v.sz) throw std::invalid_argument("Vectors must be equal size");
      TDynamicVector res(sz);
      for (size_t i = 0; i < res.sz; ++i) {
          res.pMem[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v) const
  {
      if (sz != v.sz) throw std::invalid_argument("Vectors must be equal size");
      TDynamicVector res(sz);
      for (size_t i = 0; i < res.sz; ++i) {
          res.pMem[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) const
  {
      if (sz != v.sz) throw std::invalid_argument("Vectors must be equal size");
      T res = T();
      for (size_t i = 0; i < sz; ++i) {
          res += pMem[i] * v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz == 0) throw std::out_of_range("Matrix size should be greater than zero");
      if (sz > MAX_MATRIX_SIZE) throw std::out_of_range("Matrix size should be lesser than 10.000x10.000");
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(sz);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  
  size_t size() const noexcept { return sz; }

  T& at(size_t row, size_t col)
  {
      if (row >= sz || col >= sz) throw std::out_of_range("Invalid index");
      return pMem[row][col];
  }
  const T& at(size_t row, size_t col) const
  {
      if (row >= sz || col >= sz) throw std::out_of_range("Invalid index");
      return pMem[row][col];
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < sz; ++i) {
          if (pMem[i] != m.pMem[i]) return false;
      }
      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val) const
  {
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; ++i) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (sz != v.size()) throw std::invalid_argument("Matrix and vector sizes must match");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; ++i) {
          res[i] = pMem[i] * v;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
      // можно ли написать реализацию, используя operator+ вектора?
      if (sz != m.sz) throw std::invalid_argument("Matrices must be equal size");
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; ++i) {
          res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) const
  {
      if (sz != m.sz) throw std::invalid_argument("Matrices must be equal size");
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; ++i) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      if (sz != m.sz) throw std::invalid_argument("Matrices must be equal size");
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; ++i) {
          for (size_t k = 0; k < sz; ++k) {
              for (size_t j = 0; j < sz; ++j) {
                  res.pMem[i][k] += pMem[i][j] * m.pMem[j][k];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; ++i) {
          istr >> m.pMem[i];
      }
      return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; ++i) {
          ostr << m.pMem[i] << std::endl;
      }
      return ostr;
  }
};

#endif
