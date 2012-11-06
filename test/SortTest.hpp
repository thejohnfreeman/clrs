#ifndef CLRS_SORT_TEST
#define CLRS_SORT_TEST

#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

#include "ArrayTest.hpp"

struct SortTest : public ArrayTest {

  template <typename T = int, typename F, typename Cmp = std::less<T>,
            typename Gen = std::minstd_rand>
  void test(F sort, size_t n = 10000, Cmp cmp = Cmp(), Gen gen = Gen()) {
    std::vector<T> A(sample(n, gen));
    sort(A.data(), n, cmp);
    ASSERT_TRUE(std::is_sorted(A.begin(), A.end()));
  }

};

#endif

