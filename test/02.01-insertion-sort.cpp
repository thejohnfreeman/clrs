#include <clrs/insertion_sort.hpp>

#include "SortTest.hpp"

TEST_F(SortTest, InsertionSort) {
  test(&clrs::insertion_sort<int>);
}

