#ifndef CLRS_SORT_TEST
#define CLRS_SORT_TEST

#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

#include "ArrayTest.hpp"

#define ITER_T typename std::vector<T>::iterator

struct SortTest : public ArrayTest {

  template <typename T = int, typename Compare = std::less<T>,
            typename Gen = std::minstd_rand>
  void test(std::function<void(ITER_T, ITER_T, Compare)> sort,
      size_t n = 10000, Compare comp = Compare(), Gen gen = Gen())
  {
    std::vector<T> A(sample(n, gen));
    sort(A.begin(), A.end(), comp);
    ASSERT_TRUE(std::is_sorted(A.begin(), A.end()));
  }

};

#endif

