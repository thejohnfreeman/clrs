#include <clrs/quick_sort.hpp>

#include "SortTest.hpp"

TEST_F(SortTest, QuickSort) {
  test(&clrs::quick_sort<int>);
}


