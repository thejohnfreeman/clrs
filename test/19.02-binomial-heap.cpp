#include <gtest/gtest.h>

#include <clrs/binomial_heap.hpp>

TEST(BinomialHeap, Push) {
  clrs::binomial_heap<int> bh;
  bh.push(16);
  bh.push(42);
  bh.push(23);
};

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

