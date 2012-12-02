#ifndef CLRS_SORT_TEST
#define CLRS_SORT_TEST

#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

#include "ArrayTest.hpp"

#define CLRS_DEFINE_SORTER_T(name, sort) \
  struct name {\
    template <typename RandomIt, typename Compare>\
    void operator() (RandomIt begin, RandomIt end, Compare comp) {\
      sort(begin, end, comp);\
    }\
  };

struct SortTest : public ArrayTest {

  template <typename T = int, typename Sort, typename Compare = std::less<T>,
            typename Gen = std::minstd_rand>
  void test(Sort sort, size_t n = 10000, Compare comp = Compare(),
      Gen gen = Gen())
  {
    std::vector<T> A(sample(n, gen));
    sort(A.begin(), A.end(), comp);
    ASSERT_TRUE(std::is_sorted(A.begin(), A.end()));
  }

};

#endif

