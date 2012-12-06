#ifndef CLRS_INTRO_SORT
#define CLRS_INTRO_SORT

#include <functional>
#include <cassert>
#include <cmath>

#include "quick_sort.hpp"
#include "heap_sort.hpp"

namespace clrs {

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void intro_sort(RandomIt begin, RandomIt end, const size_t threshold,
      Compare comp = Compare())
  {
    if (begin == end) return;
    assert(begin < end);
    if ((end - begin) < threshold) {
      heap_sort(begin, end, comp);
    } else {
      auto mid = clrs::partition(begin, end, comp);
      intro_sort(begin, mid, threshold, comp);
      intro_sort(mid + 1, end, threshold, comp);
    }
  }

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void intro_sort(RandomIt begin, RandomIt end, Compare comp = Compare()) {
    if (begin == end) return;
    size_t threshold = std::log2(end - begin) + 1;
    intro_sort(begin, end, threshold, comp);
  }

}

#endif

