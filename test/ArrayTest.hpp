#ifndef CLRS_ARRAY_TEST
#define CLRS_ARRAY_TEST

#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

struct ArrayTest : public ::testing::Test {

  template <typename T = int, typename Gen = std::minstd_rand>
  std::vector<T> sample(size_t n = 10000, Gen gen = Gen()) {
    std::vector<T> A;
    A.reserve(n);
    std::generate_n(std::back_inserter(A), n, gen);
    return A;
  }

  template <typename T>
  std::string take(size_t n, std::vector<T> A) {
    std::ostringstream s;
    std::copy_n(A.begin(), std::min(n, A.size()),
        std::ostream_iterator<T>(s, ", "));
    if (n < A.size()) s << "...";
    return s.str();
  }

};

#endif

