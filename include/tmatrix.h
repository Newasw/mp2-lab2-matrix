#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
using namespace std;

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
    if (sz <= 0){
      throw out_of_range("Vector size should be greater than zero");
    }
    if (sz > MAX_VECTOR_SIZE){
        throw out_of_range("Vector size should be < MAX_VECTOR_SIZE");
    }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz <= 0){
        throw out_of_range("Vector size should be greater than zero");
    }
    if (sz > MAX_VECTOR_SIZE){
        throw out_of_range("Vector size should be < MAX_VECTOR_SIZE");
    }
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : TDynamicVector(v.pMem, v.sz)
  {
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) {
          return *this;
      }
      else {
          *this = TDynamicVector(v);
          return *this;
      }
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (&v == this) {
          return *this;
      }

      if (sz != v.sz) {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind) // почему нельзя было просто i написать :(
  {
  
      return at(ind);
  }
  const T& operator[](size_t ind) const
  {
 
      return at(ind);
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0) {
          throw out_of_range("Negative index");
      }
      if (ind >= sz) {
          throw out_of_range("ERROR");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0) {
          throw out_of_range("Negative index");
      }
      if (ind >= sz) {
          throw out_of_range("ERROR");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz){
          return false;
      }

      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(this->sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(double val) // а тут не должно быть тоже Т? ну, да и ладно 
  {
      TDynamicVector res(this->sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector res(this->sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz){
          throw (" size after '+' is undefined");
      }
      TDynamicVector res(this->sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw (" size after '-' is undefined");
      }
      TDynamicVector res(this->sz);
      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - v.pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw (" size after '*' is undefined");
      }
      T res = 0;
      for (int i = 0; i < sz; i++)
          res = res + pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
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
    if (s > MAX_MATRIX_SIZE) {
          throw out_of_range("Vector size should be < MAX_VECTOR_SIZE");
    }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix& operator=(const TDynamicMatrix& m)
  {
      if (this == &m) { 
          return *this; 
      }

      else 
      {
          TDynamicVector<T>* tmp = new TDynamicVector<T>[m.sz];
          delete[] pMem;
          sz = m.sz;
          pMem = tmp;
          for (size_t i = 0; i < sz; i++){
              pMem[i] = m.pMem[i];
          }

          return *this;
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  size_t size() const noexcept { return sz; }
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) { 
          return false; 
      }
      for (size_t i = 0; i < sz; i++){
          if (pMem[i] != m.pMem[i]) { 
              return false; 
          }
      }
      return true;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }
  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }

      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) {
          throw ("ERROR whis sizes");
      }

      TDynamicVector<T> res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * v;

      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw ("ERROR whis sizes");
      }

      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++){
          res.pMem[i] = pMem[i] + m.pMem[i];
      }

      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw ("ERROR whis sizes");
      }

      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }

      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw ("ERROR whis sizes");
      }

      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++){
          for (size_t j = 0; j < sz; j++){
              for (size_t f = 0; f < sz; f++){
                  res[i][j] += pMem[i][f] * m.pMem[f][j];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
