#ifndef CLRS_CHECK_CONTAINER
#define CLRS_CHECK_CONTAINER

#include <gtest/gtest.h>
#include <autocheck/autocheck.hpp>

template <typename T = int, typename Property>
void check_container(Property prop, bool verbose = false, size_t n = 100) {
  namespace ac = autocheck;
  ac::check<std::vector<T>>(prop,
      n,
      ac::make_arbitrary<std::vector<T>>(),
      ac::gtest_reporter(),
      ac::classifier<std::vector<T>>(),
      verbose);
}

#endif

