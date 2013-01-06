#include <clrs/merge_sort.hpp>

#include "SortTest.hpp"

CLRS_DEFINE_SORTER_T(merge_sorter, clrs::merge_sort)

TEST_F(SortTest, MergeSort) {
  test(merge_sorter());
  test<std::string>(merge_sorter());
}

