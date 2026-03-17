#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector
  {
    ~Vector();
    Vector();
    bool isEmpty() const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;
  };
}

template< class T >
topit::Vector< T >::~Vector()
{}

template< class T >
topit::Vector< T >::Vector():
  data_(), size_(), capacity_()
{}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return false;
}
#endif
