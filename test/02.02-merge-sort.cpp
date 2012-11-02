#include <clrs/02.02-merge-sort.hpp>

#include "SortTest.hpp"

TEST_F(SortTest, MergeSort) {
  test(&clrs::merge_sort<int>);
}


