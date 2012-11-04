#include <clrs/merge_sort.hpp>

#include "SortTest.hpp"

TEST_F(SortTest, MergeSort) {
  test(&clrs::merge_sort<int>);
}


