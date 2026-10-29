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
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return false;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    return TDynamicMatrix<T>{};
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    return TDynamicVector<T>{};
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    // можно ли написать реализацию, используя operator+ вектора?
    return TDynamicMatrix<T>{};
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    return TDynamicMatrix<T>{};
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    return TDynamicMatrix<T>{};
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
    return ostr;
  }
};

#endif
