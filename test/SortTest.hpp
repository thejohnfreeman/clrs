#ifndef CLRS_SORT_TEST
#define CLRS_SORT_TEST

#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

struct SortTest : public ::testing::Test {

  template <typename T = int, typename F, typename Cmp = std::less<T>>
  void test(const F& sort, size_t n = 10000, const Cmp& cmp = Cmp()) {
    std::vector<T> A((n));
    std::generate_n(A.data(), n, std::minstd_rand());
    sort(A.data(), n, cmp);
    ASSERT_TRUE(std::is_sorted(A.begin(), A.end()));
  }

};

#endif

