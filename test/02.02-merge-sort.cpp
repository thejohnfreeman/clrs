#include <clrs/02.02-merge-sort.hpp>

#include "common.hpp"

int main() {
  test_sort<int>(&clrs::merge_sort<int>, 10);
  return 0;
}

