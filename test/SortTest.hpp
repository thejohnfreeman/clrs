#ifndef CLRS_SORT_TEST
#define CLRS_SORT_TEST

#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

#include <autocheck/autocheck.hpp>

#define CLRS_DEFINE_SORTER_T(name, sort) \
  struct name {\
    template <typename Container>\
    bool operator() (Container& xs) {\
      sort(xs.begin(), xs.end());\
      using namespace autocheck;\
      return std::is_sorted(xs.begin(), xs.end());\
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

