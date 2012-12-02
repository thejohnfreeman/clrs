#include <clrs/heap_sort.hpp>

#include "SortTest.hpp"

CLRS_DEFINE_SORTER_T(heap_sorter, clrs::heap_sort)

TEST_F(SortTest, HeapSort) {
  test(heap_sorter());
}

