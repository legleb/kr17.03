#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  // std::cout << __func__ << "\n";
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testGetSize()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.popBack();
  return v.getSize() == 2;
}

bool testGetCapacity()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getCapacity() == 4;
}

bool testElementInboudAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    int & val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboudConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > & rv = v;
  try
  {
    const int & val = rv.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav(v);
  return v == yav;
}

bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  try
  {
    return yav.getSize() == v.getSize() && yav.at(0) == v.at(0);
  }
  catch(...)
  {
    return false;
  }
}

bool testMoveConstructor()
{
  topit::Vector< int > v1(3, 9);
  topit::Vector< int > v2(std::move(v1));
  return v1.getSize() == 0 && v2.getSize() == 3;
}

bool testCopyAssignment()
{
  topit::Vector< int > v1(4, 2);
  topit::Vector< int > v2(5, 5);
  v2 = v1;
  bool r = v2.getSize() == v1.getSize();
  for (size_t i = 0; r && i < v1.getSize(); ++i)
  {
    r = r && v1[i] == v2[i];
  }
  v2.erase(1);
  r = r && (v1.getSize() - v2.getSize() == 1);
  return r;
}

bool testMoveAssignment()
{
  topit::Vector< int > v1(4, 2);
  topit::Vector< int > v2(5, 5);
  v2 = std::move(v1);
  return v2.getSize() == 4 && v1.getSize() == 0;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    { "Empty vector", testEmptyVector },
    { "Size of vector", testGetSize },
    { "Capacity of vector", testGetCapacity },
    { "Inbound access", testElementInboudAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboudConstAccess },
    { "Out of bound const access", testElementOutOfBoundConstAccess },
    { "Copy empty vector", testCopyConstructorForEmpty },
    { "Copy non-empty vector", testCopyConstructorForNonEmpty },
    { "Move constructor", testMoveConstructor },
    { "Copy assignment", testCopyAssignment },
    { "Move assignment", testMoveAssignment}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
  // Подсчёт кол-ва пройденных / непройденных тестов
  // Выводить только непрошедшие тесты
}
