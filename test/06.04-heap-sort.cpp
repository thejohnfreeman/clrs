#include <clrs/heap_sort.hpp>

#include "SortTest.hpp"

TEST_F(SortTest, HeapSort) {
  test(clrs::heap_sort<std::vector<int>::iterator>);
  //test(clrs::heap_sort);
}

