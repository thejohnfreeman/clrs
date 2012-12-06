#include <gtest/gtest.h>

#include <clrs/binomial_heap.hpp>

TEST(BinomialHeap, Push) {
  clrs::binomial_heap<int> bh;
  bh.push(16);
  bh.push(42);
  bh.push(23);
}

TEST(BinomialHeap, Empty) {
  clrs::binomial_heap<int> bh;
  bh.push(16);
  bh.push(42);
  bh.push(23);
  ASSERT_TRUE(!bh.empty());
}

TEST(BinomialHeap, Size) {
  clrs::binomial_heap<int> bh;
  bh.push(16);
  bh.push(42);
  bh.push(23);
  ASSERT_EQ(3, bh.size());
}

TEST(BinomialHeap, Top) {
  clrs::binomial_heap<int> bh;
  bh.push(16);
  ASSERT_EQ(16, bh.top());
  bh.push(42);
  ASSERT_EQ(42, bh.top());
  bh.push(23);
  ASSERT_EQ(42, bh.top());
}

TEST(BinomialHeap, Pop) {
  clrs::binomial_heap<int> bh;
  bh.push(16);
  bh.push(42);
  bh.push(23);
  ASSERT_EQ(42, bh.top());
  bh.pop();
  ASSERT_EQ(23, bh.top());
  bh.pop();
  ASSERT_EQ(16, bh.top());
  bh.pop();
  ASSERT_TRUE(bh.empty());
}

TEST(BinomialHeap, Print) {
  clrs::binomial_heap<int, std::greater<int>> bh;
  bh.push(27);
  bh.push(11);
  bh.push(17);
  bh.push(8);

  bh.push(38);
  bh.push(14);
  bh.push(29);
  bh.push(6);

  bh.push(18);
  bh.push(12);
  bh.push(25);
  bh.push(1);

  bh.push(10);
#ifndef NDEBUG
  print(std::clog, bh);
#endif
}

TEST(BinomialHeap, Merge) {
  clrs::binomial_heap<int, std::greater<int>> bh1;
  bh1.push(41);
  bh1.push(28);
  bh1.push(33);
  bh1.push(15);
  bh1.push(25);
  bh1.push(7);
  bh1.push(12);

  clrs::binomial_heap<int, std::greater<int>> bh2;
  bh2.push(55);
  bh2.push(45);
  bh2.push(32);
  bh2.push(30);

  bh2.push(24);
  bh2.push(23);
  bh2.push(22);
  bh2.push(8);

  bh2.push(50);
  bh2.push(48);
  bh2.push(31);
  bh2.push(29);

  bh2.push(17);
  bh2.push(10);
  bh2.push(44);
  bh2.push(6);

  bh2.push(37);
  bh2.push(3);
  bh2.push(18);

#ifndef NDEBUG
  print(std::clog, bh1);
  print(std::clog, bh2);
#endif

  bh1.absorb(std::move(bh2));
#ifndef NDEBUG
  print(std::clog, bh1);
  print(std::clog, bh2);
#endif
}

TEST(BinomialHeap, Leaks) {
#ifndef NDEBUG
  ASSERT_EQ(0, clrs::binomial_tree<int>::leaks());
#endif
}

