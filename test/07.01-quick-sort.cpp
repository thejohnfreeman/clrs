#include <clrs/quick_sort.hpp>

#include "check_container.hpp"
#include "props_sort.hpp"

CLRS_DEFINE_PROP_SORT(prop_quick_sort, clrs::quick_sort)

TEST(QuickSort, Sorts) {
  check_container<unsigned int>(prop_quick_sort());
  check_container<int>(prop_quick_sort());
  check_container<std::string>(prop_quick_sort());
}

