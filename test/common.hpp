#ifndef CLRS_TEST_COMMON
#define CLRS_TEST_COMMON

#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

template <typename T = int, typename F>
void test_sort(const F& sort) {
  const std::size_t n = 10000;
  T A[n];
  std::generate_n(A, n, std::minstd_rand());

  sort(A, n);
  assert(std::is_sorted(A, A + n));
}

#endif

