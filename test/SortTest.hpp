#ifndef CLRS_SORT_TEST
#define CLRS_SORT_TEST

#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

#include <autocheck/autocheck.hpp>

#define CLRS_DEFINE_SORTER_T(name, sort2) \
  struct name {\
    template <typename Container>\
    bool operator() (Container& xs) {\
      Container ys(xs);\
      std::sort(xs.begin(), xs.end());\
      sort2(ys.begin(), ys.end());\
      return xs == ys;\
    }\
  };

namespace ac = autocheck;

struct SortTest : public ::testing::Test {

  template <typename T = int, typename Property>
  void test(Property prop, bool verbose = false, size_t n = 100) {
    ac::check<std::vector<T>>(prop,
        n,
        ac::make_arbitrary<std::vector<T>>(),
        ac::gtest_reporter(),
        ac::classifier<std::vector<T>>(),
        verbose);
  }

};

#endif

