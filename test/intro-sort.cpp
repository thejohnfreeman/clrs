#include <clrs/intro_sort.hpp>

#include "SortTest.hpp"

CLRS_DEFINE_SORTER_T(intro_sorter, clrs::intro_sort)

TEST_F(SortTest, IntroSort) {
  test(intro_sorter());
}


