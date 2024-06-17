#include <clrs/intro_sort.hpp>

#include "check_container.hpp"
#include "props_sort.hpp"

CLRS_DEFINE_PROP_SORT(prop_intro_sort, clrs::intro_sort)

TEST(IntroSort, Sorts) {
  check_container<unsigned int>(prop_intro_sort());
  check_container<int>(prop_intro_sort());
  check_container<std::string>(prop_intro_sort());
}

