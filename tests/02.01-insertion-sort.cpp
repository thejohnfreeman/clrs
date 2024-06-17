#include <clrs/insertion_sort.hpp>

#include "check_container.hpp"
#include "props_sort.hpp"

CLRS_DEFINE_PROP_SORT(prop_insertion_sort, clrs::insertion_sort)

TEST(InsertionSort, Sorts) {
  check_container<unsigned int>(prop_insertion_sort());
  check_container<int>(prop_insertion_sort());
  check_container<std::string>(prop_insertion_sort());
}

