#ifndef CLRS_TEST_COMMON
#define CLRS_TEST_COMMON

#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

template <typename T = int, typename F>
void test_sort(const F& sort, size_t n = 10000) {
  std::vector<T> A((n));
  std::generate_n(A.data(), n, std::minstd_rand());

  sort(A.data(), n);
  assert(std::is_sorted(A.begin(), A.end()));
}

#endif

