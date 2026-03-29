#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include "viter.hpp"

namespace topit
{
  template< class T >
  struct Vector
  {
    ~Vector();
    Vector();
    Vector(const Vector< T >&);
    Vector(Vector< T >&&) noexcept;
    Vector(size_t size, const T& init);
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&) noexcept;

    void swap(Vector< T >& rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void pushBack(const T& v);
    void popBack();

    void insert(size_t i, const T& v);
    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(size_t i);
    void erase(size_t start, size_t end);

    void topit::Vector< T >::insert(CIter< T > it, const T& v);
    void topit::Vector< T >::insert(CIter< T > it, T&& v);
    void topit::Vector< T >::insert(CIter< T > i, CIter< T > start, CIter< T > end);

    CIter< T > cbegin();
    CIter< T > cend();
    Iter< T > begin();
    Iter< T > end();

  private:
    T* data_;
    size_t size_, capacity_;
    explicit Vector(size_t size);
    template< class P >
    void uniInsert(size_t pos, P&& value);
  };
  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T > & rhs);
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr), size_(0), capacity_(0)
{}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy = rhs;
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
bool topit::operator==(const Vector< T >& lhs, const Vector< T > & rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T > *cthis = this;
  return const_cast< T & >((*cthis)[id]);
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(id));
}

template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

template< class T >
void topit::Vector< T >::pushBack(const T& v)
{
  if (size_ == capacity_)
  {
    size_t newCap = capacity_ == 0 ? 1 : capacity_ * 2;
    T* newData = new T[newCap];
    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = data_[i];
    }
    delete data_;
    data_ = newData;
    capacity_ = newCap;
  }
  data_[size_] = v;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack()
{
  if (size_)
  {
    --size_;
  }
}

template< class T >
void topit::Vector< T >::insert(size_t i, const T& v)
{
  if (i > size_)
  {
    throw std::out_of_range("Index out of range");
  }
  size_t newCap = capacity_ * 2 + 1;
  if (size_ + 1 < capacity_)
  {
    newCap = capacity_;
  }
  T* newData = new T[newCap];
  try
  {
    size_t j = 0;
    for (; j < i; ++j)
    {
      newData[j] = data_[j];
    }
    newData[i] = v;
    for (; j < size_; ++j)
    {
      newData[j + 1] = data_[j];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  size_++;
  capacity_ = newCap;
}

template< class T >
void topit::Vector< T >::insert(size_t i, const Vector< T >& rhs, size_t start, size_t end)
{
  if (i > size_)
  {
    throw std::out_of_range("Index out of range");
  }
  if (end >= rhs.getSize())
  {
    throw std::out_of_range("End of vector out of range");
  }
  size_t count = (end - start);
  size_t newCap = capacity_ + count;
  if (size_ + count < capacity_)
  {
    newCap = capacity_;
  }
  T* newData = new T[newCap];
  try
  {
    size_t j = 0;
    for (; j < i; ++j)
    {
      newData[j] = data_[j];
    }
    size_t k = 0;
    for (; k < count; ++k)
    {
      newData[j + k] = rhs.at(start + k);
    }
    for (; j < size_; ++j)
    {
      newData[j + k] = data_[j];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  size_ += count;
  capacity_ = newCap;
}

template< class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("Index out of range");
  }
  T* v = new T[size_ - 1];
  try
  {
    size_t j = 0;
    for (; j < i; ++j)
    {
      v[j] = data_[j];
    }
    for (; j < size_; ++j)
    {
      v[j] = data_[j + 1];
    }
  }
  catch (...)
  {
    delete[] v;
    throw;
  }
  delete[] data_;
  data_ = v;
  size_--;
}

template< class T >
void topit::Vector< T >::erase(size_t start, size_t end)
{
  if (start >= size_ || end >= size_ || start >= end)
  {
    throw std::out_of_range("Start out of range");
  }
  size_t count = end - start;
  T* v = new T[size_ - count];
  try
  {
    for (size_t i = 0; i < start; ++i)
    {
      v[i] = data_[i];
    }
    for (size_t i = end; i < size_; ++i)
    {
      v[i - count] = data_[i];
    }
  }
  catch (...)
  {
    delete[] v;
    throw;
  }
  delete[] data_;
  data_ = v;
  size_ -= count;
}

template< class T >
topit::CIter< T > topit::Vector< T >::cbegin()
{
  return CIter< T >(data_);
}

template< class T >
topit::CIter< T > topit::Vector< T >::cend()
{
  return CIter< T >(data_ + size_);
}

template< class T >
topit::Iter< T > topit::Vector< T >::begin()
{
  return Iter< T >(data_);
}

template< class T >
topit::Iter< T > topit::Vector< T >::end()
{
  return Iter< T >(data_ + size_);
}

template< class T >
void topit::Vector< T >::insert(CIter< T > it, const T& v)
{
  if (it < CIter< T >(data_) || it > CIter< T >(data_ + size_))
  {
    throw std::out_of_range("position out of range");
  }
  size_t pos = it - CIter< T >(data_);
  generalInsert(pos, v);
}

template< class T >
void topit::Vector< T >::insert(CIter< T > it, T&& v)
{
  if (it < CIter< T >(data_) || it > CIter< T >(data_ + size_))
  {
    throw std::out_of_range("position out of range");
  }
  size_t pos = it - CIter< T >(data_);
  generalInsert(pos, std::move(v));
}

template< class T >
void topit::Vector< T >::insert(CIter< T > i, CIter< T > start, CIter< T > end)
{
  if (i < CIter< T >(data_) || i > CIter< T >(data_ + size_))
  {
    throw std::out_of_range("iterator index is out of range");
  }

  size_t index = i - CIter< T >(data_);
  size_t count = end - start;
  if (!count)
  {
    return;
  }
  size_t newCap = capacity_;
  if (size_ + count > capacity_)
  {
    newCap = capacity_ * 2 + count;
  }
  T* newData = new T[newCap];
  try
  {
    size_t j = 0;
    for (; j < index; ++j)
    {
      newData[j] = data_[j];
    }
    for (auto it = start; it != end; ++it)
    {
      newData[j++] = *it;
    }
    for (size_t k = index; k < size_; ++k)
    {
      newData[j++] = data_[k];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  size_ += count;
  capacity_ = newCap;
}

template< class T >
template< class P >
void topit::Vector< T >::uniInsert(size_t i, P&& v)
{
  if (i > size_)
  {
    throw std::out_of_range("Index is out of range");
  }
  size_t newCap = capacity_ * 2 + 1;
  if (size_ + 1 < capacity_)
  {
    newCap = capacity_;
  }
  T* newData = new T[newCap];
  try
  {
    size_t j = 0;
    for (; j < i; ++j)
    {
      newData[j] = data_[j];
    }
    newData[i] = std::forward< P >(v);
    for (; j < size_; ++j)
    {
      newData[j + 1] = data_[j];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  size_++;
  capacity_ = newCap;
}

#endif
