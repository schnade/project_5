#include "List.hpp"

#include "unit_test_framework.hpp"

using namespace std;
// Add your test cases here
TEST(test_stub) {
  ASSERT_TRUE(true);
}

TEST(empty) {
  List<int> emptyList;

  ASSERT_TRUE(emptyList.empty());
  ASSERT_EQUAL(emptyList.size(), 0);
  ASSERT_TRUE(emptyList.begin() == emptyList.end());
}

TEST(defaultIterator) {
  List<int>::Iterator one;
  List<int>::Iterator two;

  ASSERT_TRUE(one == two);

  List<int> list;
  ASSERT_TRUE(list.begin() == list.end());
  ASSERT_TRUE(one != list.end());
  ASSERT_TRUE(two != list.end());
}

TEST(pushPopBacks) {
  List<int> zeroToOne;
  zeroToOne.push_back(1);

  ASSERT_FALSE(zeroToOne.empty());
  ASSERT_EQUAL(zeroToOne.size(), 1);
  ASSERT_EQUAL(zeroToOne.front(), 1);
  ASSERT_EQUAL(zeroToOne.back(), 1);

  zeroToOne.pop_back();
  ASSERT_TRUE(zeroToOne.empty());
  ASSERT_EQUAL(zeroToOne.size(), 0);
  ASSERT_TRUE(zeroToOne.begin() == zeroToOne.end());
}

TEST(diffOrderPushBackFronts) {
  List<int> ordered;
  ordered.push_front(2);
  ordered.push_back(3);
  ordered.push_front(1);

  ASSERT_EQUAL(ordered.size(), 3);
  ASSERT_EQUAL(ordered.front(), 1);
  ASSERT_EQUAL(ordered.back(), 3);

  List<int>::Iterator it = ordered.begin();

  ASSERT_EQUAL(*it, 1);
  it++;
  ASSERT_EQUAL(*it, 2);
  it++;
  ASSERT_EQUAL(*it, 3);
}
TEST(popFrontBacks) {
  List<int> popped;
  popped.push_back(1);
  popped.push_back(2);
  popped.push_back(3);
  popped.pop_front();

  ASSERT_EQUAL(popped.front(), 2);
  ASSERT_EQUAL(popped.back(), 3);
  ASSERT_EQUAL(popped.size(), 2);
  
  popped.pop_back();
  ASSERT_EQUAL(popped.front(), 2);
  ASSERT_EQUAL(popped.back(), 2);
  ASSERT_EQUAL(popped.size(), 1);
}
TEST(clear) {
  List<int> list;
  for (int i = 0; i < 10; i++) {
    list.push_back(i);
  }
  list.clear();

  ASSERT_TRUE(list.empty());
  ASSERT_EQUAL(list.size(), 0);
  ASSERT_TRUE(list.begin() == list.end());
}

TEST(popUntilEmpty) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.pop_back();
  list.pop_back();

  ASSERT_TRUE(list.empty());
  ASSERT_TRUE(list.begin() == list.end());

  list.push_back(5);
  ASSERT_EQUAL(list.front(), 5);
}

TEST(backwardsIteration) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  List<int>::Iterator it = list.end();
  --it;
  ASSERT_EQUAL(*it, 3);
  --it;
  ASSERT_EQUAL(*it, 2);
  --it;
  ASSERT_EQUAL(*it, 1);
}
TEST(postfixIncrement) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);

  List<int>::Iterator it = list.begin();
  List<int>::Iterator old = it++;
  ASSERT_EQUAL(*old, 1);
  ASSERT_EQUAL(*it, 2);
}

TEST(insert) {
  List<int> list;
  list.push_back(2);
  list.push_back(3);

  List<int>::Iterator it = list.begin();
  List<int>::Iterator insertedOne = list.insert(it, 1);
  ASSERT_EQUAL(*insertedOne, 1);
  ASSERT_EQUAL(list.front(), 1);
  it = list.begin();
  ++it;

  List<int>::Iterator insertedTwo = list.insert(it, 3);
  ASSERT_EQUAL(*insertedTwo, 3);

  List<int>::Iterator insertedThree = list.insert(list.end(), 5);
  ASSERT_EQUAL(*insertedThree, 5);
  ASSERT_EQUAL(list.back(), 5);
  int expected[] = {1, 3, 2, 3, 5};
  int i = 0;
  for (List<int>::Iterator iter = list.begin(); iter != list.end(); ++iter) {
    ASSERT_EQUAL(*iter, expected[i]);
    ++i;
  }
}

TEST(insertIntoEmpty) {
  List<int> list;

  List<int>::Iterator it = list.insert(list.begin(), 5);
  ASSERT_EQUAL(list.size(), 1);
  ASSERT_EQUAL(list.front(), 5);
  ASSERT_EQUAL(list.back(), 5);
  ASSERT_EQUAL(*it, 5);
}

TEST(iteratorAfterInsert) {
  List<int> list;
  list.push_back(1);
  list.push_back(3);

  List<int>::Iterator it = list.begin();
  ++it;
  list.insert(it, 2);
  it = list.begin();
  ASSERT_EQUAL(*it, 1);
  ++it;
  ASSERT_EQUAL(*it, 2);
  ++it;
  ASSERT_EQUAL(*it, 3);
}
TEST(erase) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  List<int>::Iterator it = list.begin();
  List<int>::Iterator after = list.erase(it);

  ASSERT_EQUAL(*after, 2);
  ASSERT_EQUAL(list.front(), 2);

  it = list.begin();
  ++it;
  after = list.erase(it);

  ASSERT_EQUAL(*after, 4);

  it = list.begin();
  ++it;
  after = list.erase(it);

  ASSERT_TRUE(after == list.end());
  ASSERT_EQUAL(list.back(), 2);
  ASSERT_EQUAL(list.size(), 1);
}
TEST(eraseLastElement) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);

  List<int>::Iterator it = list.begin();
  ++it;

  List<int>::Iterator result = list.erase(it);
  ASSERT_TRUE(result == list.end());
  ASSERT_EQUAL(list.back(), 1);
  ASSERT_EQUAL(list.size(), 1);
}

TEST(eraseOnlyElement) {
  List<int> list;
  list.push_back(10);

  List<int>::Iterator it = list.begin();
  List<int>::Iterator result = list.erase(it);
  ASSERT_TRUE(list.empty());
  ASSERT_TRUE(result == list.end());
}

TEST(copyCtor) {
  List<int> a;
  a.push_back(1);
  a.push_back(2);
  List<int> b(a);
  a.pop_back();
  ASSERT_EQUAL(a.size(), 1);
  ASSERT_EQUAL(b.size(), 2);
  ASSERT_EQUAL(b.back(), 2);
}

TEST(assignmentInd) {
  List<int> a;
  a.push_back(1);
  a.push_back(2);

  List<int> b;
  b = a;
  a.pop_back();

  ASSERT_EQUAL(a.size(), 1);
  ASSERT_EQUAL(b.size(), 2);
  ASSERT_EQUAL(b.back(), 2);
}

TEST(assignmentSelf) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  
  List<int>& ref = list;
  list = ref;

  ASSERT_EQUAL(list.size(), 2);
  ASSERT_EQUAL(list.front(), 1);
  ASSERT_EQUAL(list.back(), 2);
}

TEST(assignmentOverwrite) {
  List<int> a;
  a.push_back(1);
  a.push_back(2);

  List<int> b;
  b.push_back(9);
  b.push_back(8);
  b.push_back(7);
  b = a;

  ASSERT_EQUAL(b.size(), 2);
  ASSERT_EQUAL(b.front(), 1);
  ASSERT_EQUAL(b.back(), 2);
}

TEST_MAIN()