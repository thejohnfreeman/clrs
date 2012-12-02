#ifndef CLRS_06_01_HEAP_SORT
#define CLRS_06_01_HEAP_SORT

#include <functional>
#include <utility>

#include "heap.hpp"

#define VAL_T typename std::iterator_traits<RandomIt>::value_type

namespace clrs {

  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void heap_sort(RandomIt begin, RandomIt end, Compare comp = Compare()) {
    clrs::make_heap(begin, end, comp);
    while (end != begin) {
      clrs::pop_heap(begin, end--, comp);
    }
  }

}

#endif

