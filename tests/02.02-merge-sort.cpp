#include <clrs/merge_sort.hpp>

#include "check_container.hpp"
#include "props_sort.hpp"

CLRS_DEFINE_PROP_SORT(prop_merge_sort, clrs::merge_sort)

TEST(MergeSort, Sorts) {
  check_container<unsigned int>(prop_merge_sort());
  check_container<int>(prop_merge_sort());
  check_container<std::string>(prop_merge_sort());
}

