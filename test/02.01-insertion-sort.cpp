#include <clrs/02.01-insertion-sort.hpp>

#include "SortTest.hpp"

TEST_F(SortTest, InsertionSort) {
  test(&clrs::insertion_sort<int>);
}

