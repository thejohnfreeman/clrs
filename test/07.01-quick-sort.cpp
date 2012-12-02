#include <clrs/quick_sort.hpp>

#include "SortTest.hpp"

CLRS_DEFINE_SORTER_T(quick_sorter, clrs::quick_sort)

TEST_F(SortTest, QuickSort) {
  test(quick_sorter());
}


