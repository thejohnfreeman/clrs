#include <clrs/heap_sort.hpp>

#include "check_container.hpp"
#include "props_sort.hpp"

CLRS_DEFINE_PROP_SORT(prop_heap_sort, clrs::heap_sort)

TEST(HeapSort, Sorts) {
  check_container<unsigned int>(prop_heap_sort());
  check_container<int>(prop_heap_sort());
  check_container<std::string>(prop_heap_sort());
}

