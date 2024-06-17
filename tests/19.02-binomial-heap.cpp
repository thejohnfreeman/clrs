#include <gtest/gtest.h>

#include <clrs/binomial_heap.hpp>

#include "check_container.hpp"
#include "props_heap.hpp"

#define CHECK_PROP(name, type) \
  check_container<type>(prop_heap_##name<clrs::binomial_heap<type>>());

TEST(BinomialHeap, Empty) {
  CHECK_PROP(empty, int);
  CHECK_PROP(empty, std::string);
}

TEST(BinomialHeap, Size) {
  CHECK_PROP(size, int);
  CHECK_PROP(size, std::string);
}

TEST(BinomialHeap, Top) {
  CHECK_PROP(top, int);
  CHECK_PROP(top, std::string);
}

TEST(BinomialHeap, Pop) {
  CHECK_PROP(pop, int);
  CHECK_PROP(pop, std::string);
}

TEST(BinomialHeap, Sort) {
  CHECK_PROP(sort, int);
  CHECK_PROP(sort, std::string);
}

TEST(BinomialHeap, Print) {
  clrs::binomial_heap<int, std::greater<int>> bh = {
    27, 11, 17, 8, 38, 14, 29, 6, 18, 12, 25, 1, 10
  };
#ifndef NDEBUG
  print(std::clog, bh);
#endif
}

TEST(BinomialHeap, Merge) {
  clrs::binomial_heap<int, std::greater<int>> bh1 = {
    41, 28, 33, 15, 25, 7, 12
  };

  clrs::binomial_heap<int, std::greater<int>> bh2 = {
    55, 45, 32, 30, 24, 23, 22, 8, 50, 48, 31, 29, 17, 10, 44, 6, 37, 3, 18
  };

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
  ASSERT_EQ(0, clrs::binomial_tree<std::string>::leaks());
#endif
}

