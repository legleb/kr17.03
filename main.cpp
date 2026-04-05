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

bool testInsert()
{
  auto v = topit::Vector< int >();
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.insert(1, 8);
  v.insert(0, 7);
  v.insert(4, 5);
  int c[] = {7, 1, 8, 2, 5, 3};
  bool r = v.getSize() == 6;
  for (size_t i = 0; r && i < v.getSize(); i++)
  {
    r = r && (v[i] == c[i]);
  }
  return r;
}

bool testRangeInsert()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  topit::Vector< int > v2;
  v2.pushBack(5);
  v2.pushBack(6);
  v2.pushBack(7);
  v2.pushBack(8);
  v2.insert(1, v, 0, 3);
  int c[] = {5, 1, 2, 3, 6, 7, 8};
  bool r = v2.getSize() == 7;
  for (size_t i = 0; r && i < v.getSize(); i++) {
    r = r && (v2[i] == c[i]);
  }
  try
  {
    v2.insert(7, v, 0, 100);
    r = false;
  }
  catch (const std::out_of_range& e)
  {}
  return r;
}

bool testErase()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.erase(2);
  int c[] = {1, 2, 4};
  bool r = v.getSize() == 3;
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    r = r && v[i] == c[i];
  }
  try
  {
    v.erase(100);
    return false;
  }
  catch (const std::out_of_range& e)
  {}
  return r;
}

bool testRangeErase()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  v.pushBack(6);
  v.erase(2, 3);
  int c[] = {1, 2, 6};
  bool r = v.getSize() == 3;
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    r = r && v[i] == c[i];
  }
  try
  {
    v.erase(100, 102);
    return false;
  }
  catch (const std::out_of_range& e)
  {}
  return r;
}

bool testMoveInsertWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(v.cbegin() + 1, std::move(2));
  bool r = v.getSize() == 3;
  r = r && (v[0] == 1);
  r = r && (v[1] == 2);
  r = r && (v[2] == 3);
  return r;
}

bool testInsertWithIterator()
{
  auto v = topit::Vector< int >();
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  auto it = v.cbegin() + 1;
  v.insert(it, 8);
  it = v.cbegin() + 3;
  v.insert(it, 7);
  it = v.cbegin() + 5;
  v.insert(it, 12);
  it = v.cbegin();
  v.insert(it, 23);
  it = v.cend();
  v.insert(it, 8);
  int c[] = {23, 1, 8, 2, 7, 3, 12, 4, 5, 8};
  bool r = v.getSize() == 10;
  for (size_t i = 0; r && i < v.getSize(); i++)
  {
    r = r && (v[i] == c[i]);
  }
  return r;
}

bool testRangeInsertWithIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  topit::Vector< int > v2;
  v2.pushBack(6);
  v2.pushBack(7);
  v2.pushBack(8);
  v2.pushBack(9);
  v2.pushBack(10);
  auto start = v.cbegin() + 1;
  auto end = v.cbegin() + 4;
  v2.insert(v2.cbegin() + 2, start, end);
  int c[] = {6, 7, 2, 3, 4, 8, 9, 10};
  bool r = v2.getSize() == 8;
  for (size_t i = 0; r && i < v.getSize(); i++)
  {
    r = r && (v2[i] == c[i]);
  }
  try
  {
    v2.insert(v2.cbegin() + 100, v.cbegin(), v.cend());
    r = false;
  }
  catch (const std::out_of_range& e)
  {}
  return r;
}

bool testEraseIterator()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  auto it = v.cbegin() + 1;
  auto ret = v.erase(it);
  bool r = v.getSize() == 3;
  r = r && (v.at(0) == 1);
  r = r && (v.at(1) == 3);
  r = r && (v.at(2) == 4);
  r = r && (*ret == 3);
  return r;
}

bool testRangeEraseWithIterator()
{
  topit::Vector< int > v;
  for (int i = 1; i <= 5; ++i)
  {
    v.pushBack(i);
  }
  auto start = v.cbegin() + 1;
  auto end = v.cbegin() + 3;
  auto ret = v.erase(start, end);
  bool r = v.getSize() == 3;
  r = r && (v.at(0) == 1);
  r = r && (v.at(1) == 4);
  r = r && (v.at(2) == 5);
  r = r && (*ret == 4);
  return r;
}

bool even(int v)
{
  return v % 2 == 0;
}

bool testErasePredicate()
{
  topit::Vector< int > v;
  for (int i = 1; i <= 5; ++i)
  {
    v.pushBack(i);
  }
  auto ret = v.erase(v.cbegin(), v.cend(), even);
  bool r = v.getSize() == 3;
  r = r && (v.at(0) == 1);
  r = r && (v.at(1) == 3);
  r = r && (v.at(2) == 5);
  r = r && (ret == v.cbegin());
  return r;
}

bool testInitializerList()
{
  topit::Vector< int > v{1, 2};
  return v.getSize() == 2 && (v[0] == 1) && (v[1] == 2);
}

bool testReserveEmpty()
{
  topit::Vector< int > v;
  v.reserve(10);
  bool res = (v.getCapacity() >= 10);
  res = res && (v.getSize() == 0);
  return res;
}

bool testReserveNoChange()
{
  topit::Vector< int > v{5, 2};
  size_t old_cap = v.getCapacity();
  v.reserve(2);
  return v.getCapacity() == old_cap;
}

bool testReserveIncrease()
{
  topit::Vector< int > v{5, 2};
  v.reserve(10);
  bool res = (v.getCapacity() >= 10);
  res = res && (v.getSize() == 2);
  return res && v[0] == 5 && v[1] == 2;
}

bool testShrinkToFitNoChange()
{
  topit::Vector< int > v{2, 5};
  v.shrinkToFit();
  bool res = (v.getCapacity() == v.getSize());
  res = res && (v.getSize() == 2);
  return res;
}

bool testShrinkToFitReduce()
{
  topit::Vector< int > v{5, 2};
  v.reserve(10);
  v.shrinkToFit();
  bool res = (v.getCapacity() >= 2);
  res = res && (v.getSize() == 2);
  res = res && (v[0] == 5 && v[1] == 2);
  return res;
}

bool testShrinkToFitEmpty()
{
  topit::Vector< int > v;
  v.shrinkToFit();
  return v.isEmpty() && (v.getCapacity() == 0);
}

bool testPushBackCountZero()
{
  topit::Vector< int > v{3, 5};
  v.pushBackCount(0, 99);
  return v.getSize() == 2;
}

bool testPushBackCountSome()
{
  topit::Vector< int > v{3, 5};

  v.pushBackCount(3, 2);
  bool res = v.getSize() == 5;
  res = res && (v[0] == 3 && v[1] == 5);
  res = res && (v[2] == 2 && v[3] == 2 && v[4] == 2);
  return res;
}

bool testPushBackCountGrow()
{
  topit::Vector< int > v{5, 2};
  v.pushBackCount(10, 2);
  bool res = (v.getSize() == 12);
  res = res && (v.getCapacity() >= 12);
  res = res && v[11] == 2;
  return res;
}

bool testPushBackRangeZero()
{
  topit::Vector< int > v{3, 5};
  int arr[] = {1, 2, 3};
  v.pushBackRange(arr, 0);
  return v.getSize() == 2;
}

bool testPushBackRangeFromArray()
{
  topit::Vector< int > v{3, 5};
  int arr[] = {10, 20, 30};
  v.pushBackRange(arr, 3);
  bool res = (v.getSize() == 5);
  res = res && (v[0] == 3 && v[1] == 5);
  res = res && (v[2] == 10 && v[3] == 20 && v[4] == 30);
  return res;
}

bool testPushBackRangeFromVector()
{
  topit::Vector< int > v{3, 5};
  topit::Vector< int > src{10, 20};
  v.pushBackRange(src.begin(), src.getSize());
  bool res = (v.getSize() == 4);
  res = res && (v[2] == 10 && v[3] == 20);
  return res;
}

bool testPushBackRangeGrow()
{
  topit::Vector<int> v{2, 5};
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  v.pushBackRange(arr, 10);
  bool res = (v.getSize() == 12);
  res = res && (v.getCapacity() >= 12);
  res = res && (v[11] == 10);
  return res;
}

bool testUnsafePushBackBasic()
{
  topit::Vector< int > v{3, 5};
  v.reserve(5);
  v.unsafePushBack(99);
  bool res = (v.getSize() == 3);
  res = res && (v[2] == 99);
  return res;
}

bool testUnsafePushBackMultiple()
{
  topit::Vector< int > v{2, 5};
  v.reserve(5);
  v.unsafePushBack(1);
  v.unsafePushBack(2);
  v.unsafePushBack(3);
  bool res = (v.getSize() == 5);
  res = res && (v[0] == 2 && v[1] == 5);
  res = res && (v[2] == 1 && v[3] == 2 && v[4] == 3);
  return res;
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
    { "Move assignment", testMoveAssignment},
    { "Insert", testInsert },
    { "Range insert", testRangeInsert },
    { "Erase", testErase },
    { "Range erase", testRangeErase },
    { "Move insert with iterator", testMoveInsertWithIterator },
    { "Insert with iterator", testInsertWithIterator },
    { "Insert by range with iterator", testRangeInsertWithIterator },
    { "Erase Iterator", testEraseIterator },
    { "Erase Iterator Range", testRangeEraseWithIterator },
    { "Erase Predicate", testErasePredicate },
    { "Non-empty vector for non-empty initializer list", testInitializerList },
    { "Reserve empty", testReserveEmpty },
    { "Reserve no change", testReserveNoChange },
    { "Reserve increase", testReserveIncrease },
    { "Shrink to fit no change", testShrinkToFitNoChange },
    { "Shrink to fit reduce", testShrinkToFitReduce },
    { "Shrink to fit empty", testShrinkToFitEmpty },
    { "Push back count zero", testPushBackCountZero },
    { "Push back count some", testPushBackCountSome },
    { "Push back count grow", testPushBackCountGrow },
    { "Push back range zero", testPushBackRangeZero },
    { "Push back range from array", testPushBackRangeFromArray },
    { "Push back range from vector", testPushBackRangeFromVector },
    { "Push back range grow", testPushBackRangeGrow },
    { "Unsafe push back basic", testUnsafePushBackBasic },
    { "Unsafe push back multiple", testUnsafePushBackMultiple },
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
}
