#include <clrs/02.01-insertion-sort.hpp>

#include "common.hpp"

int main() {
  test_sort<int>(&clrs::insertion_sort<int>);
  return 0;
}

