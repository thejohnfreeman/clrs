#include <clrs/insertion_sort.hpp>

#include "SortTest.hpp"

CLRS_DEFINE_SORTER_T(insertion_sorter, clrs::insertion_sort)

TEST_F(SortTest, InsertionSort) {
  test(insertion_sorter());
}

